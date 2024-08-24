/*
 * card.c
 *
 *  Created on: Aug 15, 2023
 *      Author: PC
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdint.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

    printf("enter your name\n");
    fflush(stdout);
    fgets(cardData->cardHolderName, 27, stdin); // size of :length of array
    uint8_t len = strlen(cardData->cardHolderName);
    uint8_t size = sizeof(cardData->cardHolderName);

    if (len == Null || (len - 1) < 20 || (len-1) >= size)
    {
//    	printf("wrong name"); // for test function
        return WRONG_NAME;
    }
//    printf("accept name\n"); // for test function
    return CARD_OK;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("enter your CardExpiryDate\n");
    fflush(stdout);
    fflush(stdin);
    fgets(cardData->cardExpirationDate, 8, stdin); // size of :length of array
    uint8_t len = strlen(cardData->cardExpirationDate);
    uint8_t size = sizeof(cardData->cardExpirationDate);

    if (len == Null || (len - 1) < 5 || len > size || cardData->cardExpirationDate[2]!='/')
    {
//    	printf("WRONG_EXP_DATE"); // for test function
        return WRONG_EXP_DATE;
    }
//    printf("accept EXP_DATE\n"); // fpr test function
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("enter your Primary Account Number\n");
    fflush(stdout);

    fgets(cardData->primaryAccountNumber, 22, stdin); // size of :length of array

    uint8_t len = strlen(cardData->primaryAccountNumber);
    uint8_t size = sizeof(cardData->primaryAccountNumber);
//    printf("%d\n", len);
//    printf("%d\n", size);

    if (len == Null || (len - 1) < 16 || len > size)
    {
//    	printf("WRONG_PAN"); // for test function
        return WRONG_PAN ;
    }
//    printf("accept pan"); // for test function
    return CARD_OK;
}
/*TESTS FUNCTIONS*/
//void getCardHolderNameTest(void)
//{
//    getCardHolderName(&(s5.cardHolderData));
//    //youseifessamyouseif -> worng due to 19 char
//    //youseifessamyouseiff -> accept
//    //youseifessamyouseifffffff -> wrong for 25 char
//}
//void getCardExpiryDateTest (void)
//{
//    getCardExpiryDate(&(s5.cardHolderData));
//    // 05/2 -<wrong
//    // 05/22 -<accept
//    // 05/222 -<wrong
//    //05222 -< wrong
//}
//
//void getCardPANTest (void)
//{
//    getCardPAN(&(s5.cardHolderData));
//    //8989374615436851 -< accept
//    //898937461543685 -< wrong due to 15 num
//    //89893746154368511111 -< wrong due to 20 num
//}
