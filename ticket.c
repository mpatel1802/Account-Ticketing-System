/*==================================================
  Assignment #2 Milestone #3
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "accountTicketingUI.h"



int findTicketIndex(int tic_num, const struct Ticket tic[], int size, int input_ticket_num)
{
	int i = 0;
	int posn = -1	;
	if (input_ticket_num)
	{
		printf("Enter ticket number: ");
		tic_num = getPositiveInteger();
		printf("\n");
	}
	for (i = 0, posn = -1; posn < 0 && i < size; i++)
	{
		if (tic_num == tic[i].number)
		{
			posn = i;
		}
	}
	return posn;
}

int removeTickets(const struct AccountTicketingData* acc_tic, struct Account* accountInfo, int* removed_tickets)
{
	int i = 0;
	int result = 0;
	for (i = 0; i < acc_tic->TICKET_MAX_SIZE; i++)
	{
		if (acc_tic->tickets[i].acc_num == accountInfo->account_num)
		{
      		if (acc_tic->tickets[i].status == 1)
			{
				acc_tic->tickets[i].number = 0;
				acc_tic->tickets[i].acc_num = 0;
			}
			else
			{
				*removed_tickets = acc_tic->tickets[i].counter;
				result = archiveRemovedClosedTickets(&acc_tic->tickets[i]);
				acc_tic->tickets[i].number = 0;
				acc_tic->tickets[i].acc_num = 0;
			}
		}
	}
	return result;
}

void addTicket(struct Ticket* newCustTic, const struct Account* accountInfo, int size)
{
	int posn = 0, max = 0;
	int i = 0;
	

	posn = findTicketIndex(0, newCustTic, size, 0);

	if (posn < 0)
	{
		printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
		pauseExecution();
	}
	else
	{

		for (i = 0; i < posn; i++)
		{
			if (newCustTic[i].number > max)
			{
				max = newCustTic[i].number;
			}
		}
		newCustTic[posn].number = max + 1;
		newCustTic[posn].acc_num = accountInfo->account_num;
		newCustTic[posn].counter = 1;
		newCustTic[posn].status = 1;
		newCustTic[posn].messageInfo->account_author_type = accountInfo->account_type;

		printf("New Ticket (Ticket#:0%d)\n", newCustTic[posn].number);
		printf("----------------------------------------\n");
		printf("Enter the ticket SUBJECT (%d chars. maximum): ", 30);
		getCString(newCustTic[posn].subject, 1, 30);
		printf("\n");
		printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", 150);
		
		getCString(newCustTic[posn].messageInfo[newCustTic[posn].counter - 1].message_details, 1, 150);
		for (i = 0; i < 30; i++)
		{
			newCustTic[posn].messageInfo[newCustTic[posn].counter - 1].name[i] = accountInfo->login.acc_holder[i];
		}

		printf("\n");
		printf("*** New ticket created! ***\n\n");
		pauseExecution();

	}
}

void updateCustTic(struct Ticket* newCustTic, struct Account* acc, int size)
{
	int posn = 0, ticket_num = 0;
	do
	{
		posn = findTicketIndex(ticket_num, newCustTic, size, 1);

	} while (posn == -1);

	if (newCustTic[posn].acc_num != acc->account_num)
	{
		printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
		pauseExecution();
	}
	else
	{
		if (newCustTic[posn].status == 1)
		{
			custTicketUpdate(&newCustTic[posn], acc);
		}
		else
		{
			printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
			pauseExecution();
		}
	}
}

void custTicketUpdate(struct Ticket* tic, struct Account* acc)
{
	int option = 0;
	int flag1 = 1;
	char close = 0;
	char msg = 0;
	int i = 0;

	do
	{

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tic->number);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tic->status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tic->subject);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		option = getIntFromRange(0, 3);
		printf("\n");

		switch (option)
		{
		case 1:
			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", 30);
			getCString(tic->subject, 0, 30);
			printf("\n");
			break;
		case 2:
			if (tic->counter >= 20)
			{
				printf("ERROR: Message limit has been reached, call ITS Support!\n");
			}
			else
			{
				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", 150);
				
				tic->counter = tic->counter + 1;
				getCString(tic->messageInfo[tic->counter - 1].message_details, 0, 150);
				for (i = 0; i < 30; i++)
				{
					tic->messageInfo[tic->counter - 1].name[i] = acc->login.acc_holder[i];
				}
			}
			printf("\n");
			break;
		case 3:
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			close = getCharOption("YN");
			if (close == 'Y')
			{
				tic->status = 0;
			}
			else
			{
				tic->status = 1;
			}
			printf("\n");
			if (tic->counter < 20)
			{
				printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
				msg = getCharOption("YN");
				printf("\n");
				if (msg == 'Y')
				{
					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", 150);
					
					tic->counter = tic->counter + 1;
					getCString(tic->messageInfo[tic->counter - 1].message_details, 0, 150);
					for (i = 0; i < 30; i++)
					{
						tic->messageInfo[tic->counter - 1].name[i] = acc->login.acc_holder[i];
					}
					printf("\n");
				}
			}
			if (close == 'Y')
			{
				printf("*** Ticket closed! ***\n\n");
				pauseExecution();
				flag1 = 0;
			}
			break;
		case 0:
			pauseExecution();
			flag1 = 0;
			break;
		}
	} while (flag1);
}

void displayAgentTicketMessage(const struct AccountTicketingData* agent_tic)
{

	int i = 0, j = 0;
	int flag = 1, flag1 = 1, ticket_Num;
	int k = 0;
	do
	{
		flag1 = 1;
		displayTicketHeader();

		for (i = 0; i < agent_tic->TICKET_MAX_SIZE; i++)
		{
			if (agent_tic->tickets[i].status == 0 && agent_tic->tickets[i].number != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", agent_tic->tickets[i].number, agent_tic->tickets[i].acc_num, agent_tic->tickets[i].messageInfo->name, agent_tic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", agent_tic->tickets[i].subject, agent_tic->tickets[i].counter);
			}
		}

		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{
			ticket_Num = getInteger();
			if (ticket_Num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (ticket_Num == 0)
			{
				printf("\n");
				flag = 0;
				flag1 = 0;
			}
			else
			{
				printf("\n");
				flag1 = 0;
			}
		} while (flag1);
		flag1 = 1;

		if (ticket_Num != 0)
		{
			k = 0;
			for (i = 0; i < agent_tic->TICKET_MAX_SIZE && flag1; i++)
			{
				if (agent_tic->tickets[i].number == ticket_Num && agent_tic->tickets[i].number != 0)
				{
					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", agent_tic->tickets[i].number, agent_tic->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", agent_tic->tickets[i].subject);
					printf("================================================================================\n");

					for (j = 0; j < agent_tic->tickets[i].counter; j++)
					{
						printf("%s (%s):\n", agent_tic->tickets[i].messageInfo[j].account_author_type == 'A' ? "AGENT" : "CUSTOMER", agent_tic->tickets[i].messageInfo[j].name);
						printf("   %s\n\n", agent_tic->tickets[i].messageInfo[j].message_details);

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
					flag1 = 0;
				}
			}
		}
		if (ticket_Num != 0)
		{
			if (flag1)
			{
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();
			}
		}
	} while (flag);
}


void modifyAgentTicket(const struct AccountTicketingData* agent_tic, struct Account* acc)
{
	int posn = 0, ticket_Num = 0;
	do
	{
		posn = findTicketIndex(ticket_Num, agent_tic->tickets, agent_tic->TICKET_MAX_SIZE, 1);
	} while (posn == -1);
	menuAgentTicketModification(&agent_tic->tickets[posn], acc);
}

void menuAgentTicketModification(struct Ticket* tic, struct Account* acc)
{
	int option = 0, flag1 = 1;
	char close = 0, reopen = 0, leave_msg = 0;
	int i = 0;
	do
	{
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tic->number);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tic->status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tic->subject);
		printf("Acct#   : %d\n", tic->acc_num);
		printf("%s: %s\n", tic->messageInfo->account_author_type == 'A' ? "AGENT" : "Customer", tic->messageInfo->name);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		option = getIntFromRange(0, 3);
		printf("\n");
		switch (option)
		{
		case 1:
			if (tic->status == 0)
			{
				printf("ERROR: Ticket is closed - new messages are not permitted.\n");
			}
			else
			{
				if (tic->counter >= 20)
				{
					printf("ERROR: Message limit has been reached, call ITS Support!\n");
				}
				else
				{
					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", 150);
					
					tic->counter = tic->counter + 1;
					getCString(tic->messageInfo[tic->counter - 1].message_details, 0, 150);
					for (i = 0; i < 30; i++)
					{

						tic->messageInfo[tic->counter - 1].name[i] = acc->login.acc_holder[i];
					}
					tic->messageInfo[tic->counter - 1].account_author_type = acc->account_type;	
				}
			}
			printf("\n");
			break;
		case 2:
			if (tic->status == 0)
			{
				printf("ERROR: Ticket is already closed!\n\n");
			}
			else
			{
				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				close = getCharOption("YN");

				if (close == 'Y')
				{
					tic->status = 0;
				}
				else
				{
					tic->status = 1;
				}
				printf("\n");
				if (tic->counter < 20)
				{
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					leave_msg = getCharOption("YN");
					printf("\n");
					if (leave_msg == 'Y')
					{
						printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", 150);
						
						tic->counter = tic->counter + 1;
						getCString(tic->messageInfo[tic->counter - 1].message_details, 0, 150);
						for (i = 0; i < 30; i++)
						{

							tic->messageInfo[tic->counter - 1].name[i] = acc->login.acc_holder[i];
						}
						tic->messageInfo[tic->counter - 1].account_author_type = acc->account_type;
						printf("\n");
					}
				}
				if (close == 'Y')
				{
					printf("*** Ticket closed! ***\n\n");
				}
			}
			break;
		case 3:
			if (tic->status == 0)
			{
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				reopen = getCharOption("YN");
				if (reopen == 'Y')
				{
					tic->status = 1;
					printf("\n*** Ticket re-opened! ***\n");
					printf("\n");
				}
				else
				{
					tic->status = 0;
					printf("\n");
				}
			}
			else
			{
				printf("ERROR: Ticket is already active!\n\n");
			}
			break;
		case 0:
			flag1 = 0;
			break;
		}
	} while (flag1);
}

int loadTickets(struct Ticket tic[], int size)
{
	int tickets = 0, field , i = 0;
	FILE* fp = fopen(TICKETSFILE, "r");

	if (fp != NULL)
	{
		do
		{
			field = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
				&tic[tickets].number,
				&tic[tickets].acc_num,
				&tic[tickets].status,
				tic[tickets].subject,
				&tic[tickets].counter);

			if (field == 5)
			{
				if (tic[tickets].number > 0)
				{
					for (i = 0, field = 3; field == 3 && i < tic[tickets].counter; i++)
					{

						field = fscanf(fp, "%c|%30[^|]|%150[^|]|", &tic[tickets].messageInfo[i].account_author_type,
							tic[tickets].messageInfo[i].name,
							tic[tickets].messageInfo[i].message_details);
					}
				}
				tickets++;
			}

		} while (!feof(fp) && tickets < size);
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return tickets;
}



int saveTickets(const struct Ticket tic[], int size)
{
	int i = 0, j = 0, tickets = 0;
	FILE* fp = fopen(TICKETSFILE, "w");

	if (fp != NULL)
	{
		for (i = 0; i < size; i++)
		{
			if (tic[i].number > 0)
			{

				fprintf(fp, "%d|%d|%d|%s|%d|", tic[i].number, tic[i].acc_num, tic[i].status, tic[i].subject, tic[i].counter);
				if (tic[i].number > 0)
				{
					for (j = 0; j < tic[i].counter; j++)
					{

						fprintf(fp, "%c|%s|%s|", tic[i].messageInfo[j].account_author_type,
							tic[i].messageInfo[j].name,
							tic[i].messageInfo[j].message_details);
						if (j == tic[i].counter - 1)
						{
							fprintf(fp, "\n");
						}
					}
				}
				tickets++;
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
	return tickets;
}

int archiveRemovedClosedTickets(const struct Ticket* tic)
{
	int i = 0;
	int result = 0;
	FILE* fp = fopen(TICKETSARCFILE, "a");

	if (fp != NULL)
	{
		fprintf(fp, "%d|%d|%d|%s|%d|", tic->number, tic->acc_num, tic->status, tic->subject, tic->counter);
		if (tic->number > 0)
		{
			for (i = 0; i < tic->counter; i++)
			{
				result = fprintf(fp, "%c|%s|%s|", tic->messageInfo[i].account_author_type,
					tic->messageInfo[i].name,
					tic->messageInfo[i].message_details);

				if (i == tic->counter - 1)
				{
					fprintf(fp, "\n");
				}
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
	return result > 0 ? 1 : 0;
}

void archiveClosedTickets(const struct Ticket* tic)
{
	int i = 0;
	FILE* fp = fopen(TICKETSARCFILE, "a");
	if (fp != NULL)
	{
		fprintf(fp, "%d|%d|%d|%s|%d|", tic->number, tic->acc_num, tic->status, tic->subject, tic->counter);
		if (tic->number > 0)
		{
			for (i = 0; i < tic->counter; i++)
			{
				fprintf(fp, "%c|%s|%s|", tic->messageInfo[i].account_author_type,
					tic->messageInfo[i].name,
					tic->messageInfo[i].message_details);
				if (i == tic->counter - 1)
				{
					fprintf(fp, "\n");
				}
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
}