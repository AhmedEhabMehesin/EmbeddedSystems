#include <stdio.h>
#include "terminal.h"
#ifndef SERVER_FILE
#define SERVER_FILE
typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
typedef enum EN_serverError_t
{
	OK_S, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
ST_accountsDB_t Accounts[255];
ST_accountsDB_t AccountA = { .balance = 12000,.primaryAccountNumber = "01234567890123456" };
ST_accountsDB_t AccountB = { .balance = 10000,.primaryAccountNumber = "11111111111111111" };
ST_accountsDB_t AccountC = { .balance = 1000,.primaryAccountNumber = "11223344556677889" };
ST_accountsDB_t AccountD = { .balance = 90000,.primaryAccountNumber = "11122233344455566" };
ST_accountsDB_t* AccountsPointer = Accounts;
char AccountIndex = 0;
char TransactionIndex = 0;
void AssignAccounts() {
	*(AccountsPointer) = AccountA;
	*(AccountsPointer+1) = AccountB;
	*(AccountsPointer+2) = AccountC;
	*(AccountsPointer+3) = AccountD;
}
ST_transaction_t Transactions[255];
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	EN_transState_t ret = DECLINED_STOLEN_CARD;
	if (isValidAccount(&((*transData).cardHolderData)) == OK_S) {
		ret = DECLINED_INSUFFECIENT_FUND;
		if (isAmountAvailable(&((*transData).terminalData)) == OK_S) {
			(*(AccountsPointer + AccountIndex)).balance -= (*transData).terminalData.transAmount;
			ret= APPROVED;
		}
	}

	ST_transaction_t Current;
	Current.cardHolderData = (*transData).cardHolderData;
	Current.terminalData = (*transData).terminalData;
	Current.transactionSequenceNumber = TransactionIndex;
	Current.transState = ret;
	saveTransaction(&Current);
	return ret;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	char* AccountsCharPointer = Accounts;
	char* CardCharPointer = cardData;
	for (int i = 0; i < 255; i++) {
		char iden = 1;
		for (char j = 0; j < 17; j++) {
			iden = (*(AccountsCharPointer + i * 24 + j + 4) == *(CardCharPointer + 25 + j) ? iden : 0);
		}
		if (iden == 1)
		{
			AccountIndex = i;
			return OK_S;
		}
	}
	return DECLINED_STOLEN_CARD;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	float Balance = (*(AccountsPointer + AccountIndex)).balance;
	float Trans = (*(termData)).transAmount;
	if (Balance >= Trans) {
		return OK_S;
	}
	return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	ST_transaction_t* TransactionPointer = Transactions;
	if (TransactionIndex > 254) { return SAVING_FAILED; }
	*(TransactionPointer + TransactionIndex) = (*transData);
	TransactionIndex++;
	return OK_S;
}
#endif