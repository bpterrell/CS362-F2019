// CS 362 F19 400
// 12/01/19
// Final Project Part B - unittest4.c
// Unit test for isGameOver function
// Created by: Kara Manseau

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    struct gameState game1;
    int i;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer = 0;
    int result;
    initializeGame(2, k, 1000, &game1);

    int pileCount = sizeof(game1.supplyCount)/ sizeof(game1.supplyCount[0]);

    for (i = 0; i < pileCount; i++)
    {
        game1.supplyCount[i]=5;
    }

    printf("Testing isGameOver when all supply piles are full.\n");
    if (isGameOver(&game1)==0) {
        printf("SUCCESS: successfully determined game is still in play.\n");
    } else {
        printf("FAILURE: game should be over.\n");
    }

    printf("-----------------------------------------------------------\n");
    for (i = 0; i < pileCount; i++) {
        if (i < 24) {

            game1.supplyCount[i] = 5;
        } else {
            game1.supplyCount[i] = 0;
        }
    }
    printf("\nTesting isGameOver when last 3 supply piles are empty.\n");
    if (isGameOver(&game1)==1) {
        printf("SUCCESS: successfully determined game is not still in play.\n");
    } else {
        printf("FAILURE: game should be over.\n");
    }
    printf("-----------------------------------------------------------\n");
}


