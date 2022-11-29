/******************************************************
 *  updateDataFileProduct.c
 *
 *  This file will read data in structure at that time
 *  then open file and write all information of product to file product.txt
 *  so point in this file is update file at that time for real time database.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableUser.h"
#include "abstractHashTableProduct.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  Arguments: allProductName - key product for hashLookup
 *             countAllProduct - sum of product in database
 *  Returns 1 if all update data complete
 *          0 if some of data can not updata or not found.
*/
int updateDataFileProduct(ALLPRODUCT_T *pHeadProduct)
{
  FILE *pOut = NULL;      /*pointer variable to open file*/
  int i = 0;              /*loop counter variable*/
  PRODUCT_T *data;        /*variable to keep data of product*/
  BID_T *currentBid;      /*variable to keep data of history bid for each product*/
  int check = 1;          /*check variable that complete update file*/
  ALLPRODUCT_T *pCurrent = pHeadProduct;
  if(strcmp(pHeadProduct->productName,"\0") != 0)
  {
    pOut = fopen("product.txt","w");
    if(pOut == NULL)
    {
      printf("Error open %s file\n","product.txt");
      exit(0);
    }
    while(pCurrent != NULL)
    {
      data = hashTableProductLookup(pCurrent->productName);
      if(data != NULL)
      {
        fprintf(pOut,"%s|%s|%s|%.2lf|%.2lf|%.2d|%.2d|%.4d|%.2d|%.2d|%.4d|%s|%d|%d\n"
                    ,data->productID
                    ,data->productName
                    ,data->description
                    ,data->startPrice
                    ,data->buyOffPrice
                    ,data->startDay
                    ,data->startMonth
                    ,data->startYear
                    ,data->endDay
                    ,data->endMonth
                    ,data->endYear
										,data->owner->username
										,data->returnMoney
                    ,data->biddingAmount);
        currentBid = data->history;
        while(currentBid != NULL)
        {
          fprintf(pOut,"%s|%.2lf|%.2d|%.2d|%4d\n"
                      ,currentBid->usernameBid
                      ,currentBid->amount
                      ,currentBid->bidDay
                      ,currentBid->bidMonth
                      ,currentBid->bidYear);
          currentBid = currentBid->pNext;
        }
      }
      else
      {
        printf("Not found this USER ID [%s]\n",pCurrent->productName);
        check = 0;
      }
      pCurrent = pCurrent->pNext;
    }
    fclose(pOut);
  }
  return check;
}