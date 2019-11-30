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
   int bonus = 0;
   int i;
   int k[10] = {adventurer, council_room, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game

   int currentPlayer = whoseTurn(&G);
   int nextPlayer = currentPlayer + 1;

   for (i = 0; i < 500; i++){
      G.deck[nextPlayer][i] = -1;
      
   }

   for (i = 0; i < 500; i++){
      G.hand[nextPlayer][i] = -1;
      
   }

   for (i = 0; i < 500; i++){
      G.discard[nextPlayer][i] = -1;
      
   }
   G.deckCount[nextPlayer] = 0;
   G.handCount[nextPlayer] = 0;
   G.discardCount[nextPlayer] = 0;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

   

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards needed to test the first state
   gainCard(silver, &G, 1, nextPlayer);    //Gain the cards needed to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0
   G.numActions = 0;

   int pre_numAct = G.numActions;
   int pre_coins = G.coins;
   int pre_handCount = G.handCount[currentPlayer];

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   int post_numAct = G.numActions;
   int post_coins = G.coins;
   int post_handCount = G.handCount[currentPlayer];

   if (pre_numAct != post_numAct){
      printf ("Bug 7 FAIL >> Tribute overran array and awarded extra actions.\n");
   }else printf ("Bug 7 PASS >> Tribute did not overrun array - no extra actions.\n");

   if (pre_coins + 4 != post_coins){
      printf ("Bug 7 FAIL >> Tribute overran array and awarded extra coins.\n");
   }else printf ("Bug 7 PASS >> Tribute did not overrun array - no extra coins.\n");

   if (pre_handCount != post_handCount){
      printf ("Bug 7 FAIL >> Tribute overran array and awarded extra draws.\n");
   }else printf ("Bug 7 PASS >> Tribute did not overrun array - no extra draws.\n");

  return 0;
}