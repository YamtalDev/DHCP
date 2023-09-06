/******************************************************************************

    Writer: Tal Aharon

    Date: 16.05.2023

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /* assert       */
#include <stdlib.h>  /*              */

#include "trie.h"    /* Internal API */
void TrieCreateTest(void);
/*****************************************************************************/
int main(void)
{
	TrieCreateTest();
	puts("\nTrieCreateTest() : passed.");
	return (0);
}
/************************************** ***************************************/
void TrieCreateTest(void)
{
    trie_t *trie = TrieCreateNode();
    assert(trie);
    TrieDestroy(trie);
}
/*****************************************************************************/
