/*=============================================================================

                           Customer requirements:

===============================================================================

*Correct and reliable implementation of DHCP functionality.

*Efficient algorithms for IP address allocation and deallocation.

*Clear and well-documented interface for ease of use.

*Effective error handling and memory management.

*Optimal memory usage, especially for large IP address ranges.

*Maintainable code structure for future updates.

===============================================================================

                           DHCP functionalities:

===============================================================================

1.) Function: DHCPCreate - Creates a DHCP object.

Usage: 

unsigned char subnet[IP_SIZE] = {192, 168, 0, 0}
size_t used_bits = 24
dhcp_t *dhcp = DHCPCreate(subnet, used_bits)

Description:

This function creates a DHCP object with the specified subnet and the number of 
used bits. The DHCP object is used to manage IP address allocation within the subnet.

Arguments:

subnet - An array of unsigned characters representing the subnet IP address.
used_bits - The number of bits used in the subnet mask.

Return value:
A pointer to the created DHCP object.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

===============================================================================

2.) Function: DHCPAllocateIP - Allocates an IP address from the DHCP.

Usage:

unsigned char preferred_ip[IP_SIZE] = {192, 168, 0, 10}
unsigned char result_ip[IP_SIZE]
status_t status = DHCPAllocateIP(dhcp, preferred_ip, result_ip)


Description:

Description:
This function allocates an IP address from the DHCP object. If a preferred IP 
address is provided, it will attempt to allocate that IP address. Otherwise, 
it will allocate the next available IP address in the subnet. The allocated 
IP address will be stored in the result_ip array provided by the user as an 
output parameter.

Arguments:

dhcp - A pointer to the DHCP object.
preferred_ip - An array of unsigned characters representing the preferred IP 
address (optional).
result_ip - An array of unsigned characters to store the allocated IP address.

Return value:

SUCCESS: IP address allocation was successful.
FAIL: IP address allocation failed (no available IP addresses).

Time complexity: Worst: O(log N), Average: O(log N), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

===============================================================================

3.) Function: DHCPFreeIP - Frees an allocated IP address in the DHCP.

Usage: unsigned char ip[IP_SIZE] = {192, 168, 0, 10}
status_t status = DHCPFreeIP(dhcp, ip)

Description:

This function frees the specified IP address in the DHCP object, making it 
available for allocation again.

Arguments:

dhcp - A pointer to the DHCP object.
ip - An array of unsigned characters representing the IP address to be freed.
Return value:

SUCCESS: IP address deallocation was successful.
DOUBLE_FREE: The specified IP address is not allocated.

Time complexity: Worst: O(log N), Average: O(log N), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

===============================================================================

4.) Function: DHCPCountFree - Counts the number of free IP addresses in the DHCP.

Usage:

size_t free_count = DHCPCountFree(dhcp)

Description:
This function returns the number of available (free) IP addresses in the DHCP object.

Arguments:

dhcp - A pointer to the DHCP object.
Return value:
The number of available (free) IP addresses.

Time complexity: Worst: O(N), Average: O(N), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

===============================================================================

5.) Function: DHCPDestroy - Destroys the DHCP object, freeing allocated resources.

Usage:

DHCPDestroy(dhcp)

Description:

This function destroys the DHCP object and frees any allocated resources.

Arguments:

dhcp - A pointer to the DHCP object to be destroyed.
Return value: None.

Time complexity: Worst: O(N), Average:

Time complexity: O(N), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

==============================================================================*/

/*  size_t, NULL  */
#include <stddef.h> 

#ifndef __DHCP_H__
#define __DHCP_H__

#define IP_SIZE (4)

typedef struct dhcp dhcp_t;

typedef enum status
{
    SUCCESS = 0,
    FAIL,
    MALLOC_FAILURE,
    DOUBLE_FREE

} status_t;

status_t DHCPAllocateIP(dhcp_t *dhcp, const unsigned char preferred_ip[IP_SIZE], unsigned char result_ip[IP_SIZE]);

dhcp_t *DHCPCreate(const unsigned char subnet[IP_SIZE], size_t used_bits);

status_t DHCPFreeIP(dhcp_t *dhcp, unsigned char ip[IP_SIZE]);

size_t DHCPCountFree(const dhcp_t *dhcp);

void DHCPDestroy(dhcp_t *dhcp);

#endif /* __DHCP_H__ */