/*********************************************************************
 *
 *   buildUser.c
 *
 *  This program will create structure user like 
 *  hash table from our database and then read file from structure. 
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
 *  This function will open file and then read user file
 *  each line put the information in structure.
 *  Arguments: pHead of ALLUSER_T, countAllUser
 *  Returns : countAllUser
 */
int buildUser(ALLUSER_T *pHead,int countAllUser)
{
  FILE *pIn = NULL;            /*pointer variable to open file*/   
  int i = 0;                   /*loop counter variable*/
  char input[1024];            /*input from file*/
  char userID[20];             /*datail user about product ID*/
  char username[32];           /*datail user about user name*/
  char name[32];               /*datail user about name*/
  char password[32];           /*datail user about password*/
  char email[32];              /*datail user about email*/
  char phoneNumber[16];        /*datail user about phone number*/
  char money[20];              /*datail user about money*/
  double numMoney;             /*money in integer form*/
  USER_T *userEntry;           /*variable to keep data of user*/
  ALLUSER_T *keyUser;          /*variable to key data of user*/
  ALLUSER_T *pCurrent;         /*variable to key data of user at that time*/
  int count = 0;               /*loop counter variable*/
  int pCollision;              /*dummy variable*/
  pIn = fopen("user.txt","r");
  if(pIn == NULL)
  {
    printf("Error open %s file\n","user.txt");
    exit(0);
  }
  while (fgets(input,sizeof(input),pIn)!=NULL)
  {
    memset(userID,'\0',sizeof(userID));
    memset(username,'\0',sizeof(username));
    memset(name,'\0',sizeof(name));
    memset(password,'\0',sizeof(password));
    memset(email,'\0',sizeof(email));
    memset(phoneNumber,'\0',sizeof(phoneNumber));
    memset(money,'\0',sizeof(money));
    sscanf(input,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]"
                  ,userID,username,name,password,email,phoneNumber,money);
    sscanf(money, "%lf", &numMoney);
    userEntry = calloc(1,sizeof(USER_T));
    if(userEntry == NULL)
    {
      printf("Error to calloc user\n");
      exit(0);
    }
    strcpy(userEntry->userID,userID);
    strcpy(userEntry->username,username);
    strcpy(userEntry->name,name);
    strcpy(userEntry->password,password);
    strcpy(userEntry->email,email);
    strcpy(userEntry->phoneNumber,phoneNumber);
    userEntry->balance = numMoney;
    if(strcmp(pHead->username,"\0") == 0)
    {
      strcpy(pHead->username,username);
    }
    else
    {
      pCurrent = pHead;
      keyUser = calloc(1,sizeof(ALLUSER_T));
      strcpy(keyUser->username, username);
      keyUser->pNext = NULL;
      if(keyUser == NULL)
      {
        printf("Error to calloc key user\n");
        exit(0);
      }
      while(pCurrent->pNext != NULL)
      {
        pCurrent = pCurrent->pNext;
      }
      pCurrent->pNext = keyUser;
    }
    hashTableUserInsert(username, userEntry, &pCollision);
    count++;
    countAllUser++;
  }
  fclose(pIn);
  return countAllUser;
}