/*********************************************************************
 *
 *   main.c
 *
 *      This program main file that defragment many files
 *    to show main display of this program.
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableUser.h"
#include "abstractHashTableProduct.h"
#include "abstractSortBinary.h"
#include "AuctionSystem.h"
#define BUCKET_COUNT 503

/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHashUser(char* key)
{
  unsigned int result = 0;
  unsigned int tmp = 0;    
	int size = hashTableUserSize();
  int i = 0;
  for (i = 0; i < strlen(key); i++)    
  {
	/* shift up four bits then add in next char */ 
	  result = (result << 4) + key[i];
    if (tmp == (result & 0xf0000000))  /* if high bit is set */
	  {
	    /* XOR result with down shifted tmp */
	    result = result ^ (tmp >> 24);
      /* then XOR with tmp itself */
	    result = result ^ tmp;
			//printf("%d \n",result);
	  }
  }
    
  result = result % size;   /* make it fit in the table size */ 
  return result;
}

/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHashProduct(char* key)
{
  unsigned int result = 0;
  unsigned int tmp = 0;    
	int size = hashTableProductSize();
  int i = 0;
  for (i = 0; i < strlen(key); i++)    
  {
	/* shift up four bits then add in next char */ 
	  result = (result << 4) + key[i];
    if (tmp == (result & 0xf0000000))  /* if high bit is set */
	  {
	    /* XOR result with down shifted tmp */
	    result = result ^ (tmp >> 24);
      /* then XOR with tmp itself */
	    result = result ^ tmp;
	  }
  }
  result = result % size;   /* make it fit in the table size */ 
  return result;
}

/*  [****PRIVATE FUNCTION****]
 *  This function will print display option of this program
 *  Arguments: productID - update product id before generate 
 *             countAllProduct - sum of product in database
 *  Returns : not return
*/
int getMenuOption()
{
  char input[32];                  /* input from user*/
  int option = -1;                 /*keep option from user input*/
  while (option < 0)
  {
    printf("\nOptions:\n");
    printf("  1 - Print user data\n");
    printf("  2 - Add money\n");
    printf("  3 - Create auction\n");
    printf("  4 - Print list all product\n");
    printf("  5 - Search by product name\n");
    printf("  6 - Bid product\n");
    printf("  7 - Show winner\n");
		printf("  8 - Log out\n");
    printf("  9 - Exit program\n");
    printf("Which option? ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&option);
    if ((option > 9) || (option < 1))
    {
	    printf("Invalid selection - choose 1 to 7\n");
	    option = -1;
	  }
  }
  printf("\n");
  return option;
}

int main() 
{
  int countAllUser = 0;             /*sum of user in hashTable User*/
  int countAllProduct = 0;          /*sum of user in hashTable Product*/
  ALLUSER_T *pHeadUser = NULL;
  ALLPRODUCT_T *pHeadProduct = NULL;
  ALLUSER_T *pCurrentUser = NULL;
  ALLPRODUCT_T *pCurrentProduct = NULL;
  char usernameLogin[30];           /*keep username login at that time*/
  FILE * pIn = NULL;          /*for read input file*/
  char input[128];            /*input from user*/
  int check = -1;             /*check for pass*/
  int check1 = 0;             /*check for Login*/
  int option = -1;             /*get option to do feature in AuctionSystem*/
  int i = 0;
	char productTosearch[32];
  BID_T *delHistory = NULL;
  BID_T *currentHistory = NULL;
  PRODUCT_T *delProduct = NULL;
  
  check = hashTableUserInit(BUCKET_COUNT, &bitwiseOpHashUser);
  if(check != 1)
  {
    printf("Error hash table\n");
    exit(0);
  }
  check = hashTableProductInit(BUCKET_COUNT, &bitwiseOpHashProduct);
  if(check != 1)
  {
    printf("Error hash table\n");
    exit(0);
  }
  pHeadUser = calloc(1,sizeof(ALLUSER_T));
  if(pHeadUser == NULL)
  {
    printf("Error to calloc key user\n");
    exit(0);
  }
  pHeadProduct = calloc(1,sizeof(ALLPRODUCT_T));
  if(pHeadProduct == NULL)
  {
    printf("Error to calloc key product\n");
    exit(0);
  }
  countAllUser = buildUser(pHeadUser,countAllUser);
  countAllProduct = buildProduct(pHeadProduct, countAllProduct);
  printf("\e[1;1H\e[2J");
	while (option != 3)
	{
    option = -1;
		while (option < 0)
		{
			printf("\nOptions:\n");
			printf("  1 - SignUp\n");
			printf("  2 - Login\n");
			printf("  3 - Exit\n");
			printf("Which option? ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%d",&option);
			if ((option > 3) || (option < 1))
			{
				printf("Invalid selection - choose 1 to 3\n");
				option = -1;
			}
		}
    if(option == 3)
      break;
		printf("\n");
		printf("\e[1;1H\e[2J");
		if(option == 1)
			countAllUser = signUpMenu(pHeadUser, countAllUser, usernameLogin);
		else if((option == 2)&&(loginOption(usernameLogin) == -1))
		{
      option = -1;
		}
    if(option != -1)
    {
      while(option!=8)
      {
        option = getMenuOption();
        printf("\e[1;1H\e[2J");
        if (option == 1)
          printUserData(usernameLogin);
        else if(option == 2)
          addMoney(usernameLogin);
        else if(option == 3)
          countAllProduct = creatAuction(pHeadProduct, countAllProduct, usernameLogin);
        else if(option == 4)
        {
          if(strcmp(pHeadProduct->productName,"\0") != 0)
          {
            printAllBinary(NULL);
          }
          else
          {
            printf("\t\t>> Print list all product menu <<\n\n");
            printf("->Not have product in database\n");
          }
        }
        else if(option == 5)
        {
          getProductName(productTosearch); 
          printProductData(productTosearch);
					memset(productTosearch,0,sizeof(productTosearch));
        }
        else if(option == 6)
          bidProduct(usernameLogin);
        else if(option == 7)
        {
          if(strcmp(pHeadProduct->productName,"\0") != 0)
          {
            showWinner(pHeadProduct);
          }
          else
          {
            printf("\t\t>> Show winner menu <<\n\n");
            printf("->Not have product in database\n");
          }
        }
        else if(option == 8)
        {
          if(logOut() == 1)
            break;
        }
        else if(option == 9)
        {
          if(exitProgram()==1)
            break;
          else
            option = -1;
        }
      }
      if(option == 9)
        option = 3;
    }
	}
  updateDataFileUser(pHeadUser);
	updateDataFileProduct(pHeadProduct);
	hashTableUserFree();
  if(strcmp(pHeadProduct->productName,"\0") != 0)
  {
    pCurrentProduct = pHeadProduct;
    while(pCurrentProduct != NULL)
    {
      delProduct = hashTableProductLookup(pCurrentProduct->productName);
      delHistory = currentHistory = delProduct->history;
      while(currentHistory != NULL)
      {
        currentHistory = currentHistory->pNext;
        free(delHistory);
        delHistory = currentHistory;
      }
      pCurrentProduct = pCurrentProduct->pNext;
    }
  }
 
  while(pHeadProduct != NULL)
  {
    pCurrentProduct = pHeadProduct;
    pHeadProduct = pCurrentProduct->pNext;
    free(pCurrentProduct);
  }
  while(pHeadUser != NULL)
  {
    pCurrentUser = pHeadUser;
    pHeadUser = pCurrentUser->pNext;
    free(pCurrentUser);
  }
	hashTableProductFree();
	freeBinaryTree(NULL);
  printf("Thank you^^\n");
  return  0;
}