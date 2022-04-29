#pragma once

/*==================================================
  Assignment #2 Milestone #2
  ==================================================
  Name    : Mann Patel
  ID      : 134633205
  Email   : mpatel394@myseneca.ca
  Section : NEE
  */
#ifndef TICKET_H_
#define TICKET_H_
#define TICKETSFILE "tickets.txt"
#define TICKETSARCFILE "tickets_arc.txt"


int findTicketIndex();

void custTicketUpdate();

void menuAgentTicketModification();

void addTicket();

void displayAgentTicketMessage();

void updateCustTic();

int removeTickets();

void modifyAgentTicket();

struct Message
{
	char account_author_type;
	char name[31];
	char message_details[151];
};

struct Ticket
{
	int number;
	int acc_num;
	int status;
	char subject[31];
	int counter;
	struct Message messageInfo[31];
};

int saveTickets();


int loadTickets();


int archiveRemovedClosedTickets();


void archiveClosedTickets();
#endif 
