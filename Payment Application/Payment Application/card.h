#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "types.h"
#ifndef CARD_FILE
#define CARD_FILE

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	 
	printf("%s", "Card Holder Name: ");
	char* p = cardData;
	char i = 0; char ret = 0;
	while (ret != 10) {
		scanf("%c", &ret);
		if (i < 25) {*(p + i) = ret;}
		i++;
	}
	return ((i <21 || i>25) ? WRONG_NAME : OK);
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("%s", "Card Expiry Date: ");
	char* p = cardData;
	char i = 0; char ret = 0;
	while (ret != 10) {
		scanf("%c", &ret);
		if (i < 5) { *(p +45+ i) = ret; }
		i++;
	}
	*(p + 50) = 0;
		return ((i == 6) && ((*(p + 45)) >= 48 && (*(p + 45)) <= 57
			&& (*(p + 46)) >= 48 && (*(p + 46)) <= 57
			&& (*(p + 47)) == '/'
			&& (*(p + 48)) >= 48 && (*(p + 48)) <= 57
			&& (*(p + 49)) >= 48 && (*(p + 49)) <= 57)
			? OK : WRONG_EXP_DATE);

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("%s", "Card PAN: ");
	char* p = cardData;
	char i = 0; char ret = 0;
	while (ret != 10) {
		scanf("%c", &ret);
		if (i < 20) { *(p + 25+i) = ret; }
		i++;
	}
	return ((i < 17 || i>21) ? WRONG_PAN : OK);
}
#endif