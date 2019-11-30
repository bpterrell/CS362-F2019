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
   int k[10] = {adventurer, council_room, embargo, gardens, mine, tribute, minion, village, baron, great_hall};
   struct gameState G;
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game

   int currentPlayer = whoseTurn(&G);

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   

   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(baron, &G, 2, currentPlayer);    //Gain the cards neede to test the first state

   int pre_coins = G.coins;

   playCard(1, 1, 0, 0, &G);
  
   int post_coins = G.coins;
   
   printf( "%i %i\n", pre_coins, post_coins);
   
   if (pre_coins + 4 != post_coins){
      printf ("Bug 8 Baron FAIL >> Baron did not properly award coins.\n");
   }else printf ("Bug 8 Baron PASS >> Baron properly awarded coins.\n");




   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game

   currentPlayer = whoseTurn(&G);

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0   
   gainCard(minion, &G, 2, currentPlayer);    //Gain the cards neede to test the first state


   pre_coins = G.coins;

   playCard(0, 1, 0, 0, &G);
  
   post_coins = G.coins;
   
   printf( "%i %i\n", pre_coins, post_coins);
   
   if (pre_coins + 2 != post_coins){
      printf ("Bug 8 Minion FAIL >> Minion did not properly award coins.\n");
   }else printf ("Bug 8 Minion PASS >> Minion properly awarded coins.\n");



   
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game

   currentPlayer = whoseTurn(&G);
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

   pre_coins = G.coins;
   playCard(0, 0, 0, 0, &G);
   post_coins = G.coins;
   
   printf( "%i %i\n", pre_coins, post_coins);
   
   if (pre_coins + 4 != post_coins){
      printf ("Bug 8 FAIL >> Tribute overran array and awarded extra coins.\n");
   }else printf ("Bug 8 PASS >> Tribute did not overrun array - no extra coins.\n");


   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game

   currentPlayer = whoseTurn(&G);

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   

   gainCard(embargo, &G, 2, currentPlayer);    //Gain the cards neede to test the first state

   pre_coins = G.coins;

   playCard(0, gardens, 0, 0, &G);
  
   post_coins = G.coins;
   
   printf( "%i %i\n", pre_coins, post_coins);
   
   if (pre_coins + 2 != post_coins){
      printf ("Bug 8 Embargo FAIL >> Embargo did not properly award coins.\n");
   }else printf ("Bug 8 Embargo PASS >> Embargo properly awarded coins.\n");



  return 0;
}