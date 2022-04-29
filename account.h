#pragma once
/*==================================================
  Assignment #2 Milestone #4
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_



#define ACCOUNTSFILE "accounts.txt"
#define ACCOUNTSARCFILE "accounts_arc.txt"
#include <stdio.h>
#define MIN_AGE 18
#define MAX_AGE 110

struct Demographic
{
	int birth_year;
	double income;
	char Cstring[31];
};

struct UserLogin
{
	char acc_holder[31];
	char username[12];
	char password[9];

};

struct Account
{


	int account_num;
	char account_type;
	struct UserLogin login;
	struct Demographic demo;
};


void getAccount(struct Account* account_details);
void getUserLogin(struct Account* account_details);
void getDemographic(struct Account* account_details);
void updateAccount(struct Account* accountData);
void updateUserLogin(struct UserLogin* user_login);
void updateDemographic(struct Demographic* demo);
int loadAccounts(struct Account acc[], int size);
int archiveAccounts(const struct Account* acc);
int saveAccounts(const struct Account acc[], int size);


#endif