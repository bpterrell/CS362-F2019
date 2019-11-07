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
* This first test is based on the player having three copies of a card and only choosing to trash one to the supply pile 
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING ambassadorEffect():\n");
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

   gainCard(ambassador, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   int pre_handCountCP = G.handCount[currentPlayer];

#if (NOISY_TEST == 1)    
   printf ("Current player gains Ambassador.\n");
   printf ("Current player gains three Estate cards.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 4)){
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
   int pre_estateSupply = supplyCount(estate, &G);
   int pre_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   int pre_EstateCountP2 = fullDeckCount(1, estate, &G);
   int pre_EstateCountP3 = fullDeckCount(2, estate, &G);
   
   cardEffect(ambassador, 1, 1, 0, &G, 0, &bonus);
   
   int post_trashCount = G.playedCardCount;
   int post_discardCountCP = G.discardCount[currentPlayer];
   int post_discardCountP2 = G.discardCount[1];
   int post_discardCountP3 = G.discardCount[2];
   int post_handCountCP = G.handCount[currentPlayer];
   int post_handCountP2 = G.handCount[1];
   int post_handCountP3 = G.handCount[2];

   int post_estateSupply = supplyCount(estate, &G);
   int post_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   int post_EstateCountP2 = fullDeckCount(1, estate, &G);
   int post_EstateCountP3 = fullDeckCount(2, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("P1 trashes an Estate to make each other player gain one.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 2 == post_handCountCP){
         printf("P1 hand count decreased by two cards. PASSED\n");
      }else printf("P1 hand count decreased by two cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(ambassador, currentPlayer, &G) == -1){
         printf("Ambassador Discarded. PASSED\n");
      }else printf("Ambassador Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountCP == pre_EstateCountCP - 1 ){
         printf("P1 has one less estate card. PASSED\n");
      }else printf("P1 has one less estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP2 == pre_EstateCountP2 + 1 ){
         printf("P2 has one more estate card. PASSED\n");
      }else printf("P2 has one more estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP3 == pre_EstateCountP3 + 1 ){
         printf("P3 has one more estate card. PASSED\n");
      }else printf("P3 has one more estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == pre_estateSupply - 1){
      printf("Estate Supply gained one and lost two. PASSED\n");
   }else printf("Estate Supply gained one and lost two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif   
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2){
      printf("P2 Hand count is correct. PASSED \n");
   }else printf("P2 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3){
      printf("P3 Hand count is correct. PASSED \n");
   }else printf("P3 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP2 + 1 == post_discardCountP2){
      printf("P2 Discard count increased by one. PASSED \n");
   }else printf("P2 Discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP3 + 1 == post_discardCountP3){
      printf("P3 Discard count increased by one. PASSED \n");
   }else printf("P3 Discard count increased by one. !!!FAILED!!!\n");        
#endif



/*
*
* This test is based on the player having three copies of a card and choosing to trash three to the supply pile 
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING ambassadorEffect():\n");
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

   gainCard(ambassador, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   pre_handCountCP = G.handCount[currentPlayer];

#if (NOISY_TEST == 1)   
   printf ("Current player gains Ambassador.\n");
   printf ("Current player gains three Estate cards.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 4)){
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
   pre_estateSupply = supplyCount(estate, &G);
   pre_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   pre_EstateCountP2 = fullDeckCount(1, estate, &G);
   pre_EstateCountP3 = fullDeckCount(2, estate, &G);
   
   cardEffect(ambassador, 1, 3, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];

   post_estateSupply = supplyCount(estate, &G);
   post_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   post_EstateCountP2 = fullDeckCount(1, estate, &G);
   post_EstateCountP3 = fullDeckCount(2, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("P1 trashes an Estate to make each other player gain one.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP  == post_handCountCP){
         printf("P1 hand count decreased by 0 cards. PASSED\n");
      }else printf("P1 hand count decreased by 0 cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP) == post_discardCountCP){
         printf("P1 discard count increased by zero. PASSED\n");
      }else printf("P1 discard count increased by zero. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(ambassador, currentPlayer, &G) > -1){
         printf("Ambassador still in hand. PASSED\n");
      }else printf("Ambassador still in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountCP == pre_EstateCountCP){
         printf("P1 has the same number of estate cards. PASSED\n");
      }else printf("P1 has the same number of estate cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP2 == pre_EstateCountP2 ){
         printf("P2 did not gain an estate card. PASSED\n");
      }else printf("P2 did not gain an estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP3 == pre_EstateCountP3){
         printf("P3 did not gain an estate card. PASSED\n");
      }else printf("P3 did not gain an estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == pre_estateSupply){
      printf("Estate Supply did not change. PASSED\n");
   }else printf("Estate Supply did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif   
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2){
      printf("P2 Hand count is correct. PASSED \n");
   }else printf("P2 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3){
      printf("P3 Hand count is correct. PASSED \n");
   }else printf("P3 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP2 == post_discardCountP2){
      printf("P2 Discard count did not change. PASSED \n");
   }else printf("P2 Discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP3 == post_discardCountP3){
      printf("P3 Discard count did not change. PASSED \n");
   }else printf("P3 Discard count did not change. !!!FAILED!!!\n");        
#endif

/*
*
* This test is based on the player having one copy of a card and choosing to trash two to the supply pile 
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING ambassadorEffect():\n");
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

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(ambassador, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   pre_handCountCP = G.handCount[currentPlayer];

#if (NOISY_TEST == 1)   
   printf ("Current player gains Ambassador.\n");
   printf ("Current player gains three Estate cards.\n");
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
   pre_estateSupply = supplyCount(estate, &G);
   pre_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   pre_EstateCountP2 = fullDeckCount(1, estate, &G);
   pre_EstateCountP3 = fullDeckCount(2, estate, &G);
   
   cardEffect(ambassador, 1, 2, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];

   post_estateSupply = supplyCount(estate, &G);
   post_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   post_EstateCountP2 = fullDeckCount(1, estate, &G);
   post_EstateCountP3 = fullDeckCount(2, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("P1 trashes an Estate to make each other player gain one.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP  == post_handCountCP){
         printf("P1 hand count decreased by 0 cards. PASSED\n");
      }else printf("P1 hand count decreased by 0 cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP) == post_discardCountCP){
         printf("P1 discard count increased by zero. PASSED\n");
      }else printf("P1 discard count increased by zero. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(ambassador, currentPlayer, &G) > -1){
         printf("Ambassador still in hand. PASSED\n");
      }else printf("Ambassador still in hand. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountCP == pre_EstateCountCP){
         printf("P1 has the same number of estate cards. PASSED\n");
      }else printf("P1 has the same number of estate cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP2 == pre_EstateCountP2 ){
         printf("P2 did not gain an estate card. PASSED\n");
      }else printf("P2 did not gain an estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP3 == pre_EstateCountP3){
         printf("P3 did not gain an estate card. PASSED\n");
      }else printf("P3 did not gain an estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == pre_estateSupply){
      printf("Estate Supply did not change. PASSED\n");
   }else printf("Estate Supply did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif   
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2){
      printf("P2 Hand count is correct. PASSED \n");
   }else printf("P2 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3){
      printf("P3 Hand count is correct. PASSED \n");
   }else printf("P3 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP2 == post_discardCountP2){
      printf("P2 Discard count did not change. PASSED \n");
   }else printf("P2 Discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP3 == post_discardCountP3){
      printf("P3 Discard count did not change. PASSED \n");
   }else printf("P3 Discard count did not change. !!!FAILED!!!\n");        
#endif



/*
*
* This test is based on the player having three copies of a card and choosing to trash two to the supply pile 
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING ambassadorEffect():\n");
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

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif

   gainCard(ambassador, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(estate, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

   pre_handCountCP = G.handCount[currentPlayer];

#if (NOISY_TEST == 1)   
   printf ("Current player gains Ambassador.\n");
   printf ("Current player gains three Estate cards.\n");
   if (G.handCount[currentPlayer] == (pre_handCountCP + 4)){
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
   pre_estateSupply = supplyCount(estate, &G);
   pre_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   pre_EstateCountP2 = fullDeckCount(1, estate, &G);
   pre_EstateCountP3 = fullDeckCount(2, estate, &G);
   
   cardEffect(ambassador, 1, 2, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];

   post_estateSupply = supplyCount(estate, &G);
   post_EstateCountCP = fullDeckCount(currentPlayer, estate, &G);
   post_EstateCountP2 = fullDeckCount(1, estate, &G);
   post_EstateCountP3 = fullDeckCount(2, estate, &G);

#if (NOISY_TEST == 1)   
   printf ("P1 trashes 2 Estatea to make each other player gain one.\n");
   printf ("P1's hand count equals: %i\n", post_handCountCP);
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 3 == post_handCountCP){
         printf("P1 hand count decreased by 3 cards. PASSED\n");
      }else printf("P1 hand count decreased by 3 cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(ambassador, currentPlayer, &G) == -1){
         printf("Ambassador Discarded. PASSED\n");
      }else printf("Ambassador Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountCP == pre_EstateCountCP -2 ){
         printf("P1 has two less estate cards. PASSED\n");
      }else printf("P1 has two less estate cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP2 == pre_EstateCountP2 + 1 ){
         printf("P2 has one more estate card. PASSED\n");
      }else printf("P2 has one more estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (post_EstateCountP3 == pre_EstateCountP3 + 1 ){
         printf("P3 has one more estate card. PASSED\n");
      }else printf("P3 has one more estate card. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (post_estateSupply == pre_estateSupply + 2){
      printf("Estate Supply gained two and lost two. PASSED\n");
   }else printf("Estate Supply gained two and lost two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (G.coins == 0){
      printf("Coins did not change. PASSED %i\n", G.coins);
   }else printf("Coins did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif   
#if (NOISY_TEST == 1)
   if (pre_handCountP2 == post_handCountP2){
      printf("P2 Hand count is correct. PASSED \n");
   }else printf("P2 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_handCountP3 == post_handCountP3){
      printf("P3 Hand count is correct. PASSED \n");
   }else printf("P3 Hand count is correct. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP2 + 1 == post_discardCountP2){
      printf("P2 Discard count increased by one. PASSED \n");
   }else printf("P2 Discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_discardCountP3 + 1 == post_discardCountP3){
      printf("P3 Discard count increased by one. PASSED \n");
   }else printf("P3 Discard count increased by one. !!!FAILED!!!\n");        
#endif

  return 0;
}