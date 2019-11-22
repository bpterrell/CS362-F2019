#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include<time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main (int argc, char** argv) {
   srand(time(NULL));

   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;  
   int testCycles = 1000;

   for (int i = 1; i <= testCycles; ++i){
   #if (NOISY_TEST == 1)
      printf("Baron card test %i/1000.\n", i);  
   #endif
      int bonus = 0;      
      int seed = (rand() % 1000) + 1;
      int startingCoins = (rand() % 50);
      int handSize = (rand() % MAX_HAND);
      int numPlayer = (rand() % (MAX_PLAYERS - 2)) + 2;    
      int choice1 = (rand() % 2);
      int choice2 = (rand() % 2);
      int choice3 = (rand() % 2);
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      int r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
      int cardToBePlayedInHand = 0;
 
   #if (NOISY_TEST == 1)
      if (r != 0){
         printf("Game initialization. !!!FAILED!!!\n");  
         return 0;
      } 
   #endif  

      int currentPlayer = whoseTurn(&G);
   
      while(numHandCards(&G) > 0){              //Clear entire hand
         discardCard(0, currentPlayer, &G, 0);
      }
      updateCoins(currentPlayer, &G, startingCoins);        //Update coins

      for (int k = 0; k < (rand() % 100); ++k){
         if (!(rand() % 1000)){
            gainCard(estate, &G, 2, currentPlayer);
         }
      }

      for (int j = 0; j < handSize ; ++j){
         gainCard(k[(rand() % 10)], &G, 2, currentPlayer);

      }
   #if (NOISY_TEST == 1)
      if (G.handCount[currentPlayer] != handSize){
         printf("G.handCount[currentPlayer] != handSize !!!FAILED!!!\n");  
      } 
   #endif    
   #if (NOISY_TEST == 1)
         printf("Baron found in deck?   ");
         if (findCardInHand(baron, currentPlayer, &G)){
            cardToBePlayedInHand = 1;
            printf(">YES<\n");
         }else printf(">NO<\n");        
   #endif
   #if (NOISY_TEST == 1)
         printf("Estate found in deck?   ");
         if (findCardInHand(estate, currentPlayer, &G)){
            printf(">YES<\n");
         }else printf(">NO<\n");        
   #endif
   #if (NOISY_TEST == 1)
         printf("Choice conditions: choice1: %i, choice2: %i, choice3: %i\n", choice1, choice2, choice3);       
   #endif

      int pre_discardCount = G.discardCount[currentPlayer];
      int pre_estateSupply = supplyCount(estate, &G);
      int pre_BaronCount = fullDeckCount(currentPlayer, baron, &G);
      int pre_EstateCount = fullDeckCount(currentPlayer, estate, &G);
      int pre_handCount = G.handCount[currentPlayer];

      cardEffect(baron, choice1, choice2, choice3, &G, 0, &bonus);

      int post_discardCount = G.discardCount[currentPlayer];
      int post_estateSupply = supplyCount(estate, &G);
      int post_BaronCount = fullDeckCount(currentPlayer, baron, &G);
      int post_EstateCount = fullDeckCount(currentPlayer, estate, &G);
      int post_handCount = G.handCount[currentPlayer];

   #if (NOISY_TEST == 1)
      if (!(cardToBePlayedInHand)){
         if (G.coins != startingCoins){
            printf("FAIL: Coin count incorrect.\n");
         }
         if (pre_handCount != post_handCount){
            printf("FAIL: Hand count incorrect.\n");
         }
         if (pre_discardCount != post_discardCount){
            printf("FAIL: Discard count incorrect.\n");
         }
         if (post_estateSupply != pre_estateSupply){
            printf("FAIL: Estate supply incorrect.\n");
         }
         if (pre_BaronCount != post_BaronCount){
            printf("FAIL: Baron cards not conserved.\n");
         }
         if (pre_EstateCount == post_EstateCount){
            printf("FAIL: Estate cards not conserved.\n");
         }
      }       
   #endif

   #if (NOISY_TEST == 1)
      if (choice1 == 1 && cardToBePlayedInHand && findCardInHand(estate, currentPlayer, &G)){
         if (G.coins != startingCoins + 4){
            printf("FAIL: Coin count incorrect.\n");
         }
         if (pre_discardCount + 2 != post_discardCount){
            printf("FAIL: Discard count incorrect.\n");
         }
         if (pre_handCount - 2 != post_handCount){
            printf("FAIL: Hand count incorrect.\n");
         }
         if (post_estateSupply != pre_estateSupply){
            printf("FAIL: Estate supply incorrect.\n");
         }
         if (pre_BaronCount != post_BaronCount){
            printf("FAIL: Baron cards not conserved.\n");
         }
         if (pre_EstateCount == post_EstateCount){
            printf("FAIL: Estate cards not conserved.\n");
         }
      }       
   #endif

   #if (NOISY_TEST == 1)
      if (  (choice1 == 0 && cardToBePlayedInHand && findCardInHand(estate, currentPlayer, &G)) ||
            (choice1 == 0 && cardToBePlayedInHand && !(findCardInHand(estate, currentPlayer, &G))) ||
            (choice1 == 1 && cardToBePlayedInHand && !(findCardInHand(estate, currentPlayer, &G)))
         ){
         if (G.coins != startingCoins){
            printf("FAIL: Coin count incorrect.\n");
         }
         if (pre_discardCount + 1 != post_discardCount){
            printf("FAIL: Discard count incorrect.\n");
         }
         if (pre_handCount - 1 != post_handCount){
            printf("FAIL: Hand count incorrect.\n");
         }
         if (post_estateSupply != pre_estateSupply - 1){
            printf("FAIL: Estate supply incorrect.\n");
         }
         if (pre_BaronCount != post_BaronCount){
            printf("FAIL: Baron cards not conserved.\n");
         }
         if (pre_EstateCount + 1 == post_EstateCount){
            printf("FAIL: Estate cards not conserved.\n");
         }
      }       
   #endif
   }  
   
   return 0;
}