#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
   int seed = 1000;
   int numPlayer = 2;
   //int i;
   int bonus = 0;
   int current_player;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G, copyG;

   //-----testing that the 

   //initialize the game
   initializeGame(numPlayer, k, seed, &G);
   
   //assign the current player
   current_player = whoseTurn(&G);

   //insert minion card into playe's hand
   gainCard(minion, &G, 2, current_player);

   //set coins amount to zero
   updateCoins(current_player, &G, 0);

   //store values for later testing
   int initial_coin_amt   = G.coins; //starting coin amount
   int initial_playedHand_amt = G.playedCardCount;

   //play the minion card
   //choice1 is 1 and choice2 is 0
   cardEffect(minion, 1, 0, 0, &G, 0, &bonus);

   //store the post coin amount
   int post_coin_amt = G.coins;
   int post_playedHand_amt = G.playedCardCount;

   if( (post_coin_amt == initial_coin_amt + 2) && (post_playedHand_amt == initial_playedHand_amt + 1)){
       printf("Bug 11 fail\n");
       printf("Two coins added.\n");
       printf("Card immediatley discarded.\n");
   }
   else{
       printf("Bug 11 pass\n");
       printf("Two coins added.\n");
       printf("Card not immediatley discarded.\n");
   }

   //----------testing the if-else if

   //initialize the game
   initializeGame(numPlayer, k, seed, &copyG);
   
   //assign the current player
   current_player = whoseTurn(&copyG);

   //insert minion card into playe's hand
   gainCard(minion, &copyG, 2, current_player);

   //set coins amount to zero
   updateCoins(current_player, &copyG, 0);

   //store values for later testing
   initial_coin_amt   = copyG.coins; //starting coin amount
   initial_playedHand_amt = copyG.playedCardCount;

   //play the minion card
   //choice1 is 1 and choice2 is 1
   cardEffect(minion, 0, 1, 0, &copyG, 0, &bonus);

   //store the post coin amount
   post_coin_amt = copyG.coins;
   post_playedHand_amt = copyG.playedCardCount;


   if((post_coin_amt == initial_coin_amt) && post_playedHand_amt > initial_playedHand_amt + 4)
   {
       printf("Bug 11 pass\n");
       printf("Starting coin amount: %d\n", initial_coin_amt);
       printf("Post coin amount: %d\n", post_coin_amt);
   }
   else
   {
       printf("Bug 11 fail the if-else");
   }
   

   return 0;
}