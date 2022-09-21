#define _CRT_SECURE_NO_WARNINGS
#ifndef APP_FILE
#define APP_FILE
#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
enum CardOp {
	Name, Exp, PAN
};
void CardInfo(char Info, ST_cardData_t* Card)
{
	if (Info == Name) {
		if (getCardHolderName(Card) == WRONG_NAME) {
			printf("%s", "Try again.\n"); CardInfo(Name, Card);
		}
	}
	if (Info == Exp) {
		if (getCardExpiryDate(Card) == WRONG_EXP_DATE) {
			printf("%s", "Try again.\n"); CardInfo(Exp, Card);
		}
	}
	if (Info == PAN) {
		if (getCardPAN(Card) == WRONG_PAN) {
			printf("%s", "Try again.\n"); CardInfo(PAN, Card);
		}
	}
}
void appStart() {
	
	printf("Welcome to Damietta Bank! \n");
	ST_cardData_t Card;
	ST_terminalData_t Terminal;
	ST_transaction_t Transaction;
	getTransactionDate(&Terminal); //gets computer date
	CardInfo(Name, &Card); //if format is invalid, it loops until valid
	CardInfo(Exp, &Card); 
	if (isCardExpired(&Card, &Terminal) == EXPIRED_CARD) {
		printf("Card Expired!\n"); appStart();
	}
	CardInfo(PAN, &Card);
	setMaxAmount(&Terminal);
	getTransactionAmount(&Terminal);
	if ( isBelowMaxAmount(&Terminal) == EXCEED_MAX_AMOUNT) {
		printf("Amount Exceeded!\n"); appStart();
	}
	Transaction.cardHolderData = Card;
	Transaction.terminalData = Terminal;
	EN_transState_t ret = recieveTransactionData(&Transaction);
	printf("%s", (ret == APPROVED) ? "Approved.\n" : ((ret == DECLINED_INSUFFECIENT_FUND) ? "Low Balance.\n" : "Stolen.\n"));
	appStart();
	
}
#endif