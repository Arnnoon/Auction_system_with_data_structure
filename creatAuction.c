/*********************************************************************
 *
 *  creatAuction.c
 *
 *  This program will create new product in AuctionSystem.
 *  New product will have all detail to input to database
 *  After finish this program file database is not change 
 *  but data in structure will add new product
 *
 *********************************************************************
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "abstractHashTableUser.h"
#include "abstractHashTableProduct.h"
#include "abstractSortBinary.h"
#include "AuctionSystem.h"

/*  [****PRIVATE FUNCTION****]
 *  main idea is generate product id Ex. 000000001, 000125351
 *  Arguments: productID - update product id before generate 
 *             countAllProduct - sum of product in database
 *  Returns : not return
*/
void createID(char id[],int countAll)
{
  int dummy;      /*dummy variable to generate id*/
  int i = 0;      /*loop counter variable*/
  char character; /*variable to keep integer that change to character*/
  countAll++;
  dummy = floor(countAll/100000000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*100000000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/10000000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*10000000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/1000000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*1000000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/100000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*100000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/10000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*10000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/1000);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*1000;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/100);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*100;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/10);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*10;
  }
  else
  {
    id[i] = '0';
  }
  i++;
  dummy = floor(countAll/1);
  if(dummy > 0)
  {
    character = (int)(48+dummy);
    id[i] = character;
    countAll -= dummy*1;
  }
  else
  {
    id[i] = '0';
  }
}

