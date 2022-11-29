# Auction_system_with_data_structure
List of all file
addMoney.c
//-> Use the username value to search for information in the user hash table, then receive the money you want to add to your account. 
//   And add numerical data into the system 
-> required 1 argument
    -username of account that loged-in
-> use username as key to search in hash table data structuer
-> get amount of money that account owner want to add to balance 
    -input must follow this rules
      *amount of money should be number and more than 0
-> add money to that account balance
-> complete

bid.c
-> create bid history that keep data user that bid for know user in each history.
-> get input of amount of money that user want to bid
	-amount of money must be numberic
-> compair amount of money of user input and highest bid
	-amount of money of user input must be higher
-> store bidding information in structure
-> insert it in history bidding of product
-> complete

buildProduct.c
//->Read the product text file and save it to the hash table product using the command insert by key (product name) 
//  and the last step is to update the product's key and count back to main.c. 
-> required 2 argument
	-productname
	-amount of product in program
-> read data from product's data file
-> save data that read it in structure
-> insert struture in hash table by
-> repeat until read all data in product's data file
-> complete

builduser.c
//-> The action is to read the user text file and save it to the hash table user using the command insert by key (username) 
//   and the last step is to update the user key and count back to main.c. 
-> read data from user's data file
-> save data that read it in structure
-> insert struture in hash table by
-> repeat until read all data in user's data file
-> complete

chainedHashTableProduct.c
-> The file for creating a product's Hash table containing all hashtable operations will be in this file, e.g. insert, delete, etc. 
-> complete

chainedHashTableUser.c
-> A file for creating a user Hash table containing all hashtable operations will be in this file, e.g. insert, delete, etc. 
-> complete

chainedSortBinary.c
-> file for create bibary tree contain all bibary tree operation will be in this file, create, insert, print all node, free.
-> complete

creatAction.c
//-> create action for each product when have action and store to structure
-> required 2 argument
-> get information of product from user
	These are required information and rules of each
		*product name 		must be all alpha and not longer than 32 characters
		*description 		must not longer than 256 character
		*start price 		must be numberic character
		*buy off price 		must be numberic character and higher than start price
		*date to start auction 	must follow this from dd/mm/yy and dd,mm,yyyy must be numberic character
		*date the auction end 	must follow this from dd/mm/yy and dd,mm,yyyy must be numberic character and later than date to start auction
-> save information in structure
-> insert struture in hash table by
-> complete

login.c
//-> show login display then varidate information to login and return array that name of user login.
-> display log-in menu
-> ask user for username and passsword
-> search that username in and compare password is it the same
-> return 1 if there are no error return 0 if have errors
-> complete

logOut.c
//-> show logOut display and print logOut complete.
-> ask user to confirm to log out Y to confirm N to cancel
-> if user confirmed exit the program
-> complete

printProductData.c
//-> input product name and print all detail that product.
-> required 1 argument
	-productname
-> use productname as key to search in hash table
-> if found display product information if not display error message
-> complete

printUserData.c
//-> input user name and print all detail that user.
-> required 1 argument
	-username
-> use username as key to search in hash table
-> if found display user information if not display error message
-> complete

signUp.c
//-> validate data for new user then create new user and update user structure.
-> get informaiton form user
	These are required information
		*username 	must not longer than 32 characters
		*name 		must be all alpha ans not longer than 32 characters
		*password 	must have at least 1 upper, 1 lower, 1 numberic, 1 special character range between 8 and 32 characters
		*email ??
		*phonenumber 	must be numberic and 10 characters long
-> insert structure in hash table
-> complete

updateDataFileProduct.c
-> rewrite current data of product to our product's data base file
-> required 1 argument
	-pHeadProduct	that is head of pointer contain product's name
-> complete

updateDataFileUser.c
-> rewrite current data of user to our user's data base file
-> required 1 argument
	-pHeadProduct	that is head of pointer contain product's name
-> complete

validate.c
-> support validate any thing for any file.c for example validate number validate alphabet.
-> required 1 argument
	-string to check
-> There are 9 validation
	-username 	must not longer than 32 characters
	-name 		must be all alpha ans not longer than 32 characters
	-password 	must have at least 1 upper, 1 lower, 1 numberic, 1 special character range between 8 and 32 characters
	-email 
	-phonenumber 	must be numberic and 10 characters long
	-product name 	must be all alpha and not longer than 32 characters
	-description 	must not longer than 256 character
	-start price 	must be numberic character
	-buy off price 	must be numberic character and higher than start price
	-date 		must follow this from dd/mm/yy and dd,mm,yyyy must be numberic character
-> complete

winner.c
-> print all product data that the auction of that product ended
-> required 1 argument
	-pHeadProduct	that is head of pointer contain product's name
-> complete
