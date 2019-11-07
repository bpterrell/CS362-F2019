#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main (int argc, char** argv) {
   int seed = 1000;
   int numPlayer = 3;
   //int maxBonus = 10;
   //int p, r, handCount;
   int bonus = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   //int maxHandCount = 5;
   //*bonus = 0;

/*
*
* This first test is based on the player having a Minion card and chooses the action of gaining two coins.  
*
*/

#if (NOISY_TEST == 1)
      printf ("\nTESTING minionEffect():\n");
      printf ("Starting game for test 1.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   int r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   int currentPlayer = whoseTurn(&G);

#if (NOISY_TEST == 1)
   printf ("Current player's is #%i and their hand count equals: %i\n", currentPlayer, G.handCount[currentPlayer]);
#endif
  
   int pre_handCountCP = G.handCount[currentPlayer];

   gainCard(minion, &G, 2, currentPlayer);    //Gain the cards neede to test the first state

   discardCard(0, 1, &G, 0);        //discard two cards from P3
   discardCard(0, 1, &G, 0);

#if (NOISY_TEST == 1)   
   printf ("Current player gains Minion.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 1)){
      printf("Hand count incremented correctly. PASSED\n");
   }else printf("Hand count incremented correctly. !!!FAILED!!!\n"); 
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   int pre_trashCount = G.playedCardCount;
   int pre_discardCountCP = G.discardCount[currentPlayer];
   int pre_discardCountP2 = G.discardCount[1];
   int pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   int pre_handCountP2 = G.handCount[1];
   int pre_handCountP3 = G.handCount[2];
   updateCoins(currentPlayer, &G, 1);        //Update coins to 1
   
   cardEffect(minion, 1, 0, 0, &G, 0, &bonus);


   int post_discardCountCP = G.discardCount[currentPlayer];
   int post_discardCountP2 = G.discardCount[1];
   int post_discardCountP3 = G.discardCount[2];
   int post_handCountCP = G.handCount[currentPlayer];
   int post_handCountP2 = G.handCount[1];
   int post_handCountP3 = G.handCount[2];
   int post_trashCount = G.playedCardCount;

#if (NOISY_TEST == 1)   
   printf ("Current player chooses action to gain 2 coins.\n");
   printf ("Current player's hand count equals: %i\n", G.discardCount[currentPlayer]);
#endif
#if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] == (pre_handCountCP - 1)){
         printf("Hand count decremented by one minion. PASSED\n");
      }else printf("Hand count decremented by one minion. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == G.discardCount[currentPlayer]){
         printf("Discard count increased by one minion. PASSED\n");
      }else printf("Discard count increased by one minion. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(minion, currentPlayer, &G) == -1){
         printf("Minion Discarded from hand. PASSED\n");
      }else printf("Minion Discarded from hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 3){
      printf("Two coins added. PASSED %i\n", G.coins);
   }else printf("Two coins added. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2 && pre_discardCountP2 == post_discardCountP2){
      printf("Player two's hand count and discard count remain the same. PASSED\n");
   }else printf("Player two's hand count and discard count remain the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3 && pre_discardCountP3 == post_discardCountP3){
      printf("Player three's hand count and discard count remain the same. PASSED \n");
   }else printf("Player three's hand count and discard count remain the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif


/*
*
* This second test is based on the player having a Minion card and chooses the attack of making everyone redraw.  
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING minionEffect():\n");
      printf ("Starting game for test 2.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);

#if (NOISY_TEST == 1)
   printf ("Current player's is #%i and their hand count equals: %i\n", currentPlayer, G.handCount[currentPlayer]);
#endif
   
   pre_handCountCP = G.handCount[currentPlayer];

   gainCard(minion, &G, 2, currentPlayer);    //Gain the cards needed to test the first state
   //gainCard(silver, &G, 2, currentPlayer);    //Gain the cards needed to test the first state
   
   discardCard(0, 1, &G, 0); //discard two cards from P3
   discardCard(0, 1, &G, 0);

#if (NOISY_TEST == 1)   
   printf ("Current player gains Minion.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 2)){
      printf("Hand count incremented correctly. PASSED\n");
   }else printf("Hand count incremented correctly. !!!FAILED!!!\n"); 
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   updateCoins(currentPlayer, &G, 1);        //Update coins to 1

   
   cardEffect(minion, 0, 1, 0, &G, 0, &bonus);


   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];

#if (NOISY_TEST == 1)   
   printf ("Current player chooses attack, force the redraw of all player's hands >= 4 cards.\n");
   printf ("Current player's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (post_handCountCP == 4){
         printf("Current player's hand count equals 4. PASSED\n");
      }else printf("Current player's hand count equals 4. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + pre_handCountCP) == post_discardCountCP){
         printf("Current player's discard count increased all cards in hand. PASSED\n");
      }else printf("Current player's discard count increased all cards in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(minion, currentPlayer, &G) == -1){
         printf("Minion Discarded from hand. PASSED\n");
      }else printf("Minion Discarded from hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 1){
      printf("Zero coins added. PASSED %i\n", G.coins);
   }else printf("Zero coins added. !!!FAILED!!! %i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
   if (post_handCountP2 == 4){
      printf("Player two's hand count is now 4. PASSED \n");
   }else printf("Player two's hand count is now 4. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if ((pre_discardCountP2 + pre_handCountP2) == post_discardCountP2){
      printf("Player two's discard count increased by number of cards in previous hand. PASSED \n");
   }else printf("Player two's discard count increased by number of cards in previous hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3 && (pre_discardCountP3 == post_discardCountP3)){
      printf("Player three's hand count and discard count remain the same. PASSED \n");
   }else printf("Player three's hand count and discard count remain the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif


/*
*
* This third test is based on the player having a Minion card and chooses the attack of making evryone redraw,
* But no decks qualify for redraw.  
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING minionEffect():\n");
      printf ("Starting game for test 3.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);

#if (NOISY_TEST == 1)
   printf ("Current player's is #%i and their hand count equals: %i\n", currentPlayer, G.handCount[currentPlayer]);
#endif
   
   pre_handCountCP = G.handCount[currentPlayer];

   gainCard(minion, &G, 2, currentPlayer);    //Gain the cards needed to test the first state
   //gainCard(silver, &G, 2, currentPlayer);    //Gain the cards needed to test the first state
   

#if (NOISY_TEST == 1)   
   printf ("Current player gains Minion.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 2)){
      printf("Hand count incremented correctly. PASSED\n");
   }else printf("Hand count incremented correctly. !!!FAILED!!!\n"); 
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   updateCoins(currentPlayer, &G, 1);        //Update coins to 1

   
   cardEffect(minion, 0, 1, 0, &G, 0, &bonus);


   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];

#if (NOISY_TEST == 1)   
   printf ("Current player chooses attack, force the redraw of all player's hands >= 4 cards.\n");
   printf ("Current player's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (post_handCountCP == 4){
         printf("Current player's hand count equals 4. PASSED\n");
      }else printf("Current player's hand count equals 4. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + pre_handCountCP) == post_discardCountCP){
         printf("Current player's discard count increased all cards in hand. PASSED\n");
      }else printf("Current player's discard count increased all cards in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(minion, currentPlayer, &G) == -1){
         printf("Minion Discarded from hand. PASSED\n");
      }else printf("Minion Discarded from hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 1){
      printf("Zero coins added. PASSED %i\n", G.coins);
   }else printf("Zero coins added. !!!FAILED!!! %i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2 && (pre_discardCountP2 == post_discardCountP2)){
      printf("Player two's hand count and discard count remain the same. PASSED \n");
   }else printf("Player two's hand count and discard count remain the same. !!!FAILED!!!\n");
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3 && (pre_discardCountP3 == post_discardCountP3)){
      printf("Player three's hand count and discard count remain the same. PASSED \n");
   }else printf("Player three's hand count and discard count remain the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif

  return 0;
}