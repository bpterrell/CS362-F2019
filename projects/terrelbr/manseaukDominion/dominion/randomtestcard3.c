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
   int v[19] = {copper, silver, gold, estate, duchy, province, gardens, great_hall, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, curse};
   int i;
   struct gameState G;  
   int testCycles = 1000;

   for (i = 1; i <= testCycles; ++i){
   #if (NOISY_TEST == 1)
      printf("Tribute card test %i/1000.\n", i);  
   #endif
      int bonus = 0;      
      int seed = (rand() % 1000) + 1;
      int startingCoins = (rand() % 50);
      int numPlayer = (rand() % (MAX_PLAYERS - 2)) + 2;    
      int choice1 = (rand() % 2);
      int choice2 = (rand() % 2);
      int choice3 = (rand() % 2);
      int topCard, secondCardDown;
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

      if ((rand() % 10)){
         gainCard(tribute, &G, 2, currentPlayer);
      }

      if (!(rand() % 100)){
         while(G.deckCount[1] > 0){
            drawCard(currentPlayer + 1, &G);
         }
         while(G.handCount[1] > 0){
            discardCard(0, currentPlayer + 1, &G, 0);
         }
         topCard = v[(rand() % 19)];
         secondCardDown = topCard;
         gainCard(topCard, &G, (rand() % 3), currentPlayer + 1);
      }else{
         secondCardDown = v[(rand() % 19)];
         gainCard(secondCardDown, &G, 2, currentPlayer + 1);
         topCard = v[(rand() % 19)];
         gainCard(topCard, &G, 2, currentPlayer + 1);  
      }      

      updateCoins(currentPlayer, &G, startingCoins);        //Update coins
   
   #if (NOISY_TEST == 1)
         printf("Tribute found in deck?   ");
         if (findCardInHand(tribute, currentPlayer, &G)){
            printf(">YES<\n");
            cardToBePlayedInHand = 1;
         }else printf(">NO<\n");        
   #endif
   #if (NOISY_TEST == 1)
         printf("Choice conditions: choice1: %i, choice2: %i, choice3: %i\nNumber of players: %i\n", choice1, choice2, choice3, numPlayer);       
   #endif

   int pre_trashCount = G.playedCardCount;
   int pre_discardCountCP = G.discardCount[currentPlayer];
   int pre_discardCountP2 = G.discardCount[1];
   int pre_handCountCP = G.handCount[currentPlayer];
   int pre_handCountP2 = G.handCount[1];
   int pre_deckCountCP = G.deckCount[currentPlayer];
   int pre_deckCountP2 = G.deckCount[1];
   int pre_numAct = G.numActions;

   cardEffect(tribute, choice1, choice2, choice3, &G, 0, &bonus);
   
   int post_trashCount = G.playedCardCount;
   int post_discardCountCP = G.discardCount[currentPlayer];
   int post_discardCountP2 = G.discardCount[1];
   int post_handCountCP = G.handCount[currentPlayer];
   int post_handCountP2 = G.handCount[1];
   int post_deckCountCP = G.deckCount[currentPlayer];
   int post_deckCountP2 = G.deckCount[1];
   int post_numAct = G.numActions;


   #if (NOISY_TEST == 1)
      if (!(cardToBePlayedInHand)){
         if (pre_numAct != post_numAct){
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
         if (post_deckCountCP != pre_deckCountCP){
            printf("FAIL: CP Deck count incorrect.\n");
         }
         if (post_discardCountP2 != pre_discardCountP2){
            printf("FAIL: Player 2  Discard count incorrect.\n");
         }
         if (post_handCountP2 != pre_handCountP2){
            printf("FAIL: Player 2 Hand count incorrect.\n");
         }
         if (post_deckCountP2 != pre_deckCountP2){
            printf("FAIL: Player 2 Deck count incorrect.\n");
         }
         if (G.coins != startingCoins){
            printf("FAIL: CP Coin count incorrect.\n");
         }
      }       
   #endif

      int numActionsGained = 0;
      int numCoinsGained = 0;
      int numCardsGained = 0;
   #if (NOISY_TEST == 1)
      if (cardToBePlayedInHand){
         if (topCard > 7 && topCard < 18){
            numActionsGained += 2;
         }
         else if (topCard > 2 && topCard <= 7){
            numCardsGained += 2;
         }
         else if (topCard <= 2){
            numCoinsGained += 2;
         }
         if (topCard != secondCardDown){
            if (secondCardDown > 7 && secondCardDown < 18){
               numActionsGained += 2;
            }
            else if (secondCardDown > 2 && secondCardDown <= 7){
               numCardsGained += 2;
            }
            else if (secondCardDown <= 2){
               numCoinsGained += 2;
            }
         }

         if (pre_numAct + numActionsGained != post_numAct){
            printf("FAIL: CP action count incorrect.\n");
         }
         if (pre_trashCount != post_trashCount){
            printf("FAIL: Cards were trashed.\n");
         }
         if (post_discardCountCP != pre_discardCountCP - 1){
            printf("FAIL: CP Discard count incorrect.\n");
         }
         if (post_handCountCP != pre_handCountCP + numCardsGained - 1){
            printf("FAIL: CP Hand count incorrect.\n");
         }
         if (post_deckCountCP != pre_deckCountCP - numCardsGained){
            printf("FAIL: CP Deck count incorrect.\n");
         }
         if (post_discardCountP2 != pre_discardCountP2 + 2){
            printf("FAIL: Player 2  Discard count incorrect.\n");
         }
         if (post_handCountP2 != pre_handCountP2){
            printf("FAIL: Player 2 Hand count incorrect.\n");
         }
         if (post_deckCountP2 != pre_deckCountP2 - 2){
            printf("FAIL: Player 2 Deck count incorrect.\n");
         }
         if (G.coins != startingCoins + numCoinsGained){
            printf("FAIL: CP Coin count incorrect.\n");
         }
      }       
   #endif

      }
   return 0;
}