// CS 362 F19 400
// 11/07/19
// Final Project Part B - unittest2.c
// Unit test for mine card
// Created by: Kara Manseau

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include <stdbool.h>
void printCards(int player, struct gameState *game, char pileType[]) {

    if (strcmp(pileType, "discard")==0) {
        int discardCount = game->discardCount[player];
        int discardIndex;
        if (discardCount == 0) {
            printf("The discard pile is currently empty.\n");
        } else {
            for (discardIndex = 0; discardIndex < discardCount; discardIndex++) {
                int card = game->discard[player][discardIndex];
                char name[MAX_STRING_LENGTH];
                cardNumToName(card, name);
                if (discardIndex == 0) printf("\tDiscard card %-2d: %-13s\n", discardIndex, name);
                else printf("\t\t\t\tDiscard card %-2d: %-13s\n", discardIndex, name);
            }
        }
    } else if (strcmp(pileType, "hand")==0) {
        int handCount = game->handCount[player];
        int handIndex;
        if (handCount == 0) {
            printf("The players hand is currently empty.\n");
        } else {
            for (handIndex = 0; handIndex < handCount; handIndex++) {
                int card = game->hand[player][handIndex];
                char name[MAX_STRING_LENGTH];
                cardNumToName(card, name);
                if (handIndex == 0) printf("\n\t\tHand card %-2d: %-13s\n", handIndex, name);
                else printf("\t\tHand card %-2d: %-13s \n", handIndex, name);
            }
        }

    }

}

int checkHandCount(struct gameState *pre, int currentPlayer, int card, int choice1, int choice2)
{
    int i;
    int check;
    int countPre=0;
    int countPost=0;
    int newCountPre=0;
    int newCountPost=0;
    struct gameState post;
    int c1 = pre->hand[currentPlayer][choice1];
    memcpy (&post, pre, sizeof(struct gameState));


//    (int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    check = cardEffect(mine, choice1, choice2, 0, &post, 0, 0);
    printf("\n\tHand content before: ");
    printCards(currentPlayer, pre, "hand");

    for (i = 0; i < pre->handCount[currentPlayer]; i++)
    {
        if (pre->hand[currentPlayer][i] == c1) {
            countPre++;
        }
        if (pre->hand[currentPlayer][i] == choice2) {
            newCountPre++;
        }
    }
    printf("\tHand content after: ");
    printCards(currentPlayer, &post, "hand");
    for (i = 0; i < post.handCount[currentPlayer]; i++)
    {

        if (post.hand[currentPlayer][i] == c1) {
            countPost++;
        }
        if (post.hand[currentPlayer][i] == choice2) {
            newCountPost++;
        }
    }

    if (countPre - 1 != countPost) {check=1;}
    if (newCountPre + 1 != newCountPost) {check+=2;}
    return check;


}

int main(int argc, char** argv)
{
    struct gameState game1;



    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer = 0;
    int result;
    initializeGame(2, k, 1000, &game1);

    assert(getCost(copper) == 0);
    assert(getCost(silver) == 3);
    assert(getCost(gold) == 6);

    game1.handCount[0] = 2;
    game1.hand[0][0] = mine;
    game1.hand[0][1] = copper;

    printf("Test mine with exchanging copper for silver.\n");
    result = checkHandCount(&game1, currentPlayer, 0, 1, silver);
    if (result == 1)
    {
        printf("\n\tFAILURE: Test failed - copper card not removed, but silver was added to hand.\n");
    } else if (result == 2) {
        printf("\n\tFAILURE: Test failed - copper card removed, but silver card not added to hand.\n");
    } else if (result == 3) {
        printf("\n\tFAILURE: Test failed - copper card not removed and silver card not added to hand.\n");
    } else {
        printf("\n\tSUCCCESS: Copper card removed from hand and silver card added without issue.\n");
    }

    game1.handCount[0] = 2;
    game1.hand[0][0] = mine;
    game1.hand[0][1] = silver;
    printf("\n-----------------------------------------------------------\n");
    printf("Test mine with exchanging silver for gold.");
    result = checkHandCount(&game1, currentPlayer, 0, 1, gold);
    if (result == 1)
    {
        printf("\n\tFAILURE: Test failed - silver card not removed, but gold was added to hand.\n");
    } else if (result == 2) {
        printf("\n\tFAILURE: Test failed - silver card removed, but gold card not added to hand.\n");
    } else if (result == 3) {
        printf("\n\tFAILURE: Test failed - silver card not removed and gold card not added to hand.\n");
    } else {
        printf("\n\tSUCCCESS: Silver card removed from hand and gold card added without issue.\n");
    }

    game1.handCount[0] = 2;
    game1.hand[0][0] = mine;
    game1.hand[0][1] = copper;
    printf("\n-----------------------------------------------------------\n");
    printf("Test mine with exchanging copper for gold.\n");
    result = checkHandCount(&game1, currentPlayer, 0, 1, gold);
    if (result < 1)
    {
        printf("\n\tFAILURE: Test failed - copper can not be exchanged for gold.\n");
    } else {
        printf("\n\tSUCCCESS: Invalid exchange identified and exchange did not occur.\n");
    }
    printf("\n");
}