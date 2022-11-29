/*********************************************************************
 *
 *  login.c
 *
 *  This program will validate username and password before use AuctionSystem
 *  You must input correct username and password
 *
 *********************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableUser.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data with username that user input
 *  then check that username has in database or not
 *  if have this username in data program will keep that data for check password
 *  if password is correct, you do function in AuctionSystem
 *  Arguments: usernameLogin - if login comple then update name of usernameLogin
 *  Returns : 1 - login complete
 *            0 - login fail.
 */
int loginOption(char *usernameLogin)
{
  int result = 0;           /*check variable for login complete or not*/
  char input[1024];         /*input from user*/
  char inputUsername[32];   /*keep username form user to check*/
  char inputPassword[32];   /*keep password form user to check*/
	USER_T * user;     				/*variable to keep data of user*/
  printf("\t\t>> Login Menu <<\n\n");
  printf("Type 'DONE' to exit\n");
	
  while(1)
  {
    printf("->Username: ");
		fgets(input,sizeof(input),stdin);
    sscanf(input,"%s",inputUsername);
    if(strncmp(input,"DONE",4) == 0)
    {
      result = -1;
      break;
    }
		user = hashTableUserLookup(inputUsername);
    if (user == NULL)
    {
      printf("\tInvalid username\n");
      continue;
    }
    else
      break;
  }
  if(result != -1)
  {
    while(1)
    {
      printf("->Password: ");
      fgets(input,sizeof(input),stdin);
      sscanf(input,"%s",inputPassword);
      if(strncmp(input,"DONE",4) == 0)
      {
        result = -1;
        break;
      }
      if (strcmp(user->password,inputPassword) == 0)
      {
        strcpy(usernameLogin, inputUsername);
        result = 1;
        break;
      }
      else
      {
        printf("\tinvalid password\n");
      }
    }
  }
  return result;
}
