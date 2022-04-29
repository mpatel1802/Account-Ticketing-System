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
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "commonHelpers.h"

int currentYear(void)
{
	time_t currentTime = time(NULL);

	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		;
	}

}

int getInteger(void)
{
	int get_int_value = 0;
	char new_line = 0;
	int flag = 1;

	do
	{
		scanf("%d%c", &get_int_value, &new_line);

		if (new_line == '\n')
		{
			flag = 0;
		}

		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");

		}

	} while (flag == 1);

	return get_int_value;
}

int getPositiveInteger(void)
{
	int flag = 1;
	int getInputPosn = 0;

	do
	{
		getInputPosn = getInteger();

		if (getInputPosn >= 0)
		{
			flag = 0;
		}
		else
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}

	} while (flag == 1);

	return getInputPosn;

}

int getIntFromRange(int lowerRange, int upperRange)
{
	int limit = 0;
	int flag = 1;
	do
	{
		limit = getInteger();

		if (limit < lowerRange || limit > upperRange)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerRange, upperRange);
		}

		else
		{
			flag = 0;
		}

	} while (flag == 1);

	return limit;
}

double getDouble(void)
{
	double get_dbl_input = 0.0;
	char new_line = 0;
	int flag = 1;

	do
	{
		scanf("%lf%c", &get_dbl_input, &new_line);

		if (new_line == '\n')
		{
			flag = 0;
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (flag == 1);

	return get_dbl_input;
}


double getPositiveDouble(void)
{
	double get_dbl_posn = 0.0;
	int flag = 1;

	do
	{
		get_dbl_posn = getDouble();

		if (get_dbl_posn > 0)
		{
			flag = 0;
		}
		else
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}

	} while (flag == 1);

	return get_dbl_posn;
}





char getCharOption(const char checkChar[])
{
	int flag = 0;
	int badInput = 0;
	int limit = 0;
	char entered_char;
	int i = 0;

	char entered_char1 = '\0';
	do
	{
		scanf("%c%c", &entered_char, &entered_char1);
		if (entered_char1 == '\n')
		{
			for (i = 0; checkChar[i] != '\0'; i++)
			{
				if (entered_char == checkChar[i])
				{
					limit++;
				}
				else
				{
					badInput++;
				}
			}
			if (limit >= 1)
			{
				flag = 1;
				return entered_char;

			}
			else
			{
				printf("ERROR: Character must be one of [%s]: ", checkChar);
			}
		}
		else
		{
			printf("ERROR : Character must be one of [%s]: ", checkChar);
			clearStandardInputBuffer();
		}
	} while (flag != 1);
	return entered_char;
}


void getCString(char get_pointer[], int minimum_character, int maximum_character)
{
	int i = 0, j = 0;
	int range = 0;
	char string[1000] = { 0 };
	int flag = 1;

	do
	{

		scanf("%1000[^\n]", string);
		clearStandardInputBuffer();

		range = 0;
		for (i = 0; string[i] != '\0'; i++)
		{
			range++;
		}

		if (range >= minimum_character && range <= maximum_character)
		{
			for (j = 0; j < range + 1; j++)
			{
				get_pointer[j] = string[j];
			}
			flag = 0;
		}
		else
		{

			if (minimum_character == maximum_character)
			{
				if (range < minimum_character || range > maximum_character)
				{
					printf("ERROR: String length must be exactly %d chars: ", minimum_character);
				}
			}

			else if (minimum_character != maximum_character)
			{
				if (range > maximum_character)
				{

					printf("ERROR: String length must be no more than %d chars: ", maximum_character);
				}
				else
				{

					printf("ERROR: String length must be between %d and %d chars: ", minimum_character, maximum_character);
				}
			}

		}


	} while (flag == 1);


}
void checkSpacesUserLogin(struct UserLogin* user_login)
{
	int count = 0;
	int repeatLoop = 1;
	int i = 0;

	do
	{
		count = 0;

		printf("Enter user login (%d chars max): ", 10);
		getCString(user_login->username, 1, 10);

		do
		{
			if (isspace(user_login->username[i]))
			{
				count++;
			}

			i++;
		} while (user_login->username[i] != '\0');

		if (count > 0)
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}
		else
		{
			repeatLoop = 0;
		}

	} while (repeatLoop);

}