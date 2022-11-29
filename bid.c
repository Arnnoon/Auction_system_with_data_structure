/*********************************************************************
 *
 *   bid.c
 *
 *      This program will show display when user start bidding,
 * show top price and current price bid. Owner doesn't use in this
 * this program.
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableProduct.h"
#include "abstractHashTableUser.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  This function use for user bidding
 *  Arguments: username
 *  Returns : bOk(success bid)
 */
int bidProduct(char *username)
{
  PRODUCT_T *data;        /* variable to keep data of product */
  USER_T *user;           /* variable to keep data of user */
  BID_T *newBid;          /* variable to keep new user bid */
	BID_T *currentBid;      /* variable to keep data of history bid for each product */
  int bOk = 0;            /* check success variable*/
  char input[64];         /* input form user */
  double topPrice  = 0;   /* variable for get top bid price*/
  double buyOffPrice = 0; /* variable for get buy off price */
  double startPrice = 0;  /* variable for get start product price*/
  double bidding = 0;     /* variable for get price of user bid */
  int dayToday;           /* day that keep bid date */
  int monthToday;         /* month that keep bid date */
  int yearToday;          /* year that keep bid date*/
  int end = 0;			  /* varible to check that this product has already buy off or not (1 is already sold, 0 is not yet sold)*/
	printf("\t\t>> Bid product menu <<\n\n");
  dateToday(&dayToday, &monthToday, &yearToday);
  printf("->Enter Product: ");
  fgets(input, sizeof(input), stdin);
  sscanf(input, "%[^\n]",input);
	data = hashTableProductLookup(input);
  user = hashTableUserLookup(username);
	if(data != NULL)
  {
    printf("------------------------------------------\n");
    printf("Product ID: %s\n",data->productID);
    printf("Product Name: %s\n",data->productName);
    printf("Description:  %s\n",data->description);
    printf("StartPrice:   %.2lf\n",data->startPrice);
    if(data->history != NULL)
    {
      printf("Current price:   %.2lf\n",data->history->amount);
    }
    else
    {
      printf("Current price:   %.2lf\n",data->startPrice);
    }
    printf("BuyOffPrice:  %.2lf\n",data->buyOffPrice);
    if(data->history != NULL)
      printf("Top price:  %.2lf\n",data->history->amount);
    else
      printf("Top price:  %.2lf\n",0.00);
    printf("Start: %.2d / %.2d / %.2d\n",data->startDay,data->startMonth,data->startYear);
    printf("End:   %.2d / %.2d / %.2d\n",data->endDay,data->endMonth,data->endYear);
    printf("*******************************************\n");

    buyOffPrice = data->buyOffPrice;
    if(data->history != NULL)
      topPrice = data->history->amount;
    else
      topPrice = 0;
    startPrice = data->startPrice;

		if (strcmp(user->username,data->owner->username) == 0)
		{
			printf("\tThe owner can't bid your auction\n");
		}
    else if((checkFuture(data->startDay, data->startMonth,data->startYear)==1)&&
    !(data->startDay == dayToday && data->startMonth == monthToday &&
    data->startYear == yearToday))
    {
      printf("\tSorry start time to bid is in future\n");
    }
    else if(checkFuture(data->endDay, data->endMonth,data->endYear)==0)
    {
      printf("\tSorry times up to bid this product\n");
    }
    else
    {
	    printf("\n");
	    if(data->history != NULL)
	    {
	     	if(data->history->amount == data->buyOffPrice)
			{
				printf("\tThis product has already bought off\n");
				end = 1;
			}
	    }
		while(end != 1)
		{
			printf("->How much do you want to bid? (DONE to cancel) ");
			fgets(input, sizeof(input), stdin);
			sscanf(input, "%lf", &bidding);
			if(strncmp(input,"DONE",4) == 0)
			{
				break;
			}

			
			if((bidding<startPrice)||(bidding>buyOffPrice))
			{
				printf("\tPlease enter in scoop %.2lf(start price) - %.2lf(buy off price)\n",startPrice,buyOffPrice);
			}
			else if(bidding <= topPrice)
			{
				printf("\tPlease enter more than %.2lf(top price)\n",topPrice);
			}
			else if(bidding > user->balance)
			{
				printf("\tYou have not enought money(You have %.2lf)\n",user->balance);
			}
			else
			{
				data->biddingAmount += 1;
				if(data->history != NULL)
				{
					data->history->buyer->balance += data->history->amount;
				}
				newBid = calloc(1, sizeof(BID_T));
				user->balance -= bidding;
				newBid->buyer = user;
				strcpy(newBid->usernameBid, user->username);
				newBid->amount = bidding;
				newBid->bidDay = dayToday;
				newBid->bidMonth = monthToday;
				newBid->bidYear = yearToday;
				if(data->history != NULL)
				{
					newBid->pNext = data->history;
				}
				else
				{
					newBid->pNext = NULL;
				}
				data->history = newBid;
				bOk = 1;
				printf("\tSuccess Bidding\n");
				break;
			}
		}
    }
  }
  else
  {
    printf("\tNot have this product name in data\n");
  }
  return bOk;
}