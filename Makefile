# Makefile for Online Auction System
# This make file use specific in auction system project
# auction system is project in CPE111(data structure) 
# Semester 2/2020 KMUTT
# 
# Last edit: 24/05/2021
# 
# Modify By ETC.official team
# 

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES=  main$(EXECEXT)
all : $(EXECUTABLES)

chainedSortBinary.o : chainedSortBinary.c abstractSortBinary.h AuctionSystem.h
	gcc -c chainedSortBinary.c

chainedHashTableUser.o : chainedHashTableUser.c abstractHashTableUser.h
	gcc -c chainedHashTableUser.c

chainedHashTableProduct.o : chainedHashTableProduct.c AuctionSystem.h abstractHashTableProduct.h 
	gcc -c chainedHashTableProduct.c

logOut.o :	logOut.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h abstractSortBinary.h
	gcc -c logOut.c

login.o : login.c AuctionSystem.h abstractHashTableProduct.h
  	gcc -c : login.c

winner.o : winner.c AuctionSystem.h abstractHashTableProduct.h
  	gcc -c : winner.c

updateDataFileUser.o :	updateDataFileUser.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c updateDataFileUser.c

updateDataFileProduct.o :	 updateDataFileProduct.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c updateDataFileProduct.c

printUserData.o :	printUserData.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c printUserData.c

printProductData.o :	printProductData.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h abstractSortBinary.h
	gcc -c printProductData.c

buildProduct.o :	buildProduct.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c buildProduct.c

buildUser.o :	buildUser.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c buildUser.c

validate.o :	validate.c AuctionSystem.h
	gcc -c validate.c

addMoney.o :	addMoney.c AuctionSystem.h abstractHashTableUser.h
	gcc -c addMoney.c

creatAuction.o :	creatAuction.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c creatAuction.c

signUp.o : signUp.c AuctionSystem.h abstractHashTableUser.h
  gcc -c : signUp.c

bid.o :	bid.c AuctionSystem.h abstractHashTableUser.h abstractHashTableProduct.h
	gcc -c bid.c

main$(EXECEXT) : main.o logOut.o login.o addMoney.o validate.o updateDataFileUser.o updateDataFileProduct.o printUserData.o printProductData.o buildUser.o buildProduct.o creatAuction.o chainedSortBinary.o chainedHashTableUser.o chainedHashTableProduct.o signUp.o bid.o winner.o
	gcc -o main$(EXECEXT) main.o logOut.o login.o addMoney.o validate.o updateDataFileUser.o updateDataFileProduct.o printUserData.o printProductData.o buildProduct.o buildUser.o creatAuction.o chainedHashTableUser.o chainedHashTableProduct.o chainedSortBinary.o signUp.o bid.o winner.o -lm

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
