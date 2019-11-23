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
   int numPlayer = 2;
   //int maxBonus = 10;
   //int p, r, handCount;
   int bonus = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   //int maxHandCount = 5;
   //*bonus = 0;

/*
*
* This first test is based on the player having an Estate card and a Baron. Player trades Estate for +4 coins. 
*
*/

#if (NOISY_TEST == 1)
      printf ("\nTESTING baronEffect():\n");
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

   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(baron, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);

#if (NOISY_TEST == 1)   
   printf ("Current player gains Baron.\n");
   printf ("Current player gains Estate.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   int pre_discardCount = G.discardCount[currentPlayer];
   int pre_estateSupply = supplyCount(estate, &G);
   int pre_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   int pre_EstateCount = fullDeckCount(currentPlayer, estate, &G);
   
   cardEffect(baron, 1, 0, 0, &G, 0, &bonus);

   int post_estateSupply = supplyCount(estate, &G);
   int post_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   int post_EstateCount = fullDeckCount(currentPlayer, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("Current player discards Estate to gain 4 coin.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
#if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] == 0){
         printf("Hand count equals zero. PASSED\n");
      }else printf("Hand count equals zero. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCount + 2) == G.discardCount[currentPlayer]){
         printf("Discard count increased by two. PASSED\n");
      }else printf("Discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(baron, currentPlayer, &G) == -1){
         printf("Baron Discarded. PASSED\n");
      }else printf("Baron Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(estate, currentPlayer, &G) == -1 ){
         printf("Estate Discarded. PASSED\n");
      }else printf("Estate Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == pre_estateSupply){
      printf("Estate Supply correct. PASSED\n");
   }else printf("Estate Supply correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 4){
      printf("Four coins added. PASSED %i\n", G.coins);
   }else printf("Four coins added. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_BaronCount == post_BaronCount){
      printf("Program conserved Baron cards. PASSED %i\n", G.coins);
   }else printf("Program conserved Baron cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_EstateCount == post_EstateCount){
      printf("Program conserved Estate cards. PASSED %i\n", G.coins);
   }else printf("Program conserved Estate cards. !!!FAILED!!!\n");        
#endif


/*
* This test is based on the player having an Estate card and a Baron. 
* Player chooses not to trade Estate for +4 coins. 
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING baronEffect():\n");
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

   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(baron, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);

#if (NOISY_TEST == 1)   
   printf ("Current player gains Baron.\n");
   printf ("Current player gains Estate.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   pre_discardCount = G.discardCount[currentPlayer];
   pre_estateSupply = supplyCount(estate, &G);
   pre_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   pre_EstateCount = fullDeckCount(currentPlayer, estate, &G);
   
   cardEffect(baron, 0, 0, 0, &G, 0, &bonus);

   post_estateSupply = supplyCount(estate, &G);
   post_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   post_EstateCount = fullDeckCount(currentPlayer, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("Current player DOES NOT discard Estate and gains an Estate card.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
#if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] == 1){
         printf("Hand count equals one. PASSED\n");
      }else printf("Hand count equals one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCount + 2) == G.discardCount[currentPlayer]){
         printf("Discard count increased by two. PASSED\n");
      }else printf("Discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(baron, currentPlayer, &G) == -1){
         printf("Baron Discarded. PASSED\n");
      }else printf("Baron Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(estate, currentPlayer, &G) > -1 ){
         printf("Estate still in hand. PASSED\n");
      }else printf("Estate still in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == (pre_estateSupply -1)){
      printf("Estate Supply correct. PASSED\n");
   }else printf("Estate Supply correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("No coins added. PASSED %i\n", G.coins);
   }else printf("No coins added. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_BaronCount == post_BaronCount){
      printf("Program conserved Baron cards. PASSED %i\n", G.coins);
   }else printf("Program conserved Baron cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if ((pre_EstateCount + 1) == post_EstateCount){
      printf("Program conserved Estate cards. PASSED %i\n", G.coins);
   }else printf("Program conserved Estate cards. !!!FAILED!!!\n");        
#endif


/*
* This test is based on the player having an zero Estate cards and a Baron. 
* Player chooses not to trade Estate for +4 coins. 
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING baronEffect():\n");
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
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
   
   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(baron, &G, 2, currentPlayer);    //Gain the cards neede to test the first stat

#if (NOISY_TEST == 1)   
   printf ("Current player gains Baron.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   pre_discardCount = G.discardCount[currentPlayer];
   pre_estateSupply = supplyCount(estate, &G);
   pre_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   pre_EstateCount = fullDeckCount(currentPlayer, estate, &G);
   
   cardEffect(baron, 0, 0, 0, &G, 0, &bonus);

   post_estateSupply = supplyCount(estate, &G);
   post_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   post_EstateCount = fullDeckCount(currentPlayer, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("Current player DOES NOT have an Estate to discard and gains an Estate card.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
#if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] == 0){
         printf("Hand count equals zero. PASSED\n");
      }else printf("Hand count equals zero. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCount + 2) == G.discardCount[currentPlayer]){
         printf("Discard count increased by two. PASSED\n");
      }else printf("Discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(baron, currentPlayer, &G) == -1){
         printf("Baron Discarded. PASSED\n");
      }else printf("Baron Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(estate, currentPlayer, &G) == -1 ){
         printf("No Estate in hand. PASSED\n");
      }else printf("No Estate in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == (pre_estateSupply -1)){
      printf("Estate Supply correct. PASSED\n");
   }else printf("Estate Supply correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("No coins added. PASSED %i\n", G.coins);
   }else printf("No coins added. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_BaronCount == post_BaronCount){
      printf("Current player conserved Baron cards. PASSED\n");
   }else printf("Current player conserved Baron cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if ((pre_EstateCount + 1) == post_EstateCount){
      printf("Current player conserved Estate cards. PASSED %i\n", post_EstateCount);
   }else printf("Current player conserved Estate cards. !!!FAILED!!!%i\n", post_EstateCount);        
#endif


/*
* This  test is based on the player having an zero Estate cards and a Baron. 
* Player chooses to trade an Estate they do not have for +4 coins. 
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING baronEffect():\n");
      printf ("Starting game for test 4.\n");        
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

   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(baron, &G, 2, currentPlayer);    //Gain the cards neede to test the first stat

#if (NOISY_TEST == 1)   
   printf ("Current player gains Baron.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif

   pre_discardCount = G.discardCount[currentPlayer];
   pre_estateSupply = supplyCount(estate, &G);
   pre_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   pre_EstateCount = fullDeckCount(currentPlayer, estate, &G);
   
   cardEffect(baron, 1, 0, 0, &G, 0, &bonus);

   post_estateSupply = supplyCount(estate, &G);
   post_BaronCount = fullDeckCount(currentPlayer, baron, &G);
   post_EstateCount = fullDeckCount(currentPlayer, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("Current player DOES NOT have an Estate to discard but trys to gain +4 coins.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);
#endif
#if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] == 0){
         printf("Hand count equals zero. PASSED\n");
      }else printf("Hand count equals zero. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCount + 2) == G.discardCount[currentPlayer]){
         printf("Discard count increased by one. PASSED\n");
      }else printf("Discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(baron, currentPlayer, &G) == -1){
         printf("Baron Discarded. PASSED\n");
      }else printf("Baron Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(estate, currentPlayer, &G) == -1 ){
         printf("No Estate in hand. PASSED\n");
      }else printf("No Estate in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == (pre_estateSupply -1)){
      printf("Estate Supply correct. PASSED\n");
   }else printf("Estate Supply correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("No coins added. PASSED %i\n", G.coins);
   }else printf("No coins added. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_BaronCount == post_BaronCount){
      printf("Current player conserved Baron cards. PASSED\n");
   }else printf("Current player conserved Baron cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if ((pre_EstateCount + 1) == post_EstateCount){
      printf("Current player conserved Estate cards. PASSED %i\n", post_EstateCount);
   }else printf("Current player conserved Estate cards. !!!FAILED!!!%i\n", post_EstateCount);        
#endif

  return 0;
}