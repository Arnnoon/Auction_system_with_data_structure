/*********************************************************************
 *
 *   buildProduct.c
 *
 *      This program will create structure product like 
 *  hash table from our database and then read file from structure.
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableProduct.h"
#include "abstractSortBinary.h"
#include "abstractHashTableUser.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  This function will open file and then read product file
 *  each line put the information in structure.
 *  Arguments: pHead of ALLPRODUCT_T, countAllProduct
 *  Returns : count of product
 */
int buildProduct(ALLPRODUCT_T *pHead,int countAllProduct)
{
  FILE *pIn = NULL;                          /*pointer variable to open file*/
  int i = 0;                                 /*loop counter variable*/
  char input[1024];                          /*input from file*/
  //Zone product
  char productID[32];                         /*datail product about product ID*/
  char productName[32];                       /*datail product about product name*/
  char description[256];                      /*datail product about product description*/
  char startPrice[32], buyOffPrice[32];       /*datail product about product ID*/
  char startDay[3],startMonth[4],startYear[5];/*datail product about start date*/
  char endDay[3], endMonth[4], endYear[5];    /*datail product about end date*/
	char owner[32];
	char returnMoney[2];
  char countHistory[10];                      /*keep history count for that product*/
  double startPriceNum, buyOffPriceNum;       /*keep start price in integer form*/
  int startDayNum, startMonthNum,startYearNum;/*keep start date in integer form*/
  int endDayNum, endMonthNum, endYearNum;     /*keep end date in integer form*/
  int countHistoryNum = 0;                    /*keep history count in integer form*/
	int returnMoneyStatas;
  //Zone bid
  char username[30];                        /*user name user that bid*/                 
  char amount[30];                          /*datail amount that user bid*/
  char bidDay[3], bidMonth[4], bidYear[5];  /*the day, month and year that user bid*/
  double amountNum;                         /*keep amount in integer form*/
  int bidDayNum, bidMonthNum, bidYearNum;   /*the day, month and year that in integer form*/
  //Zone dummy variable
  USER_T *userBid;                  /*variable to keep data of user*/
  PRODUCT_T *productEntry;          /*variable to keep data of product*/
  ALLPRODUCT_T *keyProduct;
  ALLPRODUCT_T *pCurrent;
  BID_T *bidEntry;                  /*variable to keep data of bid history*/        
  BID_T *pHeadBid = NULL;              /*variable to keep data of bid history*/

  int count = 0;                  /*loop counter variable*/
  int pCollision;                 /*dummy variable*/
  pIn = fopen("product.txt","r");
  if(pIn == NULL)
  {
    printf("Error open %s file\n","user.txt");
    exit(0);
  }
  while (fgets(input,sizeof(input),pIn)!=NULL)
  {
    productEntry = calloc(1,sizeof(PRODUCT_T));
    if(productEntry == NULL)
    {
      printf("Error to calloc user\n");
      exit(0);
    }
    memset(productID,'\0',sizeof(productID));
    memset(productName,'\0',sizeof(productName));
    memset(description,'\0',sizeof(description));
    memset(startPrice,'\0',sizeof(startPrice));
    memset(buyOffPrice,'\0',sizeof(buyOffPrice));
    memset(startDay,'\0',sizeof(startDay));
    memset(startMonth,'\0',sizeof(startMonth));
    memset(startYear,'\0',sizeof(startYear));
    memset(endDay,'\0',sizeof(endDay));
    memset(endMonth,'\0',sizeof(endMonth));
    memset(endYear,'\0',sizeof(endYear));
		memset(owner,'\0',sizeof(owner));
		memset(returnMoney,'\0',sizeof(returnMoney));
		memset(countHistory,'\0',sizeof(countHistory));
    sscanf(input,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]"
                  ,productID,productName,description,startPrice,buyOffPrice
                  ,startDay,startMonth,startYear
                  ,endDay,endMonth,endYear
                  ,owner,returnMoney,countHistory);
    sscanf(startPrice, "%lf", &startPriceNum);
    sscanf(buyOffPrice, "%lf", &buyOffPriceNum);
    sscanf(startDay, "%d", &startDayNum);
    sscanf(startMonth, "%d", &startMonthNum);
    sscanf(startYear, "%d", &startYearNum);
    sscanf(endDay, "%d", &endDayNum);
    sscanf(endMonth, "%d", &endMonthNum);
    sscanf(endYear, "%d", &endYearNum);	
		sscanf(returnMoney, "%d", &returnMoneyStatas);
    sscanf(countHistory, "%d", &countHistoryNum);

    strcpy(productEntry->productID,productID);
    strcpy(productEntry->productName,productName);
    strcpy(productEntry->description,description);
    productEntry->startPrice = startPriceNum;
    productEntry->buyOffPrice = buyOffPriceNum;
    productEntry->startDay = startDayNum;
    productEntry->startMonth = startMonthNum;
    productEntry->startYear = startYearNum;
    productEntry->endDay = endDayNum;
    productEntry->endMonth = endMonthNum;
    productEntry->endYear = endYearNum;
		productEntry->owner = hashTableUserLookup(owner);
		productEntry->returnMoney = returnMoneyStatas;
		productEntry->biddingAmount = countHistoryNum;
		
    for(i = 0 ; i < countHistoryNum ; i++)
    {
      bidEntry = calloc(1,sizeof(BID_T));
      fgets(input,sizeof(input),pIn);
      sscanf(input,"%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]"
                  ,username,amount,bidDay,bidMonth,bidYear);
      sscanf(amount, "%lf", &amountNum);
      sscanf(bidDay, "%d", &bidDayNum);
      sscanf(bidMonth, "%d", &bidMonthNum);
      sscanf(bidYear, "%d", &bidYearNum);
      userBid = hashTableUserLookup(username);
      bidEntry->buyer = userBid;
      strcpy(bidEntry->usernameBid,username);
      bidEntry->amount = amountNum;
      bidEntry->bidDay = bidDayNum;
      bidEntry->bidMonth = bidMonthNum;
      bidEntry->bidYear = bidYearNum;
      bidEntry->pNext = NULL;

      if(productEntry->history == NULL)
      {
        productEntry->history = bidEntry;
      }
      else
      {
        pHeadBid = productEntry->history;
        while(pHeadBid->pNext != NULL)
        {
          pHeadBid = pHeadBid->pNext;
        }
        pHeadBid->pNext = bidEntry;
      }
    }
    if(strcmp(pHead->productName,"\0") == 0)
    {
      strcpy(pHead->productName,productName);
    }
    else
    {
      pCurrent = pHead;
      keyProduct = calloc(1,sizeof(ALLUSER_T));
      if(keyProduct == NULL)
      {
        printf("Error to calloc key product\n");
        exit(0);
      }
      strcpy(keyProduct->productName,productName);
      keyProduct->pNext = NULL;
      while(pCurrent->pNext != NULL)
      {
        pCurrent = pCurrent->pNext;
      }
      pCurrent->pNext = keyProduct;
    }
		if ((productEntry->returnMoney == 0) && (checkFuture(productEntry->endDay, productEntry->endMonth, productEntry->endYear) == 0))
		{
			if (productEntry->history != NULL)
			{
				productEntry->owner->balance += productEntry->history->amount;
			}
      productEntry->returnMoney = 1;
		}

    hashTableProductInsert(productName, productEntry, &pCollision);
		createBinaryNode(productEntry);
    count++;
    countAllProduct++;
  }
  fclose(pIn);
  return countAllProduct;
}