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
* This first test is based on the player a copper to change for a silver 
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING mineEffect():\n");
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
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   
   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   int pre_handCountCP = G.handCount[currentPlayer];

   gainCard(mine, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   

#if (NOISY_TEST == 1)    
   printf ("Current player gains mine.\n");
   printf ("Current player gains one copper card.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 2)){
      printf("Hand count incremented correctly. PASSED\n");
   }else printf("Hand count incremented correctly. !!!FAILED!!!\n"); 
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   int pre_trashCount = G.playedCardCount;
   int pre_discardCountCP = G.discardCount[currentPlayer];
   pre_handCountCP = G.handCount[currentPlayer];
   int pre_silverSupply = supplyCount(silver, &G);
   int pre_silverCountCP = fullDeckCount(currentPlayer, silver, &G);
   int pre_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
   
   cardEffect(mine, 1, silver, 0, &G, 0, &bonus);
   
   int post_trashCount = G.playedCardCount;
   int post_discardCountCP = G.discardCount[currentPlayer];
   int post_handCountCP = G.handCount[currentPlayer];
   int post_silverSupply = supplyCount(silver, &G);
   int post_silverCountCP = fullDeckCount(currentPlayer, silver, &G);
   int post_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
;

#if (NOISY_TEST == 1)   
   printf ("P1 trashes an copper to gain silver.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one card. PASSED\n");
      }else printf("P1 hand count decreased by one card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(mine, currentPlayer, &G) == -1){
         printf("Mine Discarded. PASSED\n");
      }else printf("Mine Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_copperCountCP == pre_copperCountCP - 1 ){
         printf("P1 has one less copper card. PASSED\n");
      }else printf("P1 has one less copper card. !!!FAILED!!!\n");
#endif
#if (NOISY_TEST == 1)
      if (post_silverCountCP == pre_silverCountCP + 1 ){
         printf("P1 has one more silver card. PASSED\n");
      }else printf("P1 has one more silver card. !!!FAILED!!!\n");     
#endif      
#if (NOISY_TEST == 1)
   if (post_silverSupply == pre_silverSupply - 1){
      printf("Silver Supply lost one. PASSED\n");
   }else printf("Silver Supply lost one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount + 1 == post_trashCount){
      printf("ONE CARD TRASHED. PASSED \n");
   }else printf("ONE CARD TRASHED. !!!FAILED!!! %i   %i\n", pre_trashCount, post_trashCount);        
#endif   


/*
*
* This first test is based on the player a copper to change for a gold
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING mineEffect():\n");
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
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   
   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   pre_handCountCP = G.handCount[currentPlayer];

   gainCard(mine, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   

#if (NOISY_TEST == 1)    
   printf ("Current player gains mine.\n");
   printf ("Current player gains one copper card.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 2)){
      printf("Hand count incremented correctly. PASSED\n");
   }else printf("Hand count incremented correctly. !!!FAILED!!!\n"); 
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_handCountCP = G.handCount[currentPlayer];
   int pre_goldSupply = supplyCount(gold, &G);
   int pre_goldCountCP = fullDeckCount(currentPlayer, gold, &G);
   pre_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
   
   cardEffect(mine, 1, gold, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_handCountCP = G.handCount[currentPlayer];
   int post_goldSupply = supplyCount(gold, &G);
   int post_goldCountCP = fullDeckCount(currentPlayer, gold, &G);
   post_copperCountCP = fullDeckCount(currentPlayer, copper, &G);
;

#if (NOISY_TEST == 1)   
   printf ("P1 trashes an copper to gain gold.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP == post_handCountCP){
         printf("P1 hand count should stay the same. PASSED\n");
      }else printf("P1 hand count should stay the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP) == post_discardCountCP){
         printf("P1 discard count should stay the same. PASSED\n");
      }else printf("P1 discard count should stay the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(mine, currentPlayer, &G) > -1){
         printf("Mine Discarded. PASSED\n");
      }else printf("Mine Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_copperCountCP == pre_copperCountCP ){
         printf("P1 have same copper count. PASSED\n");
      }else printf("P1 have same copper count. !!!FAILED!!!\n");
#endif
#if (NOISY_TEST == 1)
      if (post_goldCountCP == pre_goldCountCP){
         printf("P1 gains zero golds. PASSED\n");
      }else printf("P1 gains zero golds. !!!FAILED!!!\n");     
#endif      
#if (NOISY_TEST == 1)
   if (post_goldSupply == pre_goldSupply){
      printf("Gold supply same. PASSED\n");
   }else printf("Gold supply same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount + 1 == post_trashCount){
      printf("ONE CARD TRASHED. PASSED \n");
   }else printf("ONE CARD TRASHED. !!!FAILED!!! %i   %i\n", pre_trashCount, post_trashCount);        
#endif   

  return 0;
}