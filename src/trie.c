/******************************************************************************

    Writer: Tal Aharon

    Reviewer: .

    Date: 16.05.2023

*******************************************************************************

                          Description: 

  This code implements a trie data structure for managing IP addresses. The trie 
  supports operations such as inserting an IP address, checking if an IP address 
  is allocated, finding an IP address, and removing an IP address. The trie is 
  represented using a binary tree where each node has two children. The code 
  includes functions for creating a trie node, destroying a trie, allocating 
  an IP address, checking if an IP address is allocated, inserting an IP 
  address into the trie, finding an IP address in the trie, and removing 
  an IP address from the trie.

******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <limits.h> /* CHAR_BIT     */
#include <assert.h> /* assert       */
#include <string.h> /* memcpy       */

#include "trie.h"   /* Internal API */
/*****************************************************************************/
enum full
{
    EMPTY = 0, FULL
};
/*****************************************************************************/
enum family
{
    RIGHT_CHILD = 0, LEFT_CHILD,
    NUMBER_OF_CHILDRENS
};
/*****************************************************************************/
struct trie
{
    trie_t *child[NUMBER_OF_CHILDRENS];
    int is_full;
};
/*****************************************************************************/
#define TRIE_SUCCESS (0)
#define LEFT(X) (X->child[LEFT_CHILD])
#define RIGHT(X) (X->child[RIGHT_CHILD])
#define MASK(X,Y) ((X >> (Y - 1)) & 0X01)
#define NODE_HAS_CHILDRENS(X) ((NULL != LEFT(X) && NULL != RIGHT(X)))
#define NODE_CHILDREN_ARE_FULL(X) ((LEFT(X))->is_full && (RIGHT(X))->is_full)
#define INCREMENT(X,Y) ((X + (0x01 << (Y - 1))) & (((data_t)0 - 1) << (Y - 1)))
/*****************************************************************************/
trie_t *TrieCreateNode(void)
{
    trie_t *trie_node = (trie_t *)malloc(sizeof(trie_t));
    if (NULL != trie_node)
    {
        trie_node->is_full = EMPTY;
        RIGHT(trie_node) = NULL;
        LEFT(trie_node) = NULL;
    }

    return (trie_node);
}
/*****************************************************************************/ 
void TrieDestroy(trie_t *root)
{
    if(NULL != root)
    {
        TrieDestroy(RIGHT(root));
        TrieDestroy(LEFT(root));
        free(root);
    }
}
/*****************************************************************************/ 
int TrieAllocate(trie_t *root, data_t data, size_t level, data_t *result)
{
    trie_t **child = NULL;
    data_t status = 0;
    assert(root);

    if(root->is_full)
    {
        return (DOUBLE_ALLOCATION);
    }

    if(level == 0)
    {
        *result = data;
        root->is_full = FULL;
        return (ALLOCATED);
    }

    child = &(root->child[MASK(data, level)]);
    if(NULL == *child && (NULL == (*child = TrieCreateNode())))
    {
        return (FAILED_TO_ALLOCATE);
    }

    status = TrieAllocate(*child, data, level - 1, result);
    if(DOUBLE_ALLOCATION == status && 0 == MASK(data, level))
    {
        child = &(LEFT(root));
        if(NULL == *child && NULL == (*child = TrieCreateNode()))
        {
            return (FAILED_TO_ALLOCATE);
        }

        data = INCREMENT(data, level);
        status = TrieAllocate(*child, data, level - 1, result);
    }

    if(NODE_HAS_CHILDRENS(root) && NODE_CHILDREN_ARE_FULL(root))
    {
        root->is_full = FULL;
    }

    return (status);
}
/*****************************************************************************/ 
size_t TrieCountAllocations(const trie_t *root, size_t level)
{
    size_t count = 0;
    if(NULL == root)
    {
        return (0);
    }

    if(root->is_full && level == 0)
    {
        ++count;
    }

    count += TrieCountAllocations(LEFT(root), level - 1);
    count += TrieCountAllocations(RIGHT(root), level - 1);

    return (count);
}
/*****************************************************************************/
int TrieRemove(trie_t *root, data_t data, size_t level)
{
    data_t result = 0;
    trie_t *child = NULL;

    if(NULL == root)
    {
        return (DOUBLE_FREE_NODE);
    }

    if(level == 0)
    {
        if(EMPTY == root->is_full)
        {
            return (DOUBLE_FREE_NODE);
        }
        else
        {
            root->is_full = EMPTY;
            return (TRIE_SUCCESS);
        }
    }

    child = root->child[MASK(data, level)];
    result = TrieRemove(child, data, level - 1);
    if(TRIE_SUCCESS == result && !LEFT(child) && !RIGHT(child))
    {
        free(child);
        child = NULL;
        root->child[MASK(data, level)] = NULL;
    }

    root->is_full = EMPTY;
    return (result);
}
/*****************************************************************************/
