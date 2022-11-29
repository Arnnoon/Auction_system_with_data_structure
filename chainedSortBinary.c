/********************************************************************** 
 * chainedSortBinary.c
 *
 * Implementation of abstractHashTable.h that uses a Binary tree.
 * The calling program supplies the sorted binary function
 * as part of the initialization.
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractSortBinary.h"
#include "AuctionSystem.h"

typedef struct _sortBinary
{
  struct _product * product;			/*data*/
	struct _sortBinary * pRight;    /*left data from root*/
	struct _sortBinary * pLeft;     /*right data from root*/
} SORT_BINARY_T;

/*varible to keed root node of Binary tree
*/
static SORT_BINARY_T* root = NULL;

/**  [****PUBLIC FUNCTION****]
 *
 * Arguments: pHeadProduct
 * Returns: Not return
 */
void insertBinaryNode(void* current, void* nnew)
{
		SORT_BINARY_T* currentNode = current; /*run variable for node at that time*/
		SORT_BINARY_T* newNode = nnew;  /*new node variable to insert*/
		
    if (newNode->product->biddingAmount <= currentNode->product->biddingAmount)
    {		
       	if (currentNode->pLeft == NULL)
			 	{
						currentNode->pLeft = newNode;
			 	}
       	else
				{
						insertBinaryNode(currentNode->pLeft,newNode);
				}
    }
    else if (newNode->product->biddingAmount > currentNode->product->biddingAmount)
    {
       	if (currentNode->pRight == NULL)
				{
					currentNode->pRight = newNode;
				}
       	else
				{
					insertBinaryNode(currentNode->pRight,newNode);
				}
    }
}

/**  [****PRUBLIC FUNCTION****]
 * Arguments: pHeadProduct
 * Returns: Not return
 */
void createBinaryNode(void* data)
{
		SORT_BINARY_T* pRoot;     /*get root data of binary tree*/
		SORT_BINARY_T* insertNode = NULL; /*get node to insert*/
		PRODUCT_T* newNodeData = data;    /*set variable to make new node*/
		
		if (root == NULL)
		{
				root = calloc(1,sizeof(SORT_BINARY_T));
				if (root == NULL)
				{
						printf("can't allocate\n");
						exit(0);
				}
		}
		insertNode = calloc(1,sizeof(SORT_BINARY_T));
		if (insertNode == NULL)
		{
					printf("can't allocate\n");
				exit(0);
		}
		
    if (root->product == NULL)
    {
				root->product = newNodeData;
				pRoot = root;
    }
    else
    {
				pRoot = root;
				insertNode->product = newNodeData;
        insertBinaryNode(pRoot, insertNode);
    }
}

/**  [****PRUBLIC FUNCTION****]
 * Arguments: pHeadProduct
 * Returns: Not return
 */
void printAllBinary(void* currentNode)
{
		SORT_BINARY_T* print = currentNode; /*run variable for node at that time*/

		if(print == NULL)
		{
			print = root;
		}
		if (root == NULL)
		{
			printf("Sorry. Ther are no products data yet\n");
		}
		else
		{
			if(print->pLeft != NULL)
			{
					printAllBinary(print->pLeft);
			}
			printf("------------------------------------------\n");
			printf("Product ID: %s\n",print->product->productID);
			printf("Product Name: %s\n",print->product->productName);
			printf("Description:  %s\n",print->product->description);
			if(print->product->history != NULL)
			{
				printf("Now price:   %.2lf\n",print->product->history->amount);
			}
			else
			{
				printf("Now price:   %.2lf\n",print->product->startPrice);
			}
				
			printf("BuyOffPrice:  %.2lf\n",print->product->buyOffPrice);
			printf("Start: %.2d / %.2d / %.4d\n",print->product->startDay,print->product->startMonth,	   print->product->startYear);
			printf("End:   %.2d / %.2d / %.4d\n",print->product->endDay,print->product->endMonth,print->product->endYear);
			if(print->product->returnMoney == 1)
			{
				printf("\n%33s\n","This auction has ended!!");
			}
			printf("------------------------------------------\n");
			
			if(print->pRight != NULL)
			{
					printAllBinary(print->pRight);
			}
		}
}

/**  [****PRUBLIC FUNCTION****]
 * Arguments: pHeadProduct
 * Returns: Not return
 */
void freeBinaryTree(void* currentNode)
{
		SORT_BINARY_T* freeSt = currentNode; /*run variable for node at that time*/

		if(freeSt == NULL)
		{
			freeSt = root;
		}
		if(root != NULL)
		{
			if(freeSt->pLeft != NULL)
			{
					freeBinaryTree(freeSt->pLeft);
			}
			if(freeSt->pRight != NULL)
			{
					freeBinaryTree(freeSt->pRight);
			}
			free(freeSt);
		}
		
}


