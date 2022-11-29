/*********************************************************************
 *
 *   logOut.c
 *
 *      This program check that the process of log out
 *  if it complete this program will end. 
 *
 *********************************************************************
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AuctionSystem.h"
#include "abstractHashTableProduct.h"
#include "abstractHashTableUser.h"
#include "abstractSortBinary.h"


/*  [****PUBLIC FUNCTION****]
 *  This function will log out from this program
 *  Arguments: no argument
 *  Returns : success logOut variable
 */
int logOut()
{
  int option = -1;       /*get option to do feature in AuctionSystem*/
  char input[32];       /*input from user*/
  char logout[32];      /*confirm log out*/

  while(1)
  {
    printf("->Are you sure to Log out?(Y or N) ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%s",logout);

    if (strcmp(logout,"Y") == 0)
    {
      option = 1;
			break;
    }
    else if (strcmp(logout,"N") == 0)
    {
      option = 0;
      break;
    }
    else
    {
      printf("\tPlease confirm by enter Y or N.\n\n");
    }
  }
  return option;
}
/*  [****PUBLIC FUNCTION****]
 *  This function is for user that's not log in that want to log out
 *  Arguments: no argument
 *  Returns : option success exit
 */
int exitProgram()
{
  int option = -1;
  char input[32];     /*input from user*/
  char exitPro[32];   /*confirm log out*/
	int i;
  while(1)
  {
    printf("->Are you sure to exit?(Y or N) ");
    fgets(input,32,stdin);
    sscanf(input,"%s",exitPro);
    if(strcmp(exitPro,"Y") == 0)
    {
      option = 1;
      break;
    }
    else if (strcmp(exitPro,"N") == 0)
    {
      option = 0;
      break;
    }
    else
    {
      printf("\tPlease confirm by enter Y or N.\n\n");
    }
  }
  return option;
}