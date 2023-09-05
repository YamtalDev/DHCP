/******************************************************************************

    Writer: Tal Aharon

    Reviewer: David Haver.

    Date: 16.05.2023

*******************************************************************************

                          Description:

  The code implements a DHCP server for managing IP address allocation within a 
  network range. It provides functions for creating the DHCP server, allocating 
  IP addresses, and freeing them. The DHCP server uses a trie data structure to 
  store and manage allocated IP addresses. It supports network configuration and 
  handles scenarios such as successful allocation, failed allocation, and double 
  allocation attempts.

******************************************************************************/
#include <stdint.h> /* uint32_t, uint8_t */
#include <stdlib.h> /* malloc, free      */
#include <limits.h> /* CHAR_BIT          */
#include <string.h> /* memcpy            */
#include <assert.h> /* assert            */


#include "dhcp.h"   /* Internal API      */
#include "trie.h"   /* Internal API      */
/*****************************************************************************/
typedef status_t (*table_t)(dhcp_t *dhcp, const uint32_t, uint8_t *);

struct dhcp
{
    size_t bits;
    trie_t *trie;
    uint32_t net_ip;
};
/*****************************************************************************/ 
/* Ignore variable */
#define IGNORE(X) ((void)X)
/* Create the network ip */
#define NETWORK_IP(X) (~(HOST_MASK) & X)
/* Create bit mask of host ip */
#define HOST_MASK (((1 << dhcp->bits) - 1))
/* Create bits number in IP address */
#define IP_LEN (CHAR_BIT * sizeof(uint32_t))
/* Create the server IP with host mask */
#define BROADCAST_IP (HOST_MASK | dhcp->net_ip)
/*****************************************************************************/ 
static table_t HandleIPRequest[3];
static int IPIsValid(dhcp_t *, uint32_t);
static status_t DHCPNetworkConfig(dhcp_t *);
static uint32_t ConvertIP(uint8_t ip[IP_SIZE]);
static void ConvertIPBack(uint8_t ip[IP_SIZE]);
static status_t HandleIP(dhcp_t *, uint32_t, uint8_t result_ip[IP_SIZE]);
static status_t HandleNextIP(dhcp_t *, const uint32_t, uint8_t result_ip[IP_SIZE]);
static status_t HandleSuccess(dhcp_t *, const uint32_t, uint8_t result_ip[IP_SIZE]);
static status_t HandleAllocationFail(dhcp_t *, const uint32_t, uint8_t result_ip[IP_SIZE]);
/*****************************************************************************/
dhcp_t *DHCPCreate(const unsigned char net_ip[IP_SIZE], size_t bits)
{
    uint32_t ip = 0;
    dhcp_t *dhcp = NULL;
    status_t status = 0;
    ip = ConvertIP((uint8_t *)net_ip);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if(NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->bits = IP_LEN - bits;
    dhcp->net_ip = NETWORK_IP(ip);
    status = DHCPNetworkConfig(dhcp);
    if((bits >= (IP_LEN - 1)) || SUCCESS != status)
    {
        DHCPDestroy(dhcp);
        return (NULL);
    }

    return (dhcp);
}
/*****************************************************************************/ 
void DHCPDestroy(dhcp_t *dhcp)
{
    if(NULL == dhcp)
    {
        return;
    }

    TrieDestroy(dhcp->trie);
    free(dhcp);
}
/*****************************************************************************/ 
status_t DHCPAllocateIP
(dhcp_t *dhcp, const unsigned char preferred_ip[IP_SIZE], unsigned char result_ip[IP_SIZE])
{
    uint32_t ip = 0;
    assert(dhcp);
    if(!preferred_ip)
    {
        return (FAIL);
    }

    ip = ConvertIP((uint8_t *)preferred_ip);
    if(!IPIsValid(dhcp, ip))
    {
        ip = dhcp->net_ip;
    }

    return (HandleIP(dhcp, ip, result_ip));
}
/*****************************************************************************/ 
status_t DHCPFreeIP(dhcp_t *dhcp, unsigned char ip[IP_SIZE])
{
    if(!IPIsValid(dhcp, ConvertIP(ip)))
    {
        return (FAIL);
    }

    return (TrieRemove(dhcp->trie, ConvertIP(ip), dhcp->bits));
}
/*****************************************************************************/ 
size_t DHCPCountFree(const dhcp_t *dhcp)
{
    size_t total_ips = (size_t)(1 << dhcp->bits);
    return total_ips - TrieCountAllocations(dhcp->trie, dhcp->bits);
}
/*****************************************************************************/ 
static status_t DHCPNetworkConfig(dhcp_t *dhcp)
{
    int status = SUCCESS;
    uint32_t server_ip = 0;
    uint32_t network_ip = 0;
    uint32_t broadcast_ip = 0;
    uint8_t result[IP_SIZE] = {0};
    dhcp->trie = TrieCreateNode();
    if(NULL == dhcp->trie)
    {
        return (FAIL);
    }

    network_ip = dhcp->net_ip;
    broadcast_ip = BROADCAST_IP;
    server_ip = broadcast_ip - 1;

    HandleIPRequest[FAIL] = HandleNextIP;
    HandleIPRequest[SUCCESS] = HandleSuccess;
    HandleIPRequest[MALLOC_FAILURE] = HandleAllocationFail;

    status += TrieAllocate(dhcp->trie, server_ip, dhcp->bits, (uint32_t *)result);
    status += TrieAllocate(dhcp->trie, network_ip, dhcp->bits, (uint32_t *)result);
    status += TrieAllocate(dhcp->trie, broadcast_ip, dhcp->bits, (uint32_t *)result);

    return (status);
}
/*****************************************************************************/
static status_t HandleIP(dhcp_t *dhcp, uint32_t ip, uint8_t result_ip[IP_SIZE])
{
    int status = SUCCESS;
    uint32_t *result = (uint32_t *)result_ip;
    status = TrieAllocate(dhcp->trie, ip, dhcp->bits, result);
    return (HandleIPRequest[status](dhcp, ip, result_ip));
}
/*****************************************************************************/
static status_t HandleNextIP
(dhcp_t *dhcp, const uint32_t preferred_ip, uint8_t result_ip[IP_SIZE])
{
    int status = 0;
    uint32_t *result = (uint32_t *)result_ip;
    status = TrieAllocate(dhcp->trie, dhcp->net_ip + 1, dhcp->bits, result);
    if(SUCCESS == status)
    {
        ConvertIPBack(result_ip);
    }

    IGNORE(preferred_ip);
    return (status);
}
/*****************************************************************************/
static status_t HandleAllocationFail
(dhcp_t *dhcp, const uint32_t preferred_ip, uint8_t result_ip[IP_SIZE])
{
    IGNORE(dhcp);
    IGNORE(result_ip);
    IGNORE(preferred_ip);
    return (MALLOC_FAILURE);
}
/*****************************************************************************/
static status_t HandleSuccess
(dhcp_t *dhcp, const uint32_t preferred_ip, uint8_t result_ip[IP_SIZE])
{
    IGNORE(dhcp);
    IGNORE(preferred_ip);
    ConvertIPBack(result_ip);
    return (SUCCESS);
}
/*****************************************************************************/
static int IPIsValid(dhcp_t *dhcp, uint32_t preferred_ip)
{
    return (dhcp->net_ip != preferred_ip && 
           (BROADCAST_IP != preferred_ip) && 
           (BROADCAST_IP - 1) != preferred_ip && 
           (dhcp->net_ip & ~HOST_MASK) == (preferred_ip & ~HOST_MASK));
}
/*****************************************************************************/
static uint32_t ConvertIP(uint8_t ip[IP_SIZE])
{
    size_t i = 0;
    uint32_t result = 0;
    for(; i < IP_SIZE; ++i)
    {
        result = (result << CHAR_BIT) | ip[i];
    }

    return (result);
}
/*****************************************************************************/
static void ConvertIPBack(uint8_t ip[IP_SIZE])
{
    uint32_t converted_ip = ConvertIP(ip);
    memcpy(ip, &converted_ip, IP_SIZE);
}
/*****************************************************************************/