/*  [****PUBLIC FUNCTION****]
 *  main idea is add new product to data in structure.
 *  fucntion will validate all detail about that product before add to data in structure.
 *  Arguments: allProductName - all key product in database  
 *             countAllProduct - sum of product in database
 *  Returns : 1 - creat complete
 *            0 - create fail
*/
int creatAuction(ALLPRODUCT_T *pHeadProduct,int countAllProduct, char usernameLogin[])
{
  int i = 0;                                    /*loop counter variable*/
  int bOK = 0;                                  /*variable check that pass some condition*/
  char input[1024];                             /*input from user*/
  //Zone product
  PRODUCT_T *productEntry;                    /*variable to keep data of product*/
  char productID[32];                         /*datail product about product ID*/
  char productName[32];                       /*datail product about product name*/
  char description[256];                      /*datail product about product description*/
  char startPrice[32], buyOffPrice[32];       /*datail product about product ID*/
  char startDay[3],startMonth[4],startYear[5];/*datail product about start date*/
  char endDay[3], endMonth[4], endYear[5];    /*datail product about end date*/
  char countHistory[10];                      /*keep history count for that product*/
  double startPriceNum, buyOffPriceNum;       /*keep start price in integer form*/
  int startDayNum, startMonthNum,startYearNum;/*keep start date in integer form*/
  int endDayNum, endMonthNum, endYearNum;     /*keep end date in integer form*/
  int countHistoryNum = 0;                    /*keep history count in integer form*/
  //Zone bid
  char username[30];                        /*user name user that bid*/                 
  char amount[30];                          /*datail amount that user bid*/
  char bidDay[3], bidMonth[4], bidYear[5];  /*the day, month and year that user bid*/
  double amountNum;                         /*keep amount in integer form*/
  int bidDayNum, bidMonthNum, bidYearNum;   /*the day, month and year that in integer form*/
  int pCollision;                           /* dummy variable*/
  ALLPRODUCT_T * pCurrent;                  /* variable keep data at that time*/
  ALLPRODUCT_T * keyProduct;                /* variable keep key data at that time*/

  productEntry = calloc(1,sizeof(PRODUCT_T));
  memset(productID,'\0',sizeof(productID));
  createID(productID, countAllProduct);
  printf("\t\t>> Creat auction product menu <<\n\n");
	printf("These are rules of each data:\n");
	printf("Product name:\t\t\tmust be alphabet and not more than 30 characters\n");	
	printf("Product description:\tmust not more than 250 characters\n");
	printf("Start Price:\t\t\tmust be number with no comma(,)\n");
	printf("Buy off Price:\t\t\tmust be number with no comma(,)\n");
	printf("Start date:\t\t\t\tmust be number and slash(/) only and follow this form\n");
	printf("\t\t\t\t\t\tDD/MM/YYYY\n");
	printf("End date:\t\t\t\tmust be number and slash(/) only and follow this form\n");
	printf("\t\t\t\t\t\tDD/MM/YYYY\n");
  printf("Please type your detail\n");
  printf(">>Your product ID:%s\n\n",productID);

  bOK = 0;
  while(bOK == 0)
  {
    printf("->Product Name:");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%[^\n]",productName);
    if(strlen(productName) > 30)
    {
      printf("Please enter product name not more than 30 letters(Now is %ld letters)\n"
              ,strlen(productName));
      continue;
    }
    if(hashTableProductLookup(productName) != NULL)
    {
      printf("This product name has in database, please enter anouther name\n");
      continue;
    }
    if(checkAllAlpha(productName) == 0)
    {
      printf("Product name must have only alphabet\n");
      continue;
    }
    bOK = 1;
  }
  bOK = 0;
  while(bOK == 0)
  {
    printf("->Product description(not more than 250 letters):");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%[^\n]",description);
    if(strlen(description) > 250)
    {
      printf("Please enter description not more than 250 letters(Now is %ld letters)\n"
              ,strlen(description));
      continue;
    }
    bOK = 1;
  }
  bOK = 0;
  while(bOK == 0)
  {
    printf("->Start Price(not enter ','):");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%s",startPrice);
    if(checkAllDigit(startPrice) == 0)
    {
      printf("start price must all digit\n");
      continue;
    }
    sscanf(startPrice,"%lf",&startPriceNum);
    if(startPriceNum > 100000000)
    {
      printf("Please enter start price not more than 100,000,000 Bath\n");
      continue;
    }
    bOK = 1;
  }
  bOK = 0;
  while(bOK == 0)
  {
    printf("->Buy off Price(not enter ','):");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%s",buyOffPrice);
    if(checkAllDigit(buyOffPrice) == 0)
    {
      printf("buy off price must all digit\n");
      continue;
    }
    sscanf(buyOffPrice,"%lf",&buyOffPriceNum);
    if(buyOffPriceNum > 100000000)
    {
      printf("Please enter buy off price not more than 100,000,000 Bath\n");
      continue;
    }
    if(buyOffPriceNum < startPriceNum)
    {
      printf("Buy of price must more than start price\n");
      continue;
    }
    bOK = 1;
  }

  bOK = 0;
  while(bOK == 0)
  {
    printf("->Start date (DD/MM/YYYY Ex. 31/01/2021):");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%[^\n]",input);
    if(checkDayForm(input) == 0)
    {
      printf("Wrong date form\n");
      continue;
    }
    sscanf(input, "%[^/]/%[^/]/%[^\n]",startDay,startMonth,startYear);
    sscanf(startDay, "%d",&startDayNum);
    sscanf(startMonth, "%d",&startMonthNum);
    sscanf(startYear, "%d",&startYearNum);
    if(validDate(startDayNum, startMonthNum, startYearNum) == 0)
    {
      printf("Not have this day\n");
      continue;
    }
    if(checkFuture(startDayNum, startMonthNum, startYearNum) == 0)
    {
      printf("Date must not in past\n");
      continue;
    }
    bOK = 1;
  }  

  bOK = 0;
  while(bOK == 0)
  {
    printf("->End date (DD/MM/YYYY Ex. 31/01/2021):");
    fgets(input,sizeof(input), stdin);
    sscanf(input,"%[^\n]",input);
    if(checkDayForm(input) == 0)
    {
      printf("Wrong date form\n");
      continue;
    }
    sscanf(input, "%[^/]/%[^/]/%[^\n]",endDay,endMonth,endYear);
    sscanf(endDay, "%d",&endDayNum);
    sscanf(endMonth, "%d",&endMonthNum);
    sscanf(endYear, "%d",&endYearNum);
    if(validDate(endDayNum, endMonthNum, endYearNum) == 0)
    {
      printf("Not have this day\n");
      continue;
    }
    if(checkFuture(endDayNum, endMonthNum, endYearNum) == 0)
    {
      printf("Date must not in past\n");
      continue;
    }
    if((startDayNum==endDayNum) && 
        (startMonthNum==endMonthNum) && 
        (startYearNum==endYearNum))
    {
      printf("End date must not is start date\n");
      continue;
    }
    if(compareDate(startDayNum, startMonthNum, startYearNum, endDayNum, endMonthNum, endYearNum) == 1)
    {
      printf("End date must laster than start date\n");
      continue;
    }
    
    bOK = 1;
  }
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
	productEntry->biddingAmount = countHistoryNum;
	productEntry->owner = hashTableUserLookup(usernameLogin);
	productEntry->returnMoney = 0;
  hashTableProductInsert(productName, productEntry, &pCollision);
	createBinaryNode(productEntry);
  if(strcmp(pHeadProduct->productName,"\0") == 0)
  {
    strcpy(pHeadProduct->productName,productName);
  }
  else
  {
    pCurrent = pHeadProduct;
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

	printf("\tSuccess create auction\n");
  countAllProduct++;
  return countAllProduct;
}
