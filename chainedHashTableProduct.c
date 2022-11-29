/* 
 * chainedHashTableProduct.c
 *
 * Implementation of abstractHashTable.h that uses a chained
 * hash table. The calling program supplies the hashing function
 * as part of the initialization.
 *
 * Limitation: this implementation will not work well for duplicate
 * keys. It will store both but the returned data is unpredictable.
 *
 * Limitation: this implementation assumes keys are strings 
 * less than 128 chars long
 *
 *   Created by Sally Goldin on 5 March 2012 for CPE 113
 *   Updated to explicity keep track of list head and tail on
 *       26 March 2013
 *   Modified with permission by [Phoramint Taweeros] on [05/apr/2021].
 *   
 *   Edit: change all name each Function that include word Product to make clear
 *   meaning must use in product structure only and anouther structure and code have *   not change. Change only name of function.
 */
 
 /*  Based on code by Sally Goldin from [chainedHashTable.c]
    Used with permission.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuctionSystem.h"
#include "abstractHashTableProduct.h"
#define KEYLEN 128

/* Structure for table elements */
typedef struct _hashItem
{
  char key[KEYLEN];              /* copy of the key */
  void* data;                    /* data */
  struct _hashItem * next;       /* next item in the bucket if any */
} HASH_ITEM_T; 

/* Structure for list with head and tail */
typedef struct _linkedList
{
  HASH_ITEM_T* head;             /* first item in list - null if list empty*/
  HASH_ITEM_T* tail;             /* last item in the list */
} LINKED_LIST_T; 

/* Hash function - set by hashTableInit  */
unsigned int (*hashFnProduct)(char* key) = NULL;

static LINKED_LIST_T * tableProduct = NULL;  /* we will allocate our table based on
                                       * initialization arguments and store it
                                       * here 
                                       */     
static int tableProductSize = 0;     /* size of the table */
static int itemProductCount = 0;     /* keep track of current number of stored items */

/* Return the number of slots in the hash table.
 */
int hashTableProductSize()
{
  return tableProductSize;
}


/* Return the number of items currently stored in the hash table.
 */
int hashTableItemProductCount()
{
  return itemProductCount;
}
 
/* Initialize the hash table.
 * Arguments
 *    size                - How many slots in the table
 *                          Must be 1 or greater. We assume the caller
 *                          has checked this.
 *    hashFunction        - Function that takes a string and returns an int
 *                          which will be the index into the table.
 * Return 1 if successful, 0 if some error occurred.
 */
int hashTableProductInit(int size, unsigned int (*hashFunction)(char* key))
{
  int bOk = 1;
  /* free the old table, if any */
  hashTableProductFree();
  hashFnProduct = hashFunction;
  tableProductSize = size;
  /* try to allocate the table, which will store pointers
   * to LINKED_LIST_T elements.
   */
  tableProduct = (LINKED_LIST_T*) calloc(size,sizeof(LINKED_LIST_T));
  if (tableProduct == NULL)   
  {
    bOk = 0;
  }
  return bOk;
}


/* Free the hash table.
 */
void hashTableProductFree()
{
  int i = 0;
  HASH_ITEM_T * pItem = NULL;
  HASH_ITEM_T * pNextItem = NULL;
  if (tableProduct != NULL) 
  {
	  for (i = 0; i < tableProductSize; i++)
	  {
	    if (tableProduct[i].head != NULL)  /* something stored in this slot */
	    {
	      pItem = tableProduct[i].head;
	      /* walk the linked list, freeing each item */
	      while (pItem != NULL)
	      {
		      pNextItem = pItem->next;
          free(pItem);
		      pItem = pNextItem;
	      }
	      tableProduct[i].head = NULL;
        tableProduct[i].tail = NULL;
	    }
	  }
	free(tableProduct);
	tableProduct = NULL;
	tableProductSize = 0;
	itemProductCount = 0;
  }
}


