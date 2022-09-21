#include <stdio.h>
#include "types.h"
#include "card.h"
#include <time.h>
#include <math.h>
#ifndef TERMINAL_FILE
#define TERMINAL_FILE
#define MaxAmount 10000
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	OK_T, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char* p = termData;
	*(p + 8) = (tm.tm_mday / 10) + 48;
	*(p + 9) = (tm.tm_mday % 10) + 48;
	*(p + 10) = '/';
	*(p + 11) = ((tm.tm_mon + 1) / 10) + 48;
	*(p + 12) = ((tm.tm_mon + 1) % 10) + 48;
	*(p + 13) = '/';
	*(p + 14) = ((tm.tm_year + 1900) / 1000) + 48;
	*(p + 15) = (((tm.tm_year + 1900) % 1000)/100) + 48;
	*(p + 16) = ((((tm.tm_year + 1900) % 1000) % 100)/10) + 48;
	*(p + 17) = ((((tm.tm_year + 1900) % 1000) % 100) % 10) + 48;
	*(p + 18) = 0;
	return OK_T;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {
	char* p1 = cardData; char* p2 = termData;
	int exp = 120 * (*(p1 + 48)) + 12 * (*(p1 + 49)) + 10 * (*(p1 + 45))+ (*(p1 + 46));
	int cur = 120 * (*(p2 + 16)) + 12 * (*(p2 + 17)) + 10 * (*(p2 + 11)) + (*(p2 + 12));
	return (exp < cur ? EXPIRED_CARD : OK_T);
	
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("%s", "Transaction Amount: ");
	float* p = termData;
	char i = 0; char ret = 0;
	char CharBuffer[6]; CharBuffer[0] = 0;
	while (ret != 10) {
		scanf("%c", &ret);
		if (i < 6) { CharBuffer[i] = ret; }
		i++;
	}
	float Amount = 0;
	for (int j = 0; j < i - 1; j++) {
		if ((CharBuffer[j] < 48) || (CharBuffer[j] > 57)) { return INVALID_AMOUNT; }
		Amount += pow(10, i - j - 2) * (CharBuffer[j] - 48);
	}
	*p = Amount;
	return ((Amount<=0) ? INVALID_AMOUNT : OK_T);
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	float* p = termData;
	return ((*p) > (*(p + 1)) ? EXCEED_MAX_AMOUNT : OK_T);
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	float* p = termData;
	*(p+1) = MaxAmount;
	return ((MaxAmount <= 0) ? INVALID_MAX_AMOUNT : OK_T);
}
#endif