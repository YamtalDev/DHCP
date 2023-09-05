/*===============================================================================

                           TRIE functionalities:

===============================================================================

1.) Function: TrieNode - Create a new trie node.

Usage: trie_t *trie = TrieNode()

Usage: trie_t *trie = TrieNode()

Description:
This function creates a new trie node and initializes its properties. 
It allocates memory for the trie node using malloc and sets the is_full 
property to EMPTY. The left and right child pointers are initialized to NULL. 
The function returns a pointer to the newly created trie node.

Arguments:
None.

Return value:

Returns a pointer to the newly created trie node.

Time complexity: O(1).
Space complexity: O(1).

===============================================================================

2.) Function: TrieDestroy - Destroy a trie and free memory.

Usage: TrieDestroy(trie)

Description:
This function destroys a trie and frees the memory allocated for it, 
including all its nodes. It recursively traverses the trie in a post-order 
fashion and frees each node. The function takes a pointer to the trie to be 
destroyed as an argument.

Arguments:

trie - A pointer to the trie to be destroyed.
Return value:
None.

Time complexity: O(n).
Space complexity: O(1).

===============================================================================

3.) Function: TrieRemove - Remove an IP from the trie.

Usage: status_t status = TrieRemove(trie, ip)

Description:
This function removes the given IP from the trie if it exists. It traverses 
the trie based on the bits of the IP address and removes the corresponding 
nodes. The function also handles the case of double freeing a node.

Arguments:

trie: A pointer to the trie.
ip: The IP address to be removed from the trie.
Return value:

Returns SUCCESS if the IP was successfully removed.
Returns FAILURE if the IP does not exist in the trie.
Returns DOUBLE_FREE_NODE if attempting to remove an IP 
from an already freed node.

Time complexity:

Time complexity: O(L).
Space complexity: O(1).

===============================================================================


4.) Function: TrieAllocateIP - Insert an IP into the trie.

Usage: status_t status = TrieAllocateIP(trie, ip, result_ip)

Description:
This function inserts the given IP into the trie. It traverses the trie based on 
the bits of the IP address and allocates the necessary nodes to accommodate the IP.

Arguments:

trie: A pointer to the trie.
ip: The IP address to be inserted into the trie.
Return value:

Returns SUCCESS if the IP was successfully inserted.
Returns FAILURE if the IP insertion failed due to an error.
Returns DOUBLE_ALLOCATION if attempting to insert an IP into an already allocated node.
Returns FAILED_TO_ALLOCATE if there was a memory allocation failure during the insertion.
Time complexity:

Time complexity: O(L).
Space complexity: O(1).

===============================================================================

5.) Function: TrieCountAllocatedIPs - Count the number of allocated IPs in the trie.

Usage: TrieCountAllocatedIPs(trie)

Description:
This function counts the number of allocated IP addresses in the trie. It 
recursively traverses the trie and checks whether each node represents an 
allocated IP by checking the is_full flag. If the is_full flag is set for a 
node, it increments the count by one. The function continues to traverse the 
left and right child nodes and accumulates the count of allocated IPs in the trie.

Arguments:

trie: A pointer to the trie.
Return value:
The function returns the total count of allocated IPs in the trie.

Time complexity: O(N).
Space complexity: O(log(N))

==============================================================================*/

#include <stdint.h> /* uint32_t */
#include <stddef.h> /* size_t   */

#ifndef __TRIE_H__
#define __TRIE_H__

enum trie_status_t
{
    ALLOCATED = 0,
    DOUBLE_ALLOCATION,
    FAILED_TO_ALLOCATE,
    DOUBLE_FREE_NODE
};

typedef struct trie trie_t;
typedef uint32_t data_t;

void TrieDestroy(trie_t *);

trie_t *TrieCreateNode(void);

int TrieRemove(trie_t *, data_t, size_t);

size_t TrieCountAllocations(const trie_t *, size_t);

int TrieAllocate(trie_t *, data_t, size_t, data_t *);

#endif /* __TRIE_H__ */
