/*==================================================
  Assignment #2 Milestone #2
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"




void displayAccountSummaryHeader()
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountDetailHeader()
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* acc)
{
	printf("%05d %-9s %5d", acc->account_num, acc->account_type == 'A' ? "AGENT" : "CUSTOMER", acc->demo.birth_year);
	printf("\n");

}

void displayAccountDetailRecord(struct Account* acc)
{
	int i = 0;
	int k = 0;
	k = strlen(acc->login.password);

	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", acc->account_num, acc->account_type == 'A' ? "AGENT" : "CUSTOMER", acc->demo.birth_year, acc->demo.income, acc->demo.Cstring, acc->login.acc_holder, acc->login.username);
	for (i = 0; i < k; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			printf("*");
		}
		else
		{
			printf("%c", acc->login.password[i]);
		}
	}
	printf("\n");
}

void displayAllAccountSummaryRecords(struct Account acc[], int size)
{
	int i;
	int flag = 1;

	displayAccountSummaryHeader();
	for (i = 0; i < size && flag; i++)
	{
		if (acc[i].account_num != 0)
		{

			displayAccountSummaryRecord(&acc[i]);
		}
	}
	printf("\n");
}

void displayAllAccountDetailRecords(struct Account acc[], int size)
{
	int i;
	int flag = 1;

	displayAccountDetailHeader();
	for (i = 0; i < size && flag; i++)
	{
		if (acc[i].account_num != 0)
		{

			displayAccountDetailRecord(&acc[i]);
		}
	}
	printf("\n");

}

void displayTicketHeader(void)
{

	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");

}

void displayNewMessage(const struct AccountTicketingData* newTic)
{
	int i = 0, j = 0;
	int flag1 = 1, flag2 = 1;
	int ticket_num;
	int k = 0;
	do
	{
		flag2 = 1;
		displayTicketHeader();

		for (i = 0; i < newTic->TICKET_MAX_SIZE; i++)
		{
			if (newTic->tickets[i].counter == 1 && newTic->tickets[i].number != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", newTic->tickets[i].number, newTic->tickets[i].acc_num, newTic->tickets[i].messageInfo->name, newTic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", newTic->tickets[i].subject, newTic->tickets[i].counter);
			}
		}
		
		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");

		do
		{
			ticket_num = getInteger();
			if (ticket_num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (ticket_num == 0)
			{
				printf("\n");
				flag1 = 0;
				flag2 = 0;
			}
			else
			{
				printf("\n");
				flag2 = 0;
			}
		} while (flag2);
		flag2 = 1;
		if (ticket_num != 0)
		{
			k = 0;
			for (i = 0; i < newTic->TICKET_MAX_SIZE && flag2; i++)
			{
				if (newTic->tickets[i].number == ticket_num && newTic->tickets[i].number != 0)
				{
					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", newTic->tickets[i].number, newTic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", newTic->tickets[i].subject);
					printf("================================================================================\n");
					for (j = 0; j < newTic->tickets[i].counter; j++)
					{
						printf("%s (%s):\n", newTic->tickets[i].messageInfo[j].account_author_type == 'A' ? "AGENT" : "CUSTOMER", newTic->tickets[i].messageInfo[j].name);
						printf("   %s\n\n", newTic->tickets[i].messageInfo[j].message_details);
						k++;
						if (k % 5 == 0)
						{
							pauseExecution();
						}
					}
					if (k % 5 != 0)
					{
						pauseExecution();
					}
					flag2 = 0;
				}
			}
		}
		if (ticket_num != 0)
		{
			if (flag2)
			{
				printf("ERROR: Invalid ticket number.\n");
				printf("\n");
				pauseExecution();
			}
		}
	} while (flag1);
}

void displayActiveMessage(const struct AccountTicketingData* newTic)
{
	int i = 0, j = 0;
	int flag1 = 1, flag2 = 1;
	int ticket_num;
	int k = 0;
	do
	{
		flag2 = 1;
		displayTicketHeader();
		for (i = 0; i < newTic->TICKET_MAX_SIZE; i++)
		{
			if (newTic->tickets[i].status == 1 && newTic->tickets[i].number != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", newTic->tickets[i].number, newTic->tickets[i].acc_num, newTic->tickets[i].messageInfo->name, newTic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", newTic->tickets[i].subject, newTic->tickets[i].counter);
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");

		do
		{
			ticket_num = getInteger();
			if (ticket_num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (ticket_num == 0)
			{
				printf("\n");
				flag1 = 0;
				flag2 = 0;
			}
			else
			{
				printf("\n");
				flag2 = 0;
			}
		} while (flag2);
		flag2 = 1;
		if (ticket_num != 0)
		{
			k = 0;
			for (i = 0; i < newTic->TICKET_MAX_SIZE && flag2; i++)
			{
				if (newTic->tickets[i].number == ticket_num && newTic->tickets[i].number != 0)
				{
					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", newTic->tickets[i].number, newTic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", newTic->tickets[i].subject);
					printf("================================================================================\n");

					for (j = 0; j < newTic->tickets[i].counter; j++)
					{
						printf("%s (%s):\n", newTic->tickets[i].messageInfo[j].account_author_type == 'A' ? "AGENT" : "CUSTOMER", newTic->tickets[i].messageInfo[j].name);
						printf("   %s\n\n", newTic->tickets[i].messageInfo[j].message_details);
						k++;
						if (k % 5 == 0)
						{
							pauseExecution();
						}
					}
					if (k % 5 != 0)
					{
						pauseExecution();
					}

					flag2 = 0;
				}
			}
		}
		if (ticket_num != 0)
		{
			if (flag2)
			{
				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n");
				printf("\n");
				pauseExecution();
			}
		}
	} while (flag1);
}

void displayCustHeader(void)
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

void displayCustMessage(const struct Ticket* tickets, const struct Account* accountInfo, int size)
{
	int i = 0, j = 0, posn = 0;
	int flag1 = 1, flag2 = 1;
	int ticket_num;
	int k = 0;

	do
	{
		flag2 = 1;
		displayCustHeader();
		for (i = 0; i < size; i++)
		{
			if (tickets[i].acc_num == accountInfo->account_num && tickets[i].number != 0)
			{
				printf("%06d %-6s %-30s %5d\n",tickets[i].number, tickets[i].status == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject, tickets[i].counter);
			}
		}
		printf("------ ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		do
		{
			ticket_num = getInteger();
			if (ticket_num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (ticket_num == 0)
			{
				printf("\n");
				flag1 = 0;
				flag2 = 0;
			}
			else
			{
				printf("\n");
				flag2 = 0;
			}

		} while (flag2);
		flag2 = 1;
		if (ticket_num != 0)
		{
			posn = findTicketIndex(ticket_num, tickets, size, 0);

			if (tickets[posn].acc_num != accountInfo->account_num && posn != -1)
			{
				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				pauseExecution();
				flag2 = 0;
			}
			if (tickets[posn].acc_num == accountInfo->account_num && posn != -1)
			{
				k = 0;
				for (i = 0; i < size && flag2; i++)
				{
					if (tickets[i].number == ticket_num && tickets[i].number != 0)
					{
						printf("================================================================================\n");
						printf("%06d (%s) Re: %s\n", tickets[i].number, tickets[i].status == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject);
						printf("================================================================================\n");
						for (j = 0; j < tickets[i].counter; j++)
						{

							printf("%s (%s):\n", tickets[i].messageInfo[j].account_author_type == 'A' ? "AGENT" : "CUSTOMER", tickets[i].messageInfo[j].name);
							printf("   %s\n\n", tickets[i].messageInfo[j].message_details);

							k++;
							if (k % 5 == 0)
							{
								pauseExecution();
							}
						}
						if (k % 5 != 0)
						{
							pauseExecution();
						}
						flag2 = 0;
					}
				}
			}
			if (flag2)
			{
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();
			}
		}
	} while (flag1);
}
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	printf("\n");
}


int findAccountIndexByAcctNum(int account_num, const struct Account acc[], int size, int input_account_num)
{

	int i;
	int posn;

	if (input_account_num)
	{
		printf("Enter the account#: ");
		account_num = getPositiveInteger();
		printf("\n");
	}

	for (i = 0, posn = -1; posn < 0 && i < size; i++)
	{
		if (account_num == acc[i].account_num)
		{
			posn = i;
		}
	}
	return posn;
}

int menuLogin(const struct Account acc[], int size)
{
	int option, attempt = 3, posn = 0, pwd = 0, login = 0;
	int account_num;
	int flag1 = 1, flag2 = 1;
	char character = 0;
	char login_input[200];
	char pwd_input[200];
	do
	{
		flag2 = 1;
		attempt = 3;
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\n");
		printf("Selection: ");

		option = getIntFromRange(0, 1);
		printf("\n");
		switch (option)
		{
		case 0:
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			character = getCharOption("yYnN");
			if (character == 'y' || character == 'Y')
			{
				posn = -1;
				flag1 = 0;
			}
			else
			{
				flag1 = 1;
			}
			printf("\n");
			break;
		case 1:
			do
			{
				printf("Enter the account#: ");
				account_num = getPositiveInteger();

				posn = findAccountIndexByAcctNum(account_num, acc, size, 0);
				printf("User Login    : ");
				getCString(login_input, 1, 200);
				login = strcmp(login_input, acc[posn].login.username);
				printf("Password      : ");
				getCString(pwd_input, 1, 200);

				pwd = strcmp(pwd_input, acc[posn].login.password);

				if (login == 0 && pwd == 0)
				{
					printf("\n");
					flag2 = 0;
					flag1 = 0;
				}
				else
				{
					attempt--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempt);
					printf("\n");
				}
				if (attempt == 0)
				{
					printf("ERROR:  Login failed!\n");
					printf("\n");
					pauseExecution();
					flag2 = 0;
				}
			} while (flag2);
			break;
		}
	} while (flag1);
	return posn;
}

void  menuAgent(struct AccountTicketingData* acc_tic, const struct Account* acc)
{

	int option;
	int i;
	int account_num = 0, max = 0;
	int flag = 1;
	int posn, character = 0;
	int count1 = 0, count2 = 0, tics = 0, accs = 0;
    int removed_msg = 0, closed_msg = 0, removed_acc = 0, total_removed_msg = 0;
	int total_removed_tickets = 0, total_closed_tickets = 0;
	char confirm = 0;

	do
	{
		printf("AGENT: %s (%d)\n", acc->login.acc_holder, acc->account_num);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		option = getIntFromRange(0, 12);
		switch (option)
		{

		case 1:
			printf("\n");

			posn = findAccountIndexByAcctNum(0, acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE, 0);

			if (posn < 0)
			{
				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
			else
			{

				for (i = 0; i < acc_tic->ACCOUNT_MAX_SIZE; i++)
				{
					if (acc_tic->accounts[i].account_num > max)
					{
						max = acc_tic->accounts[i].account_num;
					}
				}
				acc_tic->accounts[posn].account_num = max + 1;

				getAccount(&acc_tic->accounts[posn]);
				getUserLogin(&acc_tic->accounts[posn]);
				getDemographic(&acc_tic->accounts[posn]);

				printf("*** New account added! ***\n\n");
				pauseExecution();
			}

			break;
		case 2:
			printf("\n");
			do
			{
				posn = findAccountIndexByAcctNum(account_num, acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE, 1);

			} while (posn == -1);
			updateAccount(&acc_tic->accounts[posn]);
			break;

		case 3:
			printf("\n");
			printf("Enter the account#: ");
			account_num = getPositiveInteger();

			if (account_num == acc->account_num)
			{
				printf("\n");
				printf("ERROR: You can't remove your own account!\n\n");
				clearStandardInputBuffer();
				pauseExecution();
			}
			else
			{
				posn = findAccountIndexByAcctNum(account_num, acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE, 0);
				displayAccountDetailHeader();
				displayAccountDetailRecord(&acc_tic->accounts[posn]);

				printf("\n");

				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				character = getCharOption("YN");
				printf("\n");

				count1 = 0;
				removed_msg = 0;
				if (character == 'Y')
				{
					count1 = removeTickets(acc_tic, &acc_tic->accounts[posn], &removed_msg);
					total_removed_tickets = total_removed_tickets + count1;
					total_removed_msg = total_removed_msg + removed_msg;
					archiveAccounts(&acc_tic->accounts[posn]);
					acc_tic->accounts[posn].account_num = 0;

					removed_acc++;
					printf("*** Account Removed! ***\n\n");

					pauseExecution();
				}
				else
				{
					printf("*** No changes made! ***\n\n");
					pauseExecution();
				}
			}
			break;

		case 4:
			printf("\n");
			displayAllAccountSummaryRecords(acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;

		case 5:
			printf("\n");
			displayAllAccountDetailRecords(acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;

		case 6:
			printf("\n");
			displayNewMessage(acc_tic);
			break;

		case 7:
			printf("\n");
			displayActiveMessage(acc_tic);
			break;

		case 8:
			printf("\n");
			displayAgentTicketMessage(acc_tic);
			break;

		case 9:
			printf("\n");
			modifyAgentTicket(acc_tic, &acc->account_num);
			break;

		case 10:
			printf("\n");
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			confirm = getCharOption("YN");
			printf("\n");
			if (confirm == 'Y')
			{
				count2 = 0;

				for (i = 0; i < acc_tic->TICKET_MAX_SIZE; i++)
				{
					if (acc_tic->tickets[i].status == 0 && acc_tic->tickets[i].number != 0)
					{
						count2++;
						archiveClosedTickets(&acc_tic->tickets[i]);
						total_closed_tickets = total_closed_tickets + count2;

						closed_msg = closed_msg + acc_tic->tickets[i].counter;

						acc_tic->tickets[i].number = 0;
						acc_tic->tickets[i].acc_num = 0;
					}
				}

				printf("*** %d tickets archived ***\n\n", count2);
				pauseExecution();

			}
			break;
		case 11:
			printf("\n");
			printf("There are %d account(s) currently archived.\n\n", removed_acc);
			pauseExecution();
			break;
		case 12:
			printf("\n");
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", total_removed_tickets + count2, closed_msg + total_removed_msg);
			pauseExecution();
			break;
		case 0:		
			printf("\n");
			printf("Saving session modifications...\n");
			accs = saveAccounts(acc_tic->accounts, acc_tic->ACCOUNT_MAX_SIZE);
			printf("   %d account saved.\n", accs);
			tics = saveTickets(acc_tic->tickets, acc_tic->TICKET_MAX_SIZE);
			printf("   %d tickets saved.\n", tics);
			printf("### LOGGED OUT ###\n\n");
			flag = 0;
			break;
		}
	} while (flag);
}


void applicationStartup(struct AccountTicketingData* tic)
{
	int posn;
	do
	{
		posn = menuLogin(tic->accounts, tic->ACCOUNT_MAX_SIZE);

		if (posn != -1)
		{
			if (tic->accounts[posn].account_type == 'C')
			{
				customerMenu(tic->tickets, &tic->accounts[posn], tic->TICKET_MAX_SIZE);
			}
			else if (tic->accounts[posn].account_type == 'A')
			{
				menuAgent(tic, &tic->accounts[posn]);
			}
		}
		else
		{
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
		}
	} while (posn != -1);
}

void  customerMenu(struct Ticket* tic, struct Account* acc, int size)
{
	int option = 0;
	
	int flag = 1;
	int k = 0;

	do
	{

		printf("CUSTOMER: %s (%d)\n", acc->login.acc_holder, acc->account_num);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");

		option = getIntFromRange(0, 4);
		printf("\n");

		switch (option)
		{
		case 1:

			displayAccountDetailHeader();
			displayAccountDetailRecord(acc);
			printf("\n");
			pauseExecution();
			break;

		case 2:
			addTicket(tic, acc, size);
			break;

		case 3:

			updateCustTic(tic, acc, size);
			break;
		case 4:
			displayCustMessage(tic, acc, size);
			break;
		case 0:

			k = saveTickets(tic, size);
			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", k);
			printf("### LOGGED OUT ###\n\n");
			flag = 0;
			break;
		}
	} while (flag);
}