/******************************************************************************

    Writer: Tal Aharon

    Reviewer: David.

    Date: 16.05.2023

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <assert.h>  /* assert       */

#include "dhcp.h"    /* Internal API */
/*****************************************************************************/
#define SUCCESS (0) 
void AllocateTest(void);
void FreeTest(void);
void CountFreeTest(void);

int main()
{
	AllocateTest();
	FreeTest();
	CountFreeTest();
	puts("passed");
	return 0;
}

void AllocateTest(void)
{
	size_t i = 0;
    size_t subnet_mask = 10;
    unsigned char subnet1[IP_SIZE]        = {192, 165, 0, 0};
    unsigned char result_ip[IP_SIZE]      = {0  , 0  , 0, 0};
    unsigned char preferred_ip[IP_SIZE]   = {192, 165, 135, 12};
    unsigned char preferred_ip2[IP_SIZE]  = {192, 164, 135, 12};
	unsigned char subnet[IP_SIZE]         = {10, 122, 15, 0};
	unsigned char check[IP_SIZE]          = {10, 122, 15, 0};
	unsigned char result[IP_SIZE]         = {0, 0, 0, 0};
    dhcp_t *dhcp1 = DHCPCreate(subnet1, subnet_mask);
	dhcp_t *dhcp = DHCPCreate(subnet, 24);

    assert(dhcp);
    assert(dhcp1);
    assert(SUCCESS == DHCPAllocateIP(dhcp1, preferred_ip, result_ip));
    assert(SUCCESS == DHCPAllocateIP(dhcp1, preferred_ip2, result_ip));


	assert(NULL != dhcp);
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 1;
	for(i = 0; i < IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 2;

	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 254;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 3;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}

	check[3] = 7;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}

	check[2] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 4;
	check[2] = 15;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	assert(FAIL == DHCPAllocateIP(dhcp, NULL, result));

	DHCPDestroy(dhcp);
	dhcp = NULL;

	dhcp = DHCPCreate(subnet, 27);
	assert(NULL != dhcp);
	check[2] = 15;
	check[3] = 0;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 1;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 31;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 2;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 30;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 3;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 7;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[2] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 4;
	check[2] = 15;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}

	DHCPDestroy(dhcp);
	dhcp = NULL;

	subnet[3] = 5;

	dhcp = DHCPCreate(subnet, 24);
	assert(NULL != dhcp);
	check[2] = 15;
	check[3] = 0;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 1;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 2;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 254;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 3;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 7;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[2] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 4;
	check[2] = 15;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}

	DHCPDestroy(dhcp1);
	DHCPDestroy(dhcp);
	dhcp = NULL;
}

void FreeTest(void)
{
	unsigned char subnet[IP_SIZE] = {10, 122, 0, 0};
	unsigned char check[IP_SIZE] = {10, 122, 0, 0};
	unsigned char result[IP_SIZE] = {0, 0, 0, 0};
	size_t i = 0;


	dhcp_t *dhcp = DHCPCreate(subnet, 17);
	assert(NULL != dhcp);
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 1;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 255;
	check[2] = 127;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 2;
	check[2] = 0;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 254;
	check[2] = 127;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 3;
	check[2] = 0;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[3] = 7;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}
	check[2] = 255;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	check[3] = 4;
	check[2] = 0;
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}

	check[3] = 0;
	assert(FAIL == DHCPFreeIP(dhcp, check));
	check[2] = 127;
	check[3] = 255;
	assert(FAIL == DHCPFreeIP(dhcp, check));
	check[3] = 254;
	assert(FAIL == DHCPFreeIP(dhcp, check));
	check[2] = 128;
	check[3] = 4;
	assert(FAIL == DHCPFreeIP(dhcp, check));
	check[2] = 0;
	check[3] = 1;
	assert(SUCCESS == DHCPFreeIP(dhcp, check));
	check[3] = 1;
	assert(DOUBLE_FREE == DHCPFreeIP(dhcp, check));
	check[3] = 145;
	assert(DOUBLE_FREE == DHCPFreeIP(dhcp, check));
	check[3] = 254;
	assert(DOUBLE_FREE == DHCPFreeIP(dhcp, check));

	
	check[3] = 1;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	for(i = 0; i <IP_SIZE; ++i)
	{
		assert(check[i] == result[i]);
	}


	DHCPDestroy(dhcp);
	dhcp = NULL;
}

void CountFreeTest(void)
{
	unsigned char subnet[IP_SIZE] = {10, 122, 15, 0};
	unsigned char check[IP_SIZE] = {10, 122, 15, 0};
	unsigned char result[IP_SIZE] = {0, 0, 0, 0};

	dhcp_t *dhcp = DHCPCreate(subnet, 29);
	assert(NULL != dhcp);
	assert(5 == DHCPCountFree(dhcp));

	check[3] = 2;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	assert(4 == DHCPCountFree(dhcp));
	check[3] = 5;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	assert(3 == DHCPCountFree(dhcp));

	check[3] = 0;
	assert(FAIL == DHCPFreeIP(dhcp, check));
	assert(3 == DHCPCountFree(dhcp));
	check[3] = 2;
	assert(SUCCESS == DHCPFreeIP(dhcp, check));
	assert(4 == DHCPCountFree(dhcp));
	check[3] = 5;
	assert(SUCCESS == DHCPFreeIP(dhcp, check));
	assert(5 == DHCPCountFree(dhcp));

	check[3] = 2;
	assert(SUCCESS == DHCPAllocateIP(dhcp, check, result));
	assert(4 == DHCPCountFree(dhcp));

	DHCPDestroy(dhcp);
	dhcp = NULL;
}
