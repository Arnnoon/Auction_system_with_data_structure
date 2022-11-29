/*********************************************************************
 *
 *   validate.c
 *
 *      This program validate many type of information that user
 *  input to this program for example username, phone number etc.
 *
 *
 *********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "AuctionSystem.h"

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string is all digits.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkAllDigit(char *stringToCheck)
{
	int result = 1;						/* Resuit value after checking */
	int i = 0;				        /* Loop controller */

	/* Loop to check the stringLength */
	for (i = 0; i < strlen(stringToCheck); i++)
	{
		/* Check digit,when it found non-digit character and set result = 0 then return and stop*/
		if (!isdigit(stringToCheck[i]))
		{
			result = 0;
			break;
		}
	}
	return result;
}

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string is all alphabet.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkAllAlpha(char *stringToCheck)
{
  int i = 0;                      /* Loop controller */
  int result = 1;						      /* Resuit value after checking */
  /* Loop to check the stringLength */
  for ( i = 0; i < strlen(stringToCheck); i++)
  {
    /* Check alphabet,when it found non-alphabet will set result = 0 then return and stop*/
    if (!isalpha(stringToCheck[i]))
    {
      result = 0;
      break;
    }
  }
  return result;
}

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have Uppercase.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeUpper(char *stringToCheck)
{
  int i = 0;                      /* Loop controller */
  int result = 0;						      /* Resuit value after checking */
  /* Loop to check the stringLength */
  for ( i = 0; i < strlen(stringToCheck); i++)
  {
    if (isupper(stringToCheck[i]))
    {
      result = 1;
    }
  }
  return result;
}

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have Lowercase.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeLower(char *stringToCheck)
{
  int i = 0;                      /* Loop controller */
  int result = 0;						      /* Resuit value after checking */
  /* Loop to check the stringLength */
  for ( i = 0; i < strlen(stringToCheck); i++)
  {
    /* Check to string must be have some alphabet,when it found some alphabet will set result = 1 then return*/
    if (islower(stringToCheck[i]))
    {
      result = 1;
    }
  }
  return result;
}

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have special character.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeSpecial(char *stringToCheck)
{
  int i = 0;                      /* Loop controller */
  int result = 0;						      /* Resuit value after checking */
  /* Loop to check the stringLength */
  for ( i = 0; i < strlen(stringToCheck); i++)
  {
    /* Check to string must be have some special character,when it found some special character will set result = 1 then return*/
    if (ispunct(stringToCheck[i]))
    {
      result = 1;
    }
  }
  return result;
}

//////////////////////////////////
/*ZONE Validate email address*/

/**  [****PRIVATE FUNCTION****]
 *   checkAlphabet function.
 *   This function get string that alphabet or not.
 *   This function check day valid or not.
 *   Check about
 *       - All alphabet character?
 *   return about type
 *       - 0 is invalid
 *       - 1 is valid
 */
int checkAlphabet(char string[])
{
  int check = 1; /*mark variable 0 is invalid, 1 is valid*/
  int i = 0; /*loop counter variable*/
  /* Loop to check the stringLength */
  for(i = 0; i < strlen(string); i++)
  {
    /* Check to string must be have all alphabet,when it found non-all alphabet will set result = 0 then return*/
    if(!isupper(string[i]) && !islower(string[i]))
      check = 0; /*invalid*/
  }
  return check;
}

/**  [****PRIVATE FUNCTION****]
 *   locateSign function.
 *   This function get string and sign to search.
 *   Check about
 *       - find location of sign in string.
 *   return location of sign
 */
int locateSign(char string[], char sign)
{
  int location = 0; /*keep the index in array of assign*/
  int i = 0; /*loop counter variable*/
  /* Loop to check the stringLength */
  for(i = 0; i < strlen(string); i++)
  {
    if(string[i] == sign)
      location = i;
  }
  return location;
}