/* Insert a value into the hash table.
 * Arguments 
 *    key                 - character string key
 *    data                - data to store in the table
 *    pCollision          - set to true if there was a collision storing
 *                          the data, else false 
 * Returns true (1) unless hash table has not been initialized or
 * we can't allocate memory, in which case returns false (0)
 */
int hashTableProductInsert(char* key, void* data,int* pCollision)
{
  int bOk = 1;    
  int hashval = 0;
  HASH_ITEM_T * pItem = NULL;
  HASH_ITEM_T * pTemp = NULL;
  if (tableProduct == NULL)  /* not initialized */
	  return 0;
  pItem = (HASH_ITEM_T*) calloc(1,sizeof(HASH_ITEM_T));
  if (pItem == NULL)
  {
    bOk = 0;  /* can't allocate memory */
  }
  else
  {
    strncpy(pItem->key,key,KEYLEN-1);
    pItem->data = data;
    hashval = hashFnProduct(key);
    if (tableProduct[hashval].head == NULL)
    {
	    tableProduct[hashval].head = pItem;  /* bucket was empty */
	    *pCollision = 0;              /* no collision */
    }
    else
    {
	    *pCollision = 1;         /* We have a collision */
	    /* put the new item at the end of the bucket list */
	    tableProduct[hashval].tail->next = pItem;
    }
    tableProduct[hashval].tail = pItem;
    itemProductCount++;
  }
  return bOk;
}


/* Remove a value from the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data removed, or NULL if it is not found or table not init'd 
 */
void* hashTableProductRemove(char* key)
{
  void * foundData = NULL;
  HASH_ITEM_T* pPrev = NULL;
  HASH_ITEM_T* pTemp = NULL;
  if (tableProduct != NULL)    /* initialized */
  {
    int hashval = hashFnProduct(key);
    if (tableProduct[hashval].head != NULL)   /* in the table */
    {
	    pTemp = tableProduct[hashval].head;
	    while (pTemp != NULL)
	    {
	      if (strncmp(pTemp->key,key,KEYLEN-1) == 0)  /* match */
	      {
		      foundData = pTemp->data;
		      if (pPrev == NULL)  /* first item */
		      {
		        tableProduct[hashval].head = pTemp->next;
		      }
          else 
          {
            pPrev->next = pTemp->next;
          }
          /* adjust tail if necessary */
          if (tableProduct[hashval].tail == pTemp)
          {
            tableProduct[hashval].tail = pPrev; 
          } 
          free(pTemp);
          itemProductCount--;
          pTemp = NULL;  /* this will make us exit loop */
		    }
	      else
	      {
          pPrev = pTemp;
          pTemp = pTemp->next;  /* check next item */	  
		    }

	    } /* end loop through items in the bucket */
    }     /* end if the bucket is not empty */
  }         /* end if the hash table is initialized */            
  return foundData;
}


/* Look up a value in the hash table.
 * Arguments 
 *    key                 - character string key
 * Returns the data associated with the key, or NULL if 
 * data associated with the key is not found.
 */
void* hashTableProductLookup(char* key)
{
  /* This function is similar to remove but we do not
   * change anything in the hashtable structure 
   */
  void * foundData = NULL;
  HASH_ITEM_T* pPrev = NULL;
  HASH_ITEM_T* pTemp = NULL;
  if (tableProduct != NULL)    /* initialized */
  {
    int hashval = hashFnProduct(key);
    if (tableProduct[hashval].head != NULL)   /* in the table */
    {
	    pTemp = tableProduct[hashval].head;
	    while (pTemp != NULL)
	    {
	      if (strncmp(pTemp->key,key,KEYLEN-1) == 0)  /* match */
		    {
		      foundData = pTemp->data;
		      pTemp = NULL;  /* this will make us exit loop */
		    }
	      else
	      {
          pPrev = pTemp;
          pTemp = pTemp->next;  /* check next item */	  
        }
	    } /* end loop through items in the bucket */
    }        /* end if the key is in the table */
  }            /* end if the hash table is initialized */            
  return foundData;
}


