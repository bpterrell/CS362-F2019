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

   //insert an ambassador card into the player's hand
   gainCard(ambassador, &G, 2, current_player);

   //insert two identical cards into the player's hand
   gainCard(gardens, &G, 2, current_player);
   gainCard(gardens, &G, 2, current_player);

   //store values for later testing
   int pre_suppy_amt = G.supplyCount[gardens];

   //play the ambassador card
   cardEffect(ambassador, gardens, 2, 0, &G, 0, &bonus);

   //store the post supply amount
   int post_supply_amt = G.supplyCount[gardens];

   if(post_supply_amt == pre_suppy_amt + 2){
       printf("Bug 10 pass\n");
       printf("Pre supply amount: %d\n", pre_suppy_amt);
       printf("Post supply amount: %d\n", post_supply_amt);
   }
   else{
       printf("Bug 10 fail\n");
       printf("Pre supply amount: %d\n", pre_suppy_amt);
       printf("Post supply amount: %d\n", post_supply_amt);
   }




   return 0;
}