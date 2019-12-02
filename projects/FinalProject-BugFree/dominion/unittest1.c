#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

int main (int argc, char** argv) {
   int seed = 1000;
   int numPlayer = 3;
   int i;
   int bonus = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;

  
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game   
   int currentPlayer = whoseTurn(&G);

   //Clear all cards
   for (i = 0; i < 500; i++){
      G.deck[currentPlayer][i] = -1;
      
   }

   for (i = 0; i < 500; i++){
      G.hand[currentPlayer][i] = -1;
      
   }

   for (i = 0; i < 500; i++){
      G.discard[currentPlayer][i] = -1;
      
   }
   G.deckCount[currentPlayer] = 0;
   G.handCount[currentPlayer] = 0;
   G.discardCount[currentPlayer] = 0;

   gainCard(mine, &G, 2, currentPlayer);    //Gain the cards need to test
   gainCard(copper, &G, 2, currentPlayer);    //Gain the cards need to test
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0


   int pre_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
   
   cardEffect(mine, 1, silver, 0, &G, 0, &bonus);
   
   int post_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
   int post_silverCountCP = fullDeckCount(currentPlayer, silver, &G);
;

if (pre_copperCountCP == post_copperCountCP){
   printf ("Bug 1 FAIL >> Copper was not trashed. %i %i %i\n", pre_copperCountCP, post_copperCountCP,  post_silverCountCP );
}else printf ("Bug 1 PASS >> Copper was trashed. %i %i %i\n", pre_copperCountCP, post_copperCountCP,  post_silverCountCP );
   
  return 0;
}