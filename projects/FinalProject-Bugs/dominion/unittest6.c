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
   struct gameState G;

   //initialize the game
   initializeGame(numPlayer, k, seed, &G);
   //assign the current player
   current_player = whoseTurn(&G);  

   //insert a feast card into the players hand
   gainCard(feast, &G, 2, current_player);

   //insert card to gain (village) into the players hand
   gainCard(village, &G, 2, current_player);

   //set coins amount to zero
   updateCoins(current_player, &G, 0);
   
   //store values for later testing
   int initial_coin_amt   = G.coins; //starting coin amount
   //int gaining_card_cost  = getCost(village); 
   //int initial_hand_count = G.handCount[current_player];
   //int initial_discard_amt = G.discardCount

   //play the feast card
   cardEffect(feast, village, 0, 0, &G, 0, &bonus);

   int post_coin_amt   = G.coins;
   //int post_hand_count = G.handCount[current_player];

   if(post_coin_amt == initial_coin_amt + 5){
       printf("Bug 6 fail\n");
       printf("Starting coin amount: %d\n", initial_coin_amt);
       printf("Post coin amount: %d\n", post_coin_amt);
   }
   else{
       printf("Bug 6 pass\n");
       printf("Starting coin amount: %d\n", initial_coin_amt);
       printf("Post coin amount: %d\n", post_coin_amt);
   } 




   return 0;
}