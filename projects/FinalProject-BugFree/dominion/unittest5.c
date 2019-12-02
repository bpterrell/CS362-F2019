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
   //int bonus = 0;
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

   gainCard(estate, &G, 0, currentPlayer);    //Gain the card to discard
   gainCard(estate, &G, 1, currentPlayer);    //Gain the card to deck
   gainCard(estate, &G, 1, currentPlayer);    //Gain the card to deck
   gainCard(estate, &G, 1, currentPlayer);    //Gain the card to deck
   gainCard(estate, &G, 2, currentPlayer);    //Gain the card to hand
   gainCard(estate, &G, 2, currentPlayer);    //Gain the card to hand
   
   int score = scoreFor (currentPlayer, &G);

if (score != 6){
   printf (" Bug 5 FAIL >> score is incorrect.\n");
}else printf ("Bug 5 PASS >> Score is correct.\n");
   
  return 0;
}