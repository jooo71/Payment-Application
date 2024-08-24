/*
 * app.c
 *
 *  Created on: Aug 15, 2023
 *      Author: PC
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"
ST_transaction s5;
ST_transaction transactions_DB[255];

void appStart(void)
{
    uint8_t result = getCardHolderName(&(s5.cardHolderData));
    if (result == WRONG_NAME)
    {
        printf("wrong name\n");

    }
//    else
//    {
//        printf("card ok\n");
//    }
    uint8_t result2 = getCardExpiryDate(&(s5.cardHolderData));
    if (result2 == WRONG_EXP_DATE)
    {
        printf("wrong EXP_DATE\n");
    }
//    else
//    {
//        printf("EXP_DATE ok\n");
//    }
    uint8_t result3 = getCardPAN(&(s5.cardHolderData));
    if (result3 == WRONG_PAN)
    {
        printf("wrong CardPAN\n");
    }
//    else
//    {
//        printf("CardPAN ok\n");
//    }
    uint8_t result4 = getTransactionDate(&(s5.terminalData));
    if (result == WRONG_DATE)
    {
        printf("wrong transactionDate\n");
    }
//    else
//    {
//        printf("transactionDate ok\n");
//    }

    uint8_t result5= isCardExpired(&(s5.cardHolderData),&(s5.terminalData));
    if (result5 == EXPIRED_CARD)
    {
        
    }
    else
    {
        uint8_t result6 = getTransactionAmount(&(s5.terminalData));
        if (result6 == INVALID_AMOUNT)
        {
            printf("INVALID_AMOUNT\n");
        }
        else
        {
//            printf("TERMINAL_OK amount\n");
            uint8_t result = setMaxAmount(&(s5.terminalData),1000);
            if (result== INVALID_MAX_AMOUNT)
            {
                printf("INVALID_MAX_AMOUNT");
            }
            else
            {
//                printf("MAX_AMOUNT_OK");
                uint8_t result7= isBelowMaxAmount(&(s5.terminalData));
                if (result7==EXCEED_MAX_AMOUNT)
                {
                    printf("EXCEED_MAX_AMOUNT\n");
                }
                else{
//                    printf("TERMINAL_OK amount\n");
                    uint8_t result8= recieveTransactionData(transactions_DB);
//                    if (result8 == ACCOUNT_NOT_FOUND )
//                    {
//                        printf("FRAUD_CARD\n");
//                    }
//                    else if(result8 == LOW_BALANCE)
//                    {
//                        printf("DECLINED_INSUFFECIENT_FUND\n");
//                    }
//                    else if (result3==BLOCKED_ACCOUNT)
//                    {
//                        printf("DECLINED_STOLEN_CARD");
//                    }
//                    else
//                    {
//                        printf("APPROVD3");
//                    }
                    
                }
            }

        }
    }

    
}

int main(int argc, char const *argv[])
{
    appStart();
    return 0;
}
