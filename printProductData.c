/******************************************************************** *
 *
 *   printProductData.c
 *
 *      This program print information about the product for example,
 *  print their product ID and print error if do not find that user 
 *  read from structure. 
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableProduct.h"
#include "AuctionSystem.h"
#include "abstractSortBinary.h"

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data some product in database
 *  then print all data of that product
 *  Arguments: productName
 *  Returns : not have return
 */
void printProductData(char productName[])
{
	PRODUCT_T *data;      /*variable to keep data of product*/
	BID_T *currentBid;    /*variable to keep data of bid history of that product*/
	int i = 0;            /*loop counter variable*/

	data = hashTableProductLookup(productName);
	if(data != NULL)
  {
    printf("------------------------------------------\n");
    printf("Product ID: %s\n",data->productID);
    printf("Product Name: %s\n",data->productName);
    printf("Description:  %s\n",data->description);
    if(data->history != NULL)
    {
      printf("Now:   %.2lf\n",data->history->amount);
    }
    else
    {
      printf("Now:   %.2lf\n",data->startPrice);
    }
    printf("BuyOffPrice:  %.2lf\n",data->buyOffPrice);
    printf("Start: %.2d / %.2d / %.4d\n",data->startDay,data->startMonth,data->startYear);
    printf("End:   %.2d / %.2d / %.4d\n",data->endDay,data->endMonth,data->endYear);
    printf("*******************************************\n");
    printf("History:\n");
    currentBid = data->history;
    while(currentBid != NULL)
    {
      i++;
      printf("---> %d\n",i);
      printf("\tUser:%s\n",currentBid->usernameBid);
      printf("\tAmount:%.2lf\n",currentBid->amount);
      printf("\tBid day: %.2d / %.2d / %.4d\n",currentBid->bidDay,currentBid->bidMonth,currentBid->bidYear);
      currentBid = currentBid->pNext;
    }
    printf("*******************************************\n");
  }
	else
	{
		printf("Can't found product whith product name '%s'\n",productName);
	}
}

/*  [****PUBLIC FUNCTION****]
 *  This function will get product name to search
 *  Arguments: productName
 *  Returns : not have return
 */
void getProductName(char productName[])
{
	char input[32];   /*variable to keep input from user*/
	printf("Enter Product name to search: ");
  fgets(input, sizeof(input), stdin);
  sscanf(input, "%[^\n]",productName);
}