/**  [****PRIVATE FUNCTION****]
 *   locateSign function.
 *   This function get string to search TLD.
 *   This function cut every string by '.' to check.
 *   Check about
 *       - find location of TLD(.co.th, .com etc) in string.
 *   return location of TLD
 */
int locateTLD(char string[])
{
  int location = -1; /*keep the index in array of assign*/
  int i = 0; /*loop counter variable*/
  int j = 0; /*loop counter variable*/
  char stringCheck[100] ; /*string check is TLD or not*/
  /*set stringTocheck = 0*/
  memset(stringCheck,'\0',sizeof(stringCheck));
  /* Loop to check the stringLength */
  for(i = 0; i < strlen(string); i++)
  {
    if(string[i] == '.')
    {
      memset(stringCheck,'\0',sizeof(stringCheck));
      for(j=i;j < strlen(string); j++)
      {
        stringCheck[j-i] = string[j];
      }
      if((strcmp(stringCheck, ".com")==0)||(strcmp(stringCheck, ".net")==0)||(strcmp(stringCheck, ".ac.th")==0)||(strcmp(stringCheck, ".co.th")==0))
        location = i;
    }
  }
  return location;
}

/**  [****PRIVATE FUNCTION****]
 *   findAlphanumericEmail function.
 *   This function get string.
 *   This function check between '@' and TLD is alphanumeric or not.
 *   Check about
 *       - between '@' and TLD is alphanumeric?
 *   This function use another function
 *       - locateSign
 *       - locateTLD
 *   return about type
 *       - 0 is invalid
 *       - 1 is valid
 */
int findAlphanumericEmail(char email[])
{
  int check = 0; /*mark variable 0 is invalid, 1 is valid*/
  int i = 0; /*loop counter variable*/

  for(i = locateSign(email,'@')+1; i < locateTLD(email) ; i++)
  {
    if(isupper(email[i]) || islower(email[i]) || isdigit(email[i]))
      check = 1; /*valid*/
  }
  return check;
}

/**  [****PRIVATE FUNCTION****]
 *   checkCharacter function.
 *   This function get string that alphabet and special character or not.
 *   Check about
 *       - All alphabet character and special character ( a-z , A-Z , 0-9 , @ , . , _ , - )?
 *   return about type of valid character
 *       - 0 is invalid
 *       - 1 is valid
 */
int checkCharacter(char string[])
{
  int check = 1; /*mark variable 0 is invalid, 1 is valid*/
  int i = 0; /*loop counter variable*/

  for(i = 0; i < strlen(string); i++)
  {
    if(!isupper(string[i]) && !islower(string[i]) && !isdigit(string[i]) && !(string[i]=='@') && !(string[i]=='.') && !(string[i]=='_') && !(string[i]=='-'))
      check = 0; /*invalid*/
  }
  return check;
}

/**  [****PRIVATE FUNCTION****]
 *   countAtsign function.
 *   This function get string and count '@' in this string.
 *   Check about
 *       - loop for count '@'.
 *   return about count of '@'
 */
int countAtsign(char string[])
{
  int count = 0; /*count the at-sign(@)*/
  int i = 0; /*loop counter variable*/

  for(i = 0; i < strlen(string); i++)
  {
    if(string[i] == '@')
      count++ ;
  }
  return count;
}

/**  [****PRIVATE FUNCTION****]
 *   checkPeriodsAtsign function.
 *   This function get string.
 *   Check about
 *       - period together with '@'?
 *   return about type
 *       - 0 is invalid
 *       - 1 is valid
 */
int checkPeriodsAtsign(char string[])
{
  int check = 1; /*mark variable 0 is invalid, 1 is valid*/
  int i = 0; /*loop counter variable*/
  for(i = 0; i<(strlen(string)-1); i++)
  {
    if(((string[i]=='.')&&(string[i+1]=='@')) || ((string[i+1]=='.')&&(string[i]=='@')))
      check = 0;
  }
  return check;
}

/* [****PUBLIC FUNCTION****]
 * This function check that email valid form or not.
 * Return the checking result: 0 is false, 1 is true
 */
int checkEmail(char *email)
{
  int mark = 1; /*mark variable 0 is invalid, 1 is valid*/
  int i = 0; /*loop counter variable*/

  mark = 1;
  mark = checkCharacter(email);
  if(mark != 0)
  {
    if(!isupper(email[0]) && !islower(email[0]) && !isdigit(email[0]))
      printf("\t\tInvalid, must begin with letter or digit character.\n");
    else if(countAtsign(email)!=1)
      printf("\t\tInvalid, '@' must have one character.\n");
    else if(locateTLD(email)==-1)
      printf("\t\tInvalid, wrong TLD.\n");
    else if(checkPeriodsAtsign(email)==0)
      printf("\t\tInvalid, periods together the '@'.\n");
    else if(findAlphanumericEmail(email)==0)
      printf("\t\tInvalid, must have alphanumeric character between the '@' and the TLD.\n");
    else
    {
      for(i = locateSign(email,'@')+1; i< strlen(email); i++)
      {
        if(email[i] == '_')
          mark = 0;
      }
      if(mark == 0)
        printf("\t\tInvalid, must not have underscores after the '@'.\n");
    }
  }
  return mark;
}

///////////////////////////////
/*ZONE Validate date*/

/**  [****PRIVATE FUNCTION****]
 *   checkYear function.
 *   This function check year valid or not.
 *   Check about
 *       - year are 4 digit?
 *       - year in scoop (1920 - 2120)?
 *       - leap year?
 *   return about type of year
 *       - 0 is invalid
 *       - 1 is valid but not leap year
 *       - 2 is 1 is valid and leap year
 */
int checkYear(int year)
{
  int check = 1;      /*mark variable 0 is invalid, 1 is valid*/
  int numYear = year; /*year in integer form*/

  if((numYear < 1920)&&(check != 0))
  {
    printf("\t\tInvalid, year is lower\n");
    check = 0;
  }
  else if((numYear > 2120)&&(check != 0))
  {
    printf("\t\tInvalid, year is higher\n");
    check = 0;
  }
  else if(check != 0) /*check leap year or not*/
  {
    if(numYear%4 != 0)
      check = 1;  /*not leap year*/
    else
      check = 2;  /*leap year*/
  }
  return check;
}

/**  [****PRIVATE FUNCTION****]
 *   checkMonth function.
 *   This function check month valid or not.
 *   Check about
 *       - month 3 upper character?
 *       - month valid?
 *       - year that 30 days?
 *       - year that 31 days?
 *       - year that 28/29 days
 *   return about type of month
 *       - 0 is invalid
 *       - 1 is valid 28/29 days
 *       - 2 is valid 30 days
 *       - 3 is valid 31 days
 */
int checkMonth(int month)
{
  int check = -1; /*mark variable 0 is invalid, 1 is valid 28/29 days, 2 is valid 30 days, 3 is valid 31 days*/
  int i = 0; /*loop counter variable*/

  if(check != 0)
  {
    if(month == 2)
      check = 1; /*valid 28/29 days*/
    if(month == 4||month == 6||month == 9||month == 11)
      check = 2; /*valid 30 days*/
    if(month == 1||month == 3||month == 5||month == 7||month == 8||month == 11||month == 12)
      check = 3; /*valid 31 days*/
  }
  if(check == -1)
  {
    printf("\t\tInvalid month form\n");
    check = 0;
  }
  return check;
}

/**  [****PRIVATE FUNCTION****]
 *   checkDay function.
 *   This function get type year, type month and calculate range day that valid or not.
 *   This function check day valid or not.
 *   Check about
 *       - day 2 digit character?
 *       - day valid(in scoop range day for each month and year)?
 *   return about type of day
 *       - 0 is invalid
 *       - 1 is valid
 */
int checkDay(int checkLeap, int typeMonth, int day)
{
  int numDay = day; /*day in integer form*/
  int check = 1; /*mark variable 1 is valid, 2 is invalid*/
  int rangeDay = 0; /*calculate range of that month and year*/

  if(typeMonth == 3)
    rangeDay = 31;
  else if(typeMonth == 2)
    rangeDay = 30;
  else if((typeMonth == 1)&&(checkLeap == 2))
    rangeDay = 29;
  else if((typeMonth == 1)&&(checkLeap == 1))
    rangeDay = 28;
  if((numDay > rangeDay )&&(check != 0))
  {
    printf("\t\tInvalid, day outside allowed range\n");
    check = 0;
  }
  return check;
}

/**  [****PUBLIC FUNCTION****]
 *   validDate function.
 *   This function check all day month year valid or not.
 *   Return the checking result: 0 is false, 1 is true
 */
int validDate(int day, int month, int year)
{
  int markYear;    /*mark year valid or not*/
  int markMonth;  /*mark month valid or not*/
  int markDay;    /*mark day valid or not*/
  int mark = 0;   /*mark variable 0 is invalid, 1 is valid*/

  markDay = 0;
  markYear = checkYear(year);
  markMonth = checkMonth(month);
  if((markYear!= 0)&&(markMonth!= 0))
    markDay = checkDay(checkYear(year), checkMonth(month), day);
  if(markDay == 1)
    mark = 1;
  return mark;
}
/**  [****PUBLIC FUNCTION****]
 *   validDate function.
 *   This function check day form valid or not. (Ex. 14/01/2021)
 *   Return the checking result: 0 is false, 1 is true
 */
int checkDayForm(char *stringToCheck)
{
  int i = 0;
  int check = 1;

  if(strlen(stringToCheck) != 10)
  {
    printf("Please type only 10 character\n");
    check = 0;
  }
  if(check == 1)
  {
    for(i = 0; i < strlen(stringToCheck); i++)
    {
      if(stringToCheck[i] != '/' && !isdigit(stringToCheck[i]))
      {
        check = 0;
      }
    }
  }
  if(check == 1)
  {
    if(stringToCheck[2] != '/' || stringToCheck[5] != '/')
    {
      printf("wrong location of '/'\n");
      check = 0;
    }
  }
  else
  {
    printf("Have wrong character plese type again\n");
  }
 return check;
}

/* [****PUBLIC FUNCTION****]
 *
 * 	This function check Password that must have 
 *  Uppercase Lowercase and Special character
 *  Return the checking result: 0 is false, 1 is true
*/
int checkPassword(char *password)
{
  int i = 0;                      /* Loop controller */
  int result = 1;						      /* Resuit value after checking */

  if ((strlen(password) < 8) || (strlen(password) > 16))
  {
    printf("\tPassword must be 8-16 characters long\n");
    result = 0;
  }
  else
  {
    if(checkSomeLower(password) == 0)
      result = 0;
    else if(checkSomeUpper(password) == 0)
      result = 0;
    else if(checkSomeSpecial(password) == 0)
      result = 0;
  }
  return result;
}

/* [****PRIVATE FUNCTION****]
 *  This function will check spacebar
*/
int checkPhoneSpace(char phoneInput[])
{
  int count = 0;			    /* check count value after checking */

  for(count = 0;count < strlen(phoneInput);count++)
  {
    if(phoneInput[count] == ' ')
    {
      return 0;
    }
  }
  return 1;
}

/*  [****PRIVATE FUNCTION****]
 *  This function will check Prefix
 *  if first two digits is 01 05 06 08 or 09 return 1 and if it is  
 * not return 0
 */
int checkPrefix(char input[])
{
	int twoDigit = 0;           /* Variable for return */

	if (((input[0] == '0')) && ((input[1] == '1') || (input[1] == '5') || (input[1] == '6') || (input[1] == '8') || (input[1] == '9')))
	{
		twoDigit = 1;
	}
	else
	{
		twoDigit = 0;
	}
	return twoDigit;
}

/* [****PUBLIC FUNCTION****] //////////Not complete
 *
 * 	This function check Phonenumber
 *    if result = 0 that's phone number is invalid
 *    if result = 1 that means phone number is valid
 *
*/
int checkPhoneNumber(char *stringToCheck)
{
  int i = 0;              /* Loop controller */
  int result = 1;				 /* Resuit value after checking */
  
  if ((strlen(stringToCheck) != 10))
  {
		printf("\tInvalid - Your Phonenumber must be 10 character\n");
    result = 0;
  }
	else if(checkPrefix(stringToCheck) == 0 && result == 1)
  {
    printf("\tInvalid - Your Phonenumber begin with 01,05,06,08,09\n");
    result = 0;
  }
  else
  {
    for(i = 0; i < strlen(stringToCheck); i++)
    {
      if(!isdigit(stringToCheck[i]))
      {
        result = 0;
      } 
    }
    if (result == 0)
    printf("\tInvalid - Must be all digits\n");
  }
  
  return result;
}

/* [****PUBLIC FUNCTION****]
 * Compares two dates. 
 * Returns  1 if the first date is later than the second, 
 *         -1 if the first date is earlier than the second, and 
 *          0 if they are the same.
 * Arguments: day1   - day of first date
 *            month1 - month of first date
 *            year1  - year of first date
 *            day2   - day of second date
 *            month2 - month of second date
 *            year2  - year of second date
 *
 *   Modified with permission by [Phoramint Taweeros] on [05/apr/2021]
 *   
 *   Edit: not edit
 *   Based on code by Sally Goldin from [timeFunction.c]
 *   Used with permission.
 */
int compareDate(int day1,int month1,int year1, int day2,int month2,int year2)
{
  int compare = 0; /*mark variable*/

  if (year1 > year2)                // year future
    compare = 1;
  else if (year1 < year2)           // year past
    compare = -1;
  else if (month1 > month2)         // month future
    compare = 1;
  else if (month1 < month2)         // month past
    compare = -1;
  else if (day1 > day2)             // day future
    compare = 1;
  else if (day1 < day2)             // day past
    compare = -1;
  return compare;
} 

/**[****PUBLIC FUNCTION****]
 *   Local function, not exposed in the header file.
 *   dateToday function.
 *   get day month year today and send data with pointer
 *	 
 *   Modified with permission by [Phoramint Taweeros] on [05/apr/2021]
 *   
 *   Edit: not edit
 *   Based on code by Sally Goldin from [timeFunction.c]
 *   Used with permission.
 */
void dateToday(int* pDay, int *pMonth, int* pYear)
{
  time_t seconds = 0;                 /*get time in second*/
  struct tm * pTimeStruct;            /* get time day, month, year in struct variable*/

  seconds = time(&seconds);           /* time in seconds */
  pTimeStruct = localtime(&seconds);
  *pDay = pTimeStruct->tm_mday;
  *pMonth = pTimeStruct->tm_mon + 1;
  *pYear = pTimeStruct->tm_year + 1900;
}

/*  [****PUBLIC FUNCTION****] 
 *  This function checks user input that 
 *  the day is in the future or not
 *  if check = 1 day is in the future or now
 *  and if check = 0 day is in the past
 *
 *   Modified with permission by [Phoramint Taweeros] on [05/apr/2021]
 *   
 *   Edit: not edit
 *   Based on code by Sally Goldin from [timeFunction.c]
 *   Used with permission.
 */
int checkFuture(int day, int month, int year)
{
  int nowDay;     /*day today at run program*/
  int nowMonth;   /*month today at run program*/
  int nowYear;    /*Year today at run program*/
  int check = 0;  /*variable for keep that future or not*/
  
  dateToday(&nowDay,&nowMonth,&nowYear);
  if(compareDate(nowDay,nowMonth,nowYear,day,month,year)!= 1)
  {
    check = 1;    //Now or future
  }
  return check;
}
