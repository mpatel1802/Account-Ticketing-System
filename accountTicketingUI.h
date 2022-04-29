#pragma once
/*==================================================
  Assignment #2 Milestone #2
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_


#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

void displayNewMessage();
void displayCustMessage();
void displayActiveMessage();
void displayTicketHeader(void);
void displayAccountSummaryHeader(void);

void displayAccountDetailHeader(void);


void displayAccountSummaryRecord();

void displayAccountDetailRecord();

void applicationStartup();

int menuLogin();

void menuAgent();

int findAccountIndexByAcctNum();

void displayAllAccountSummaryRecords();

void displayAllAccountDetailRecords();

void pauseExecution(void);

void  customerMenu();



struct AccountTicketingData
{
	struct Account* accounts;
	const int ACCOUNT_MAX_SIZE;
	struct Ticket* tickets;
	const int TICKET_MAX_SIZE;
};




#endif