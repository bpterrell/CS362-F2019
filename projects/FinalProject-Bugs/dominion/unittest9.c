// CS 362 F19 400
// 12/01/19
// Final Project Part B - unittest9.c
// Unit test for tribute card
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
int getHandCount(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = cardEffect(tribute, 0, 0, 0, &post, 0, 0);
    assert(check==0);
    printf("\n\tNumber of cards in hand before: %d", pre->numActions);
    printf("\n\tNumber of cards in hand after:  %d\n", post.numActions);
    if (pre->handCount[currentPlayer]+2 == post.handCount[currentPlayer]) {
        printf("\n\tNumber of player actions before: %d", pre->numActions);
        printf("\n\tNumber of player actions after:  %d\n", post.numActions);
        if (pre->numActions == post.numActions) {
            return 0;}
        else {return 1;}
    } else {
        return 1;
    }
}

int actionCount(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = cardEffect(tribute, 0, 0, 0, &post, 0, 0);
    assert(check==0);
    printf("\n\tNumber of player actions before: %d", pre->numActions);
    printf("\n\tNumber of player actions after:  %d\n", post.numActions);
    if (pre->numActions+2 == post.numActions) {
        return 0;
    } else {
        return 1;
    }
}


int main(int argc, char** argv) {
    struct gameState game1;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer = 0;
    initializeGame(2, k, 1000, &game1);

    game1.hand[currentPlayer][0] = tribute;
    game1.deckCount[1] = 2;
    game1.deck[1][0] = baron;
    game1.deck[1][1] = baron;
    printf("Testing two duplicate action cards\n");
    if (actionCount(&game1, currentPlayer)==0) {
        printf("\nSUCCESS: duplicate card ignored and bonus actions added only once.\n");
    } else {
        printf("\nFAILURE: duplicate card not ignored and bonus actions added twice.\n");
    }
    printf("-----------------------------------------------------------\n");

    game1.deckCount[1] = 2;
    game1.deck[1][0] = baron;
    game1.deck[1][1] = estate;
    printf("Testing one action card and one tribute card\n");
    if (actionCount(&game1, currentPlayer)==0) {
        printf("\nSUCCESS: bonus actions added only once.\n");
    } else {
        printf("\nFAILURE: bonus actions added twice.\n");
    }
    printf("-----------------------------------------------------------\n");

    game1.deckCount[1] = 2;
    game1.deck[1][0] = baron;
    game1.deck[1][1] = mine;
    printf("Testing two distinct action cards\n");
    if (actionCount(&game1, currentPlayer)==1) {
        printf("\nSUCCESS: bonus actions added twice because action cards are distinct.\n");
    } else {
        printf("\nFAILURE: action cards seen as duplicates and added only once.\n");
    }
    printf("-----------------------------------------------------------\n");

    game1.deckCount[1] = 2;
    game1.deck[1][0] = estate;
    game1.deck[1][1] = estate;
    printf("Testing two duplicate victory cards\n");
    if (getHandCount(&game1, currentPlayer)==0) {
        printf("\nSUCCESS: duplicate card ignored and bonus actions added only once.\n");
    } else {
        printf("\nFAILURE: duplicate card not ignored and bonus actions added for non action card.\n");
    }
}