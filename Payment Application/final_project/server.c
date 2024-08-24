/*
 * server.c
 *
 *  Created on: Aug 15, 2023
 *      Author: PC
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
uint8_t flag=0;
extern ST_transaction s5;
#define BALANCE 100
ST_accountsDB_t ptrrrr; // for test function

// ST_accountsDB_t accountsDB[255]={0};
ST_accountsDB_t accountsDB[]=
{
    {2000.0, RUNNING, "8989374615436851"},
    {1000.0, BLOCKED, "7989374615436851"},
    {3000.0, RUNNING, "6989374615436851"},
    {4000.0, BLOCKED, "5989374615436851"},
    {5000.0, RUNNING, "4989374615436851"},

};
extern ST_transaction transactions_DB[255];
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
//    uint8_t result= getCardPAN((cardData));
//    if (result==WRONG_PAN )
//    {
//        return WRONG_PAN ;
//    }

    for (uint8_t j = 0; j < 5; j++)
    {

        for (uint8_t i = 0; i < 16; i++)
        {
            if (accountsDB[j].primaryAccountNumber[i] == cardData->primaryAccountNumber[i])
            {
                // accountRefrence=accountsDB[j];

                flag = 1;
            }
            else
            {
                // accountRefrence=NULL;

                flag = 0;
                break;
                // return ACCOUNT_NOT_FOUND;
            }
        }
        if (flag == 1)
        {
            accountRefrence->balance = accountsDB[j].balance;
            for (uint8_t i = 0; i < strlen(accountRefrence->primaryAccountNumber); i++)
            {
                accountRefrence->primaryAccountNumber[i] = accountsDB[j].primaryAccountNumber[i];
            }


            accountRefrence->state = accountsDB[j].state;
//            printf("%d\n", j);
            break;
        }
    }
    if (flag == 1)
    {
//    	printf("SERVER_OK"); // for test function
        return SERVER_OK;
    }
    else
    {
        accountRefrence = NULL;
//        printf("ACCOUNT_NOT_FOUND"); // for test function
        return ACCOUNT_NOT_FOUND;
    }
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    // termData->transAmount = 30;
//    getTransactionAmount(&(termData->transAmount));
    accountRefrence->balance = BALANCE;
    if (s5.terminalData.transAmount > accountRefrence->balance)
    {
//    	printf("LOW_BALANCE"); // for test function
        return LOW_BALANCE;
    }
    else
    {
//        printf("SERVER_OK");  // for test function
        return SERVER_OK;
    }
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence->state == BLOCKED)
    {
//    	printf("BLOCKED_ACCOUNT\n"); // for test function
        return BLOCKED_ACCOUNT;
    }
    else
    {
//        printf("SERVER_OK\n"); // for test function
        return SERVER_OK;
    }
}

EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
    // ST_cardData_t *s1;
    ST_accountsDB_t ptr;

    // isValidAccount(&(s5.cardHolderData), ptr);
    uint8_t result = isValidAccount(&(s5.cardHolderData), &ptr);
    if (result == ACCOUNT_NOT_FOUND)
    {
        printf("FRAUD_CARD");
    }
    else
    {
//        printf("APPROVD1\n");
        uint8_t result2 = isAmountAvailable(&(s5.terminalData), &ptr);
        if (result2 == LOW_BALANCE)
        {
            printf("DECLINED_INSUFFECIENT_FUND\n");
        }
        else
        {
//            printf("APPROVD2\n");
            uint8_t result3= isBlockedAccount(&ptr);
            if (result3==BLOCKED_ACCOUNT )
            {
                printf("DECLINED_STOLEN_CARD\n");
            }
            else
            {
            	uint8_t res= saveTransaction(transactions_DB);
                if (res == SAVING_FAILED)
                {
                    return INTERNAL_SERVER_ERROR;
                }
            	listSavedTransactions();
                printf("APPROVD3");
            }

        }
    }




}


EN_serverError_t saveTransaction(ST_transaction *transData)
{
    if (s5.transactionSequenceNumber >255)
    {
        printf("SAVING_FAILED");
        return SAVING_FAILED;
    }
    else
    {
        uint8_t i;
        for (i = 0; i < strlen(s5.cardHolderData.cardHolderName); i++)
        {
            transData[s5.transactionSequenceNumber].cardHolderData.cardHolderName[i] = s5.cardHolderData.cardHolderName[i];
        }

        for (i = 0; i < strlen(s5.cardHolderData.cardExpirationDate); i++)
        {
            transData[s5.transactionSequenceNumber].cardHolderData.cardExpirationDate[i] = s5.cardHolderData.cardExpirationDate[i];
        }

        for (i = 0; i < strlen(s5.cardHolderData.primaryAccountNumber); i++)
        {
            transData[s5.transactionSequenceNumber].cardHolderData.primaryAccountNumber[i] = s5.cardHolderData.primaryAccountNumber[i];
        }

        for (i = 0; i < strlen(s5.terminalData.transactionDate); i++)
        {
            transData[s5.transactionSequenceNumber].terminalData.transactionDate[i] = s5.terminalData.transactionDate[i];
        }

        transData[s5.transactionSequenceNumber].terminalData.transAmount = s5.terminalData.transAmount;
        transData[s5.transactionSequenceNumber].transState = s5.transState;
        transData[s5.transactionSequenceNumber].terminalData.maxTransAmount = s5.terminalData.maxTransAmount; /********************************/
        s5.transactionSequenceNumber++;

        return SERVER_OK;
    }
}

void listSavedTransactions(void)
{
    for (uint8_t i = 0; i < s5.transactionSequenceNumber; i++)
    {
        printf("#########################\n");
        printf("Transaction Sequence Number: %d\n\
Transaction Date: %s\n\
Transaction Amount: %f\n\
Transaction State: %d\n\
Terminal Max Amount: %f\n\
Cardholder Name: %s\n\
PAN: %s\n\
Card Expiration Date: %s\n",transactions_DB[i].transactionSequenceNumber, transactions_DB[i].terminalData.transactionDate, transactions_DB[i].terminalData.transAmount,transactions_DB[i].transState,transactions_DB[i].terminalData.maxTransAmount, \
        transactions_DB[i].cardHolderData.cardHolderName,transactions_DB[i].cardHolderData.primaryAccountNumber,transactions_DB[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");
    }
}

/*TESTS FUNCTIONS*/
//void isValidAccountTest(void)
//{
//    isValidAccount(&(s5.cardHolderData), &ptrrrr);
//}
//
//void isBlockedAccountTest(void)
//{
//    isBlockedAccount(&ptrrrr);
//}
//
//void isAmountAvailableTest(void)
//{
//    isAmountAvailable(&(s5.terminalData), &ptrrrr);
//    // 10 -< low balance , balance=20
//}
//
//void saveTransactionTest(void)
//{
//    saveTransaction(transactions_DB);
//}
//
//void listSavedTransactionsTest(void)
//{
//    listSavedTransactions();
//}
//
//void recieveTransactionDataTest(void)
//{
//    recieveTransactionData(transactions_DB);
//}
