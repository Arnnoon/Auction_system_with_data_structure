/******************************************************
 *  updateDataFileUser.c
 *
 *  This file will read data in structure at that time
 *  then open file and write all information of user to file user.txt
 *  so point in this file is update file at that time for real time database.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTableUser.h"
#include "AuctionSystem.h"

/*  [****PUBLIC FUNCTION****]
 *  Arguments: allUserName - key user for hashLookup
 *             countAllUser - sum of user in database
 *  Returns 1 if all update data complete
 *          0 if some of data can not updata or not found.
*/
int updateDataFileUser(ALLUSER_T *pHeadUser)
{
  FILE *pOut = NULL;    /*pointer variable to open file*/
  int i = 0;            /*loop counter variable*/
  USER_T *data;         /*variable to keep data of user*/
  int check = 1;        /*check variable that complete update file*/
  ALLUSER_T *pCurrent = pHeadUser;
  if(strcmp(pHeadUser->username,"\0") != 0)
  {
    pOut = fopen("user.txt","w");
    if(pOut == NULL)
    {
      printf("Error open %s file\n","user.txt");
      exit(0);
    }
    while(pCurrent != NULL)
    {
      data = hashTableUserLookup(pCurrent->username);
      if(data != NULL)
      {
        fprintf(pOut,"%s|%s|%s|%s|%s|%s|%.2lf\n"
                    ,data->userID
                    ,data->username
                    ,data->name
                    ,data->password
                    ,data->email
                    ,data->phoneNumber
                    ,data->balance);
      }
      else
      {
        printf("Not found this USER ID [%s]\n",pCurrent->username);
        check = 0;
      }
      pCurrent = pCurrent->pNext;
    }
    fclose(pOut);
  }
  
  return check;
}