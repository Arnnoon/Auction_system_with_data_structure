typedef struct _keyuser
{
  char username[32];
  struct _keyuser *pNext;
} ALLUSER_T;

typedef struct _keyproduct
{
  char productName[32];
  struct _keyproduct *pNext;
} ALLPRODUCT_T;

typedef struct _user
{
  char userID[20];
  char username[32];
	char name[32];
  char password[32];
  char email[32];
  char phoneNumber[16];
  double balance;
} USER_T;

typedef struct _bid
{
	USER_T * buyer;
  char usernameBid[30];
	double amount;
  int bidDay;
  int bidMonth;
  int bidYear;
	struct _bid * pNext;
} BID_T;

typedef struct _product
{
	USER_T * owner;
  char productID[11];
  char productName[32];
  char description[256];
  double startPrice;
  double buyOffPrice;
  int startDay;
  int startMonth;
  int startYear;
  int endDay;
  int endMonth;
  int endYear;
	int biddingAmount;	
	int returnMoney;
	struct _product *pNext;
  BID_T *history;
} PRODUCT_T;

/*  [****PUBLIC FUNCTION****]
 *  This function add user's money
 *  Arguments: username that login
 *  Returns : not have return
 */
void addMoney(char *usernameLogin);

/*  [****PUBLIC FUNCTION****]
 *  This function will open file and then read product file
 *  each line put the information in structure.
 *  Arguments: pHead of ALLPRODUCT_T, countAllProduct
 *  Returns : count of product
 */
int buildProduct(ALLPRODUCT_T *pHead,int countAllProduct);

/*  [****PUBLIC FUNCTION****]
 *  This function will open file and then read user file
 *  each line put the information in structure.
 *  Arguments: pHead of ALLUSER_T, countAllUser
 *  Returns : countAllUser
 */
int buildUser(ALLUSER_T *pHead,int countAllUser);

/*  [****PUBLIC FUNCTION****]
 *  main idea is add new product to data in structure.
 *  fucntion will validate all detail about that product before add to data in structure.
 *  Arguments: allProductName - all key product in database  
 *             countAllProduct - sum of product in database
 *  Returns : 1 - creat complete
 *            0 - create fail
*/
int creatAuction(ALLPRODUCT_T *pHeadProduct,int countAllProduct,char usernameLogin[]);

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data with username that user input
 *  then check that username has in database or not
 *  if have this username in data program will keep that data for check password
 *  if password is correct, you do function in AuctionSystem
 *  Arguments: usernameLogin - if login comple then update name of usernameLogin
 *  Returns : 1 - login complete
 *            0 - login fail.
 */
int loginOption(char *usernameLogin);

/*  [****PUBLIC FUNCTION****]
 *  This function will log out from this program
 *  Arguments: no argument
 *  Returns : success logOut variable
 */
int logOut();

/*  [****PUBLIC FUNCTION****]
 *  This function is for user that's not log in that want to log out
 *  Arguments: no argument
 *  Returns : option success exit
 */
int exitProgram();

/*  [****PUBLIC FUNCTION****]
 *  This function will get product name to search
 *  Arguments: productName
 *  Returns : not have return
 */
void getProductName(char productName[]);

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data some product in database
 *  then print all data of that product
 *  Arguments: productName
 *  Returns : not have return
 */
void printProductData();

/*  [****PUBLIC FUNCTION****]
 *  This function will look up data some people in database
 *  then print all data of that people
 *  Arguments: no argument
 *  Returns : not have return
 */
void printUserData();

/*  [****PUBLIC FUNCTION****]
 *  Arguments: allProductName - key product for hashLookup
 *             countAllProduct - sum of product in database
 *  Returns 1 if all update data complete
 *          0 if some of data can not updata or not found.
*/
int updateDataFileProduct(ALLPRODUCT_T *pHeadProduct);

/*  [****PUBLIC FUNCTION****]
 *  Arguments: allUserName - key user for hashLookup
 *             countAllUser - sum of user in database
 *  Returns 1 if all update data complete
 *          0 if some of data can not updata or not found.
*/
int updateDataFileUser(ALLUSER_T *pHeadUser);

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string is all digits.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkAllDigit(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string is all alphabet.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkAllAlpha(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have Uppercase.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeUpper(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have Lowercase.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeLower(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 *
 * This function will check that the string have special character.
 * Argument: stringTocheck - the string that is going to be checked
 * Return the checking result: 0 is false, 1 is true
 */
int checkSomeSpecial(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 * This function check that email valid form or not.
 * Return the checking result: 0 is false, 1 is true
 */
int checkEmail(char *email);

/**  [****PUBLIC FUNCTION****]
 *   validDate function.
 *   This function check all day month year valid or not.
 *   Return the checking result: 0 is false, 1 is true
 */
int validDate(int day, int month, int year);

/**  [****PUBLIC FUNCTION****]
 *   validDate function.
 *   This function check day form valid or not. (Ex. 14/01/2021)
 *   Return the checking result: 0 is false, 1 is true
 */
int checkDayForm(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 *
 * 	This function check Password that must have 
 *  Uppercase Lowercase and Special character
 *  Return the checking result: 0 is false, 1 is true
*/
int checkPassword(char *password);

/* [****PUBLIC FUNCTION****]
 *
 * 	This function check Phonenumber
 *    if result = 0 that's phone number is invalid
 *    if result = 1 that means phone number is valid
 *
*/
int checkPhoneNumber(char *stringToCheck);

/* [****PUBLIC FUNCTION****]
 * Compares two dates. 
 * Returns -1 if the first date is later than the second, 
 *          1 if the first date is earlier than the second, and 
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
int compareDate(int day1,int month1,int year1, int day2,int month2,int year2);

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
void dateToday(int* pDay, int *pMonth, int* pYear);

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
int checkFuture(int day, int month, int year);

/*  [****PRIVATE FUNCTION****]
 *  main idea is generate product id Ex. 000000001, 000125351
 *  Arguments: productID - update product id before generate 
 *             countAllProduct - sum of product in database
 *  Returns : not return
*/
void createID(char id[],int countAll);

/*  [****PUBLIC FUNCTION****]
 *  Arguments: usernameLogin - for update username login 
                              that time if sign up complete
 *  Returns 1 if signUp complete
 *          0 if signUp fail
 */
int signUpMenu(ALLUSER_T *pHeadUser, int countAllUser, char *usernameLogin);

/*  [****PUBLIC FUNCTION****]
 *  This function use for user bidding
 *  Arguments: username
 *  Returns : bOk(success bid)
 */
int bidProduct(char *username);

/** [****PRUBLIC FUNCTION****]
 *  This function will show display about winner bidding.
 *  Arguments: pHeadProduct - product to be printed at the end of the auction
 *  Returns: Not return
 */
void showWinner(ALLPRODUCT_T *pHeadProduct);
