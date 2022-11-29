/*********************************************************************
 *
 *   winner.c
 *
 *      This program will show display about winner bidding.
 *
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableProduct.h"
#include "AuctionSystem.h"

/** [****PRUBLIC FUNCTION****]
 *  This function will show display about winner bidding.
 *  Arguments: pHeadProduct - product to be printed at the end of the auction
 *  Returns: Not return
 */
void showWinner(ALLPRODUCT_T *pHeadProduct)
{
  PRODUCT_T *data;      /* variable to keep data of product */
  USER_T *user;         /* variable to keep data of user */
  BID_T *currentBid;    /* variable to keep data of bid */
  ALLPRODUCT_T *pCurrent = pHeadProduct;    /* variable to keep current data of current product */
  while(pCurrent != NULL)
  {
    data = hashTableProductLookup(pCurrent->productName);
    if(checkFuture(data->endDay, data->endMonth,data->endYear)==0)
    {
      currentBid = data->history;
			printf("These is all auction that ended:\n\n");
      printf("\n------------------------------------------\n");
      printf("Product ID: %s\n",data->productID);
      printf("Product Name: %s\n",data->productName);
      printf("Description:  %s\n",data->description);
      printf("StartPrice:   %.2lf\n",data->startPrice);
      printf("BuyOffPrice:  %.2lf\n",data->buyOffPrice);
      printf("Start: %.2d / %.2d / %.4d\n",data->startDay,data->startMonth,data->startYear);
      printf("End:   %.2d / %.2d / %.4d\n",data->endDay,data->endMonth,data->endYear);
      if(data->history != NULL)
      {
        printf("<<<<<<< The winner >>>>>> ----> %s(%.2lf Bath)\n",currentBid->buyer->username,currentBid->amount);
      }
      else
      {
        printf("<<<<<<< Not have winner >>>>>>\n");
      }
      printf("------------------------------------------\n");
    }
    pCurrent = pCurrent->pNext;
  }
}