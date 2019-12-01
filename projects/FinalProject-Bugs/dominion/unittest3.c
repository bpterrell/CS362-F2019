// CS 362 F19 400
// 11/07/19
// Final Project Part B - unittest3.c
// Unit test for remodel card
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
                if (discardIndex == 0) printf("\n\t\tDiscard card %-2d: %-13s\n", discardIndex, name);
                else printf("\t\tDiscard card %-2d: %-13s\n", discardIndex, name);
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
int checkDiscardCount(struct gameState *pre, int currentPlayer, int card, int choice1, int choice2)
{
    int check;
    int i;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    int c1 = pre->hand[currentPlayer][choice1];
    check = cardEffect(remodel, choice1, choice2, 0, &post, 0, 0);
//    assert(check==0);
    printf("\n\tDiscard content before: ");
    printCards(currentPlayer, pre, "discard");

    for (i = 0; i < pre->discardCount[currentPlayer]; i++)
    {
        if (post.discard[currentPlayer][i] == choice2) {
            countPre++;
        }
    }
    printf("\tDiscard content after: ");
    printCards(currentPlayer, &post, "discard");
    for (i = 0; i < post.discardCount[currentPlayer]; i++)
    {

        if (post.discard[currentPlayer][i] == choice2) {
            countPost++;
        }
    }
    if (countPre + 1 == countPost) {return 0;} else {return 1;}
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
    check = cardEffect(remodel, choice1, choice2, 0, &post, 0, 0);
    printf("\n\tHand content before: ");
    printCards(currentPlayer, pre, "hand");

    for (i = 0; i < pre->handCount[currentPlayer]; i++)
    {
        if (pre->hand[currentPlayer][i] == c1) {
            countPre++;
        }
    }
    printf("\tHand content after: ");
    printCards(currentPlayer, &post, "hand");
    for (i = 0; i < post.handCount[currentPlayer]; i++)
    {

        if (post.hand[currentPlayer][i] == c1) {
            countPost++;
        }

    }

    if (countPre - 1 != countPost) {return 1;}




}

int main(int argc, char** argv)
{
    struct gameState game1;



    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer = 0;
    int result;
    initializeGame(2, k, 1000, &game1);

    assert(getCost(baron) == 4);
    assert(getCost(mine) == 5);


    game1.handCount[0] = 2;
    game1.hand[0][0] = remodel;
    game1.hand[0][1] = baron;

    printf("Test remodel with exchanging baron for mine.\n");
    result = checkHandCount(&game1, currentPlayer, 0, 1, mine);
    if (result == 1)
    {
        printf("\n\tFAILURE: Baron card not trashed.\n");
    } else {
        printf("\n\tSUCCCESS: baron card successfully removed from hand.\n");
    }
    result = checkDiscardCount(&game1, currentPlayer, 0, 1, mine);
    if (result == 1)
    {
        printf("\n\tFAILURE: Mine card not added to discard.\n");
    } else {
        printf("\n\tSUCCCESS: mine card was successfully added to players discard.\n");
    }
    printf("---------------------------------------------------------\n\n");
    game1.handCount[0] = 2;
    game1.hand[0][0] = remodel;
    game1.hand[0][1] = embargo;

    printf("Test remodel with exchanging embargo for mine.\n");
    result = checkHandCount(&game1, currentPlayer, 0, 1, mine);
    if (result != 1)
    {
        printf("\n\tFAILURE: Exchange is invalid, but the embargo card was still removed from hand .\n");
    } else {
        printf("\n\tSUCCCESS: Exchange seen as invalid and embargo card remains in players hand.\n");
    }
    result = checkDiscardCount(&game1, currentPlayer, 0, 1, mine);
    if (result != 1)
    {
        printf("\n\tFAILURE: Exchange is invalid, but mine card was still added to discard.\n");
    } else {
        printf("\n\tSUCCCESS: Exchange seen as invalid and mine card was not added to discard pile.\n");
    }
    printf("---------------------------------------------------------\n\n");
    game1.handCount[0] = 2;
    game1.hand[0][0] = remodel;
    game1.hand[0][1] = baron;

    printf("Test remodel with exchanging baron for adventurer.\n");
    result = checkHandCount(&game1, currentPlayer, 0, 1, adventurer);
    if (result == 1)
    {
        printf("\n\tFAILURE: Baron card not trashed.\n");
    } else {
        printf("\n\tSUCCCESS: Baron card successfully removed from hand.\n");
    }
    result = checkDiscardCount(&game1, currentPlayer, 0, 1, adventurer);
    if (result == 1)
    {
        printf("\n\tFAILURE: Adventurer card not added to discard pile.\n");
    } else {
        printf("\n\tSUCCCESS: Adventurer card was successfully added to players discard.\n");
    }
    printf("---------------------------------------------------------\n\n");
}