/*
 * terminal.c
 *
 *  Created on: Aug 15, 2023
 *      Author: PC
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<dos.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("enter your transaction date\n");
    fflush(stdout);
    fflush(stdin);
    fgets(termData->transactionDate, 13, stdin); // size of :length of array
    uint8_t len = strlen(termData->transactionDate);
    uint8_t size = sizeof(termData->transactionDate);

    if (len == Null || (len - 1) < 10 || (len - 1) >= size ||termData->transactionDate[2]!='/' ||termData->transactionDate[5]!='/')
    {
//    	printf("WRONG_Transaction date"); // for test function
        return WRONG_DATE;
    }
//    printf("accept_Transaction date"); // for test function
    return TERMINAL_OK;

}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
//    uint8_t result = getCardExpiryDate(cardData->cardExpirationDate);
//
//    if (result == WRONG_EXP_DATE)
//    {
//        printf("wrong EXP_DATE format\n");
//        return WRONG_EXP_DATE;
//    }

//    uint8_t the_transaction_date_result = getTransactionDate(termData->transactionDate);
//
//    if (the_transaction_date_result == WRONG_DATE)
//    {
//        printf("wrong transactionDate\n");
//        return WRONG_DATE;
//    }

    if (cardData->cardExpirationDate[3] > termData->transactionDate[6])
    {

//        printf("TERMINAL_OK");
        return TERMINAL_OK;
    }
    else if (cardData->cardExpirationDate[3] == termData->transactionDate[6] && cardData->cardExpirationDate[3] >= termData->transactionDate[8] && cardData->cardExpirationDate[4] > termData->transactionDate[9])
    {
//        printf("TERMINAL_OK");
        return TERMINAL_OK;
    }

    else
    {
        printf("EXPIRED_CARD");
        return EXPIRED_CARD;
    }

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("enter your transaction amount\n");
    fflush(stdout);
    scanf("%f", &(termData->transAmount));
    if (termData->transAmount <= 0)
    {
//    	printf("INVALID_AMOUNT"); // for test function
        return INVALID_AMOUNT;
    }
//    printf("TERMINAL_OK");        // for test function
    return TERMINAL_OK;

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
//    	printf("EXCEED_MAX_AMOUNT\n"); // for test function
        return EXCEED_MAX_AMOUNT;
    }
//    printf("TERMINAL_OK\n"); // for test function
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    termData->maxTransAmount=maxAmount;
    if (termData->maxTransAmount<=0)
    {
//    	printf("INVALID_MAX_AMOUNT"); // for test function
        return INVALID_MAX_AMOUNT ;
    }
//    printf("TERMINAL_OK");           // for test function
    return TERMINAL_OK;
}
/*TESTS FUNCTIONS*/
//void getTransactionDateTest(void)
//{
//    getTransactionDate(&(s5.terminalData));
//    // 26/05/2022
//
//}
//
//void isCardExpriedTest(void)
//{
//    isCardExpired(&(s5.cardHolderData),&(s5.terminalData));
//}
//
//void getTransactionAmountTest(void)
//{
//    getTransactionAmount(&(s5.terminalData));
//    // 0 or 0< invalid
//}
//
//void setMaxAmountTest(void)
//{
//    setMaxAmount(&(s5.terminalData),1000);
//    // 0 or 0< invalid
//}
//
//void isBelowMaxAmountTest(void)
//{
//    isBelowMaxAmount(&(s5.terminalData));
//    // trans amount < max amount -<ok
//}

