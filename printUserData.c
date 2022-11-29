/*********************************************************************
 *
 *   printUserData.c
 *
 *      This program print information about the user for example,
 *  print their user ID and print error if do not find that user 
 *  read from structure. 
 *
 *********************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableUser.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data some people in database
 *  then print all data of that people
 *  Arguments: username
 *  Returns : not have return
 */
void printUserData(char *username)
{
  char input[64];               /*input from user*/
  USER_T *data;                 /*variable to keep data of user*/
  data = hashTableUserLookup(username);
  if(data != NULL)
  {
    printf("------------------------------------------\n");
    printf("User ID: %s\n",data->userID);
    printf("User name: %s\n",data->username);
    printf("Name: %s\n",data->name);
    printf("Password: %s\n",data->password);
    printf("Email: %s\n",data->email);
    printf("PhoneNumber: %s\n",data->phoneNumber);
    printf("Money: %.2lf\n",data->balance);
  }
  else
  {
    printf("Not found this USER Name\n");
  }
}