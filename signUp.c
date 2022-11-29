/******************************************************
 *  signUp.c
 *
 *  This file for create new user in database
 *  main ideal in this file is valadate data of new user
 *  before create to database
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AuctionSystem.h"
#include "abstractHashTableUser.h"

/*  [****PUBLIC FUNCTION****]
 *  Arguments: usernameLogin - for update username login 
                              that time if sign up complete
 *  Returns 1 if signUp complete
 *          0 if signUp fail
 */
int signUpMenu(ALLUSER_T *pHeadUser, int countAllUser, char *usernameLogin)
{
  char input[256];
  int pCollision;              /*dummy variable*/
  USER_T* userEntry = NULL;
	int bOk = 0;                /* free the old table, if any */
  char userID[20];
  char username[32];
	char name[32];
  char password[32];
  char email[32];
  char phoneNumber[16];
  double balance;
	int blackList;
  ALLUSER_T *pCurrent;
  ALLUSER_T *keyUser;
  memset(userID,'\0',sizeof(userID));
  createID(userID, countAllUser-1);
	userEntry = calloc(1,sizeof(USER_T));
	if(userEntry == NULL)
	{
		printf("error allocate memory for pSignUp\n");
		exit(0);
	}

  printf("\t\t>> Sign Up Menu <<\n\n");
	printf("These are rules of each data\n");
	printf("Username:\t\tmust not have special character and not more than 30 characters\n");	
	printf("Password:\t\tmust be 8-16 characters long and have at least 1 uppercase,\n");
	printf("Name:\t\t\tmust be all alphabet and not more than 30 characters\n");
	printf("\t\t\t\t1 lowwercase, 1number, 1 special character\n");
	printf("Phonenumber:\tmust be 10 characters long and be all number with no dash(-)\n\n");

	while(bOk == 0)
  {
    printf("->Enter username: ");
		fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%[^\n]",username);
	  if (checkSomeSpecial(username) == 1)
    {
      printf("\tUsername must be alphabet or number\n");
      continue;
    }
    if(hashTableUserLookup(username) != NULL)
    {
      printf("\tSorry, this username have used\n");
      continue;
    }
    if(strlen(username)>30)
    {
      printf("\tUsername must not more than 30 characters.\n");
      continue;
    }
    bOk = 1;
  }
  bOk = 0;
  
  while(bOk == 0)
  {
    printf("->Enter Name: ");
	 	fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%[^\n]",name);
    if (checkAllAlpha(name) == 0)
    {
      printf("\tName must all alphabet\n");
      continue;
    }
    if(strlen(name)>30)
    {
      printf("\tName not more than 30 characters.\n");
      continue;
    }
    bOk = 1;
  }
  bOk = 0;
  while(bOk == 0)
  {
    printf("->Enter Password: ");
	 	fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%[^\n]",password);
    if (checkPassword(password) == 0)
    {
      printf("\tPassword must have upper, lower and special character\n");
      continue;
    }
    bOk = 1;
  }

  bOk = 0;
	while(bOk == 0)
  {
    printf("->Enter Email: ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%[^\n]",email);
    if (checkEmail(email) == 0)
    {
      printf("\tYour email is wrong!\n");
      continue;
    }
    bOk = 1;
  }
	bOk = 0;
  while(bOk == 0)
  {
    printf("->Enter PhoneNumber: ");
	  fgets(input,sizeof(input),stdin);
	  sscanf(input,"%[^\n]",phoneNumber);
    if(checkPhoneNumber(phoneNumber) == 0)
    {
      continue;
    }
    bOk = 1;
  }
  strcpy(userEntry->userID,userID);
  strcpy(userEntry->username,username);
  strcpy(userEntry->name,name);
  strcpy(userEntry->password,password);
  strcpy(userEntry->email,email);
  strcpy(userEntry->phoneNumber,phoneNumber);
  userEntry->balance = 0;
  if(strcmp(pHeadUser->username,"\0") == 0)
  {
    strcpy(pHeadUser->username,username);
  }
  else
  {
    pCurrent = pHeadUser;
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
  countAllUser++;
  strcpy(usernameLogin, username);
  return countAllUser;
}