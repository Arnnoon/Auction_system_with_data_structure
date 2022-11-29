/*********************************************************************
 *
 *   addMoney.c
 *
 *      This program will add money that user input in this program
 *
 *********************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuctionSystem.h"
#include "abstractHashTableUser.h"

/*  [****PUBLIC FUNCTION****]
 *  This function add user's money
 *  Arguments: username that login
 *  Returns : not have return
 */
void addMoney(char *usernameLogin)
{
  char input[32];                   /* input from user*/
  double moneyInput = 0;            /* money in integer form*/
  USER_T * currentUser = NULL;      /* variable to keep data of user */
  printf("\t\t>> Add money Menu <<\n\n");
  printf("->Enter money: ");
  //check validate
  fgets(input, sizeof(input), stdin);
  sscanf(input, "%lf",&moneyInput);
  currentUser = hashTableUserLookup(usernameLogin);
  currentUser->balance += moneyInput;
	printf("\tsuccess adding money\n");
}