/*==================================================
  Assignment #2 Milestone #4
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */

#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<ctype.h>
#include "commonHelpers.h"
#include "account.h"


void getAccount(struct Account* account_details)
{


	printf("New Account Data (Account#:%d)\n", account_details->account_num);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	account_details->account_type = getCharOption("AC");
	printf("\n");

}


void getUserLogin(struct Account* account_details)
{
	
	int i = 0;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	checkSpacesUserLogin(&account_details->login);
	

	printf("Enter the display name (%d chars max): ", 30);
	getCString(account_details->login.acc_holder, 1, 30);


	int countDigit, countUpper, countLower, countSymbol;
	int j = 0;
	int keepRepeating = 1;
	char symbols[9] = "!@#$%^&*";

	do
	{
		countDigit = 0;
		countUpper = 0;
		countLower = 0;
		countSymbol = 0;

		printf("Enter the password (must be %d chars in length): ", 8);
		getCString(account_details->login.password, 8, 8);


		i = 0;
		do
		{
			if (isdigit(account_details->login.password[i]))
			{
				countDigit++;
			}

			if (isupper(account_details->login.password[i]))
			{
				countUpper++;
			}

			if (islower(account_details->login.password[i]))
			{
				countLower++;
			}

			if (!islower(account_details->login.password[i]) && !isupper(account_details->login.password[i]) && !isdigit(account_details->login.password[i]))
			{
				for (j = 0; j < 8; j++)
				{
					if (account_details->login.password[i] == symbols[j])
					{

						countSymbol++;

					}

				}

			}

			i++;

		} while (account_details->login.password[i] != '\0');

		if (countDigit == 2 && countLower == 2 && countUpper == 2 && countSymbol == 2)
		{
			keepRepeating = 0;
		}
		else
		{

			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");

		}

	} while (keepRepeating);

	printf("\n");
}


void getDemographic(struct Account* account_details)
{
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	int year = 0;
	int limit = year - MAX_AGE;
	int limit1 = year - MIN_AGE;

	int i = 0;

	int flag = 0;
	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	do
	{
		scanf("%d", &account_details->demo.birth_year);
		year = currentYear();
		limit = year - MAX_AGE;
		limit1 = year - MIN_AGE;



		if (account_details->demo.birth_year < limit)
		{
			printf("ERROR: Value must be between 1911 and 2003 inclusive: ");
			flag = 0;
		}
		else if (account_details->demo.birth_year > limit1)
		{
			printf("ERROR: Value must be between 1911 and 2003 inclusive: ");
			flag = 0;
		}
		else
		{
			flag = 1;
		}

	} while (flag != 1);

	printf("Enter the household Income: $");
	account_details->demo.income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(account_details->demo.Cstring, 1, 30);


	do
	{
		if (islower(account_details->demo.Cstring[i]))
		{
			account_details->demo.Cstring[i] = toupper(account_details->demo.Cstring[i]);
		}
		i++;

	} while (account_details->demo.Cstring[i] != '\0');

	printf("\n");


}

void updateAccount(struct Account* acc)
{
	int option;
	int flag = 1;
	do
	{
		printf("Account: %d - Update Options\n", acc->account_num);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", acc->account_type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 3);
		printf("\n");

		switch (option)
		{
		case 1:
			printf("Enter the account type (A=Agent | C=Customer): ");
			acc->account_type = getCharOption("AC");
			
			break;
		case 2:
			updateUserLogin(&acc->login);
			break;
		case 3:
			updateDemographic(&acc->demo);
			break;
		case 0:
			flag = 0;
			break;
		}
	} while (flag);
}
void updateUserLogin(struct UserLogin* user_login)
{
	int option;
	int flag1 = 1;
	int flag = 1;
	int digit, upper, lower, symbol;
	int i;
	do
	{
		printf("User Login: %s - Update Options\n", user_login->username);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", user_login->acc_holder);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);
		printf("\n");

		switch (option)
		{
		case 1:

			printf("Enter the display name (%d chars max): ", 30);
			getCString(user_login->acc_holder, 1, 30);
			printf("\n");
			break;
		case 2:
			do
			{
				digit = 0, lower = 0, upper = 0, symbol = 0;
				printf("Enter the password (must be %d chars in length): ", 8);
				getCString(user_login->password, 8, 8);
				i = 0;
				do
				{
					if (isdigit(user_login->password[i]))
					{
						digit++;
					}
					if (isupper(user_login->password[i]))
					{
						upper++;
					}
					if (islower(user_login->password[i]))
					{
						lower++;
					}
					if (!islower(user_login->password[i]));
					{
						if (!isupper(user_login->password[i]))
						{
							if (!isdigit(user_login->password[i]))
							{
								symbol++;
							}
						}
					}
					i++;

				} while (user_login->password[i] != '\0');

				if (digit == 2)
				{
					if (lower == 2)
					{
						if (upper == 2)
						{
							flag1 = 0;
						}
					}
				}
				else
				{
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*\n");
				}
			} while (flag1);
			printf("\n");
			break;
		case 0:
			flag = 0;
			break;
		}
	} while (flag);
}

void updateDemographic(struct Demographic* demo)
{
	int option;
	int flag = 1;
	int i = 0;
	do
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->income);
		printf("2) Country (current value: %s)\n", demo->Cstring);
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);
		printf("\n");

		switch (option)
		{
		case 1:
			printf("Enter the household Income: $");
			demo->income = getPositiveDouble();
			printf("\n");
			break;

		case 2:
			printf("Enter the country (30 chars max.): ");
			getCString(demo->Cstring, 1, 30);
			do
			{
				if (islower(demo->Cstring[i]))
				{
					demo->Cstring[i] = toupper(demo->Cstring[i]);
				}
				i++;

			} while (demo->Cstring[i] != '\0');

			printf("\n");
			break;
		case 0:
			flag = 0;
			break;
		}

	} while (flag);
};


int loadAccounts(struct Account acc[], int size)
{
	int count = 0;
	char ch;
	FILE* fp = fopen(ACCOUNTSFILE, "r");

	if (fp != NULL)
	{

		while (count < size && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]%c",
			&acc[count].account_num,
			&acc[count].account_type,
			acc[count].login.acc_holder,
			acc[count].login.username,
			acc[count].login.password,
			&acc[count].demo.birth_year ,
			&acc[count].demo.income,
			acc[count].demo.Cstring, &ch) == 9)
		{
			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}
			count++;
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return count;
}


int archiveAccounts(const struct Account* acc)
{
	int result = 0;

	FILE* fp = fopen(ACCOUNTSARCFILE, "a");

	if (fp != NULL)
	{

		result = fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", acc->account_num,
			acc->account_type,
			acc->login.acc_holder,
			acc->login.username,
			acc->login.password,
			acc->demo.birth_year,
			acc->demo.income,
			acc->demo.Cstring);

		fflush(fp);
		fclose(fp);
		fp = NULL;

	}
	else
	{
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

	}

	return result > 0 ? 1 : 0;

}


int saveAccounts(const struct Account acc[], int size)
{
	int i = 0, count = 0;
	FILE* fp = fopen(ACCOUNTSFILE, "w");

	if (fp != NULL)
	{

		for (i = 0; i < size; i++)
		{
			if (acc[i].account_num > 0)
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", acc[i].account_num,
					acc[i].account_type,
					acc[i].login.acc_holder,
					acc[i].login.username,
					acc[i].login.password,
					acc[i].demo.birth_year,
					acc[i].demo.income,
					acc[i].demo.Cstring);
				count++;
			}
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return count;
}

