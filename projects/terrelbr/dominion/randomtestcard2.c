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
   int i, j, h;
   struct gameState G;  
   int testCycles = 1000;

   for (i = 1; i <= testCycles; ++i){
   #if (NOISY_TEST == 1)
      printf("Minion card test %i/1000.\n", i);  
   #endif
      int bonus = 0;      
      int seed = (rand() % 1000) + 1;
      int startingCoins = (rand() % 50);
      int numPlayer = (rand() % (MAX_PLAYERS - 2)) + 2;    
      int choice1 = (rand() % 2);
      int choice2 = (rand() % 2);
      int choice3 = (rand() % 2);
      int player2 = (rand() % numPlayer - 1) + 1;
      int player3 = (rand() % numPlayer - 1) + 1;
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
   
      if ((rand() % 10)){
         gainCard(minion, &G, 2, currentPlayer);
      }

      for (j = 0; j < numPlayer; ++j){
         if((rand() % 2)){
            for (h = 0; h < (rand() % 6); ++h){
               discardCard(0, j, &G, 0);
            }
         }else{
            for (h = 0; h < (rand() % 6); ++h){
               gainCard(k[(rand() % 10)], &G, 2, j);
            }  
         }
      }

      updateCoins(currentPlayer, &G, startingCoins);        //Update coins
   
   #if (NOISY_TEST == 1)
         printf("Minion found in deck?   ");
         if (findCardInHand(minion, currentPlayer, &G)){
            printf(">YES<\n");
            cardToBePlayedInHand = 1;
         }else printf(">NO<\n");        
   #endif
   #if (NOISY_TEST == 1)
         printf("Choice conditions: choice1: %i, choice2: %i, choice3: %i\nNumber of players: %i\n", choice1, choice2, choice3, numPlayer);       
   #endif

      int pre_trashCount = G.playedCardCount;
      int pre_discardCountCP = G.discardCount[currentPlayer];
      int pre_discardCountP2 = G.discardCount[player2];
      int pre_discardCountP3 = G.discardCount[player3];
      int pre_handCountCP = G.handCount[currentPlayer];
      int pre_handCountP2 = G.handCount[player2];
      int pre_handCountP3 = G.handCount[player3];
      int pre_actions = G.numActions;
      
      cardEffect(minion, choice1, choice2, choice3, &G, 0, &bonus);


      int post_discardCountCP = G.discardCount[currentPlayer];
      int post_discardCountP2 = G.discardCount[player2];
      int post_discardCountP3 = G.discardCount[player3];
      int post_handCountCP = G.handCount[currentPlayer];
      int post_handCountP2 = G.handCount[player2];
      int post_handCountP3 = G.handCount[player3];
      int post_trashCount = G.playedCardCount;
      int post_actions = G.numActions;


   #if (NOISY_TEST == 1)
      if (  !(cardToBePlayedInHand) || 
            (choice1 == 1 && choice2 == 1) || 
            (choice1 == 0 && choice2 == 0)
         ){
         if (post_actions != pre_actions + 1){
            printf("FAIL: CP action count incorrect.\n");
         }
         if (pre_trashCount != post_trashCount){
            printf("FAIL: Cards were trashed.\n");
         }
         if (post_discardCountCP != pre_discardCountCP){
            printf("FAIL: CP Discard count incorrect.\n");
         }
         if (post_handCountCP != pre_handCountCP){
            printf("FAIL: CP Hand count incorrect.\n");
         }
         if (post_discardCountP2 != pre_discardCountP2){
            printf("FAIL: Player %i - Discard count incorrect.\n", player2);
         }
         if (post_handCountP2 != pre_handCountP2){
            printf("FAIL: Player %i - Hand count incorrect.\n", player2);
         }
         if (post_discardCountP3 != pre_discardCountP3){
            printf("FAIL: Player %i - Discard count incorrect.\n", player3);
         }
         if (post_handCountP3 != pre_handCountP3){
            printf("FAIL: Player %i - Hand count incorrect.\n", player3);
         }
         if (G.coins != startingCoins){
            printf("FAIL: CP Coin count incorrect.\n");
         }
      }       
   #endif

   #if (NOISY_TEST == 1)
      if (cardToBePlayedInHand && choice1 == 1 && choice2 == 0){
         if (post_actions != pre_actions + 1){
            printf("FAIL: CP action count incorrect.\n");
         }         
         if (pre_trashCount != post_trashCount){
            printf("FAIL: Cards were trashed.\n");
         }
         if (post_discardCountCP != pre_discardCountCP + 1){
            printf("FAIL: CP Discard count incorrect.\n");
         }
         if (post_handCountCP != pre_handCountCP - 1){
            printf("FAIL: CP Hand count incorrect.\n");
         }
         if (post_discardCountP2 != pre_discardCountP2){
            printf("FAIL: Player %i - Discard count incorrect.\n", player2);
         }
         if (post_handCountP2 != pre_handCountP2){
            printf("FAIL: Player %i - Hand count incorrect.\n", player2);
         }
         if (post_discardCountP3 != pre_discardCountP3){
            printf("FAIL: Player %i - Discard count incorrect.\n", player3);
         }
         if (post_handCountP3 != pre_handCountP3){
            printf("FAIL: Player %i - Hand count incorrect.\n", player3);
         }
         if (G.coins != startingCoins + 2){
            printf("FAIL: CP Coin count incorrect.\n");
         }
      }       
   #endif 

   #if (NOISY_TEST == 1)
      if (cardToBePlayedInHand && choice1 == 0 && choice2 == 1){
         if (post_actions != pre_actions + 1){
            printf("FAIL: CP action count incorrect.\n");
         }         
         if (pre_trashCount != post_trashCount){
            printf("FAIL: Cards were trashed.\n");
         }
         if (post_discardCountCP != pre_discardCountCP + pre_handCountCP){
            printf("FAIL: CP Discard count incorrect.\n");
         }
         if (post_handCountCP != 4){
            printf("FAIL: CP Hand count incorrect.\n");
         }
         if (pre_handCountP2 >= 5 && (post_discardCountP2 != (pre_discardCountP2 + pre_handCountP2))){
            printf("FAIL: Player %i - Discard count incorrect.\n", player2);
         }
         if (pre_handCountP2 >= 5 && (post_handCountP2 != 4)){
            printf("FAIL: Player %i - Hand count incorrect.\n", player2);
         }
         if (pre_handCountP3 >= 5 && (post_discardCountP3 != (pre_discardCountP3 + pre_handCountP3))){
            printf("FAIL: Player %i - Discard count incorrect.\n", player3);
         }
         if (pre_handCountP3 >= 5 && (post_handCountP3 != 4)){
            printf("FAIL: Player %i - Hand count incorrect.\n", player3);
         }
         if (G.coins != startingCoins){
            printf("FAIL: CP Coin count incorrect.\n");
         }
      }       
   #endif

      }
   return 0;
}