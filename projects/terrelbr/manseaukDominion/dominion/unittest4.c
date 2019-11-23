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
* This first test is based on the next player having an action card and a treasure card.
* Current player will gain 2 actions and 2 coins.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
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
   int nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   int pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(mine, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains Copper to deck.\n");
   printf ("Next  player gains Mine to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 2)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   int pre_trashCount = G.playedCardCount;
   int pre_discardCountCP = G.discardCount[currentPlayer];
   int pre_discardCountP2 = G.discardCount[1];
   int pre_discardCountP3 = G.discardCount[2];
   int pre_handCountCP = G.handCount[currentPlayer];
   int pre_handCountP2 = G.handCount[1];
   int pre_handCountP3 = G.handCount[2];
   int pre_deckCountCP = G.deckCount[currentPlayer];
   int pre_deckCountP2 = G.deckCount[1];
   int pre_deckCountP3 = G.deckCount[2];
   int pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   int post_trashCount = G.playedCardCount;
   int post_discardCountCP = G.discardCount[currentPlayer];
   int post_discardCountP2 = G.discardCount[1];
   int post_discardCountP3 = G.discardCount[2];
   int post_handCountCP = G.handCount[currentPlayer];
   int post_handCountP2 = G.handCount[1];
   int post_handCountP3 = G.handCount[2];
   int post_deckCountCP = G.deckCount[currentPlayer];
   int post_deckCountP2 = G.deckCount[1];
   int post_deckCountP3 = G.deckCount[2];
   int post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct + 2 == post_numAct){
         printf("P1 gained two actions. PASSED\n");
      }else printf("P1 gained two actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one cards. PASSED\n");
      }else printf("P1 hand count decreased by one cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2 + 2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2 - 2) == post_deckCountP2){
         printf("P2 deck count decreased by two. PASSED\n");
      }else printf("P2 deck count decreased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif



/*
*
* This test is based on the next player having an curse card and a treasure card.
* Current player will gain 2 coins.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
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
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(curse, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains Copper to deck.\n");
   printf ("Next  player gains Curse to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 2)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one cards. PASSED\n");
      }else printf("P1 hand count decreased by one cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2 + 2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2 - 2) == post_deckCountP2){
         printf("P2 deck count decreased by two. PASSED\n");
      }else printf("P2 deck count decreased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif

/*
*
* This test is based on the next player having two treasure cards.
* Current player will gain 2 coins.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
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
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains two Coppers to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 2)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one cards. PASSED\n");
      }else printf("P1 hand count decreased by one cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2 + 2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2 - 2) == post_deckCountP2){
         printf("P2 deck count decreased by two. PASSED\n");
      }else printf("P2 deck count decreased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif


/*
*
* This test is based on the next player having a copper and great_hall card.
* Current player will gain 2 coins and draw two cards.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
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
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   gainCard(great_hall, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains one Copper and one Great Hall to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 2)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");       
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP + 1 == post_handCountCP){
         printf("P1 hand count decreased by one and gained two cards. PASSED\n");
      }else printf("P1 hand count decreased by one and gained two cards. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2 + 2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2 - 2) == post_deckCountP2){
         printf("P2 deck count decreased by two. PASSED\n");
      }else printf("P2 deck count decreased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif



/*
*
* This test is based on the next player having only one 
* card and it is copper in the deck.
* Current player will gain 2 coins.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
      printf ("Starting game for test 5.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   while(G.deckCount[1] > 0){
      drawCard(nextPlayer, &G);
   }
   while(G.handCount[1] > 0){
      discardCard(0, nextPlayer, &G, 0);
   }
#if (NOISY_TEST == 1)
      if (G.handCount[1] == 0 && G.deckCount[1] == 0 && G.discardCount[1] == 0){
         printf("P2 has zero cards. PASSED\n");
      }else printf("P2 has zero cards. !!!FAILED!!!\n");        
#endif


#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 1, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains one Copper and one Tribute to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 1)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");       
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one. PASSED\n");
      }else printf("P1 hand count decreased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2 + 1) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2 - 1) == post_deckCountP2){
         printf("P2 deck count decreased by one. PASSED\n");
      }else printf("P2 deck count decreased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif


/*
*
* This test is based on the next player having only one 
* card and it is copper in the discard pile.
* Current player will gain 2 coins.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
      printf ("Starting game for test 6.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   while(G.deckCount[1] > 0){
      drawCard(nextPlayer, &G);
   }
   while(G.handCount[1] > 0){
      discardCard(0, nextPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
      if (G.handCount[1] == 0 && G.deckCount[1] == 0 && G.discardCount[1] == 0){
         printf("P2 has zero cards. PASSED\n");
      }else printf("P2 has zero cards. !!!FAILED!!!\n");        
#endif


#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 0, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains one Copper and one Tribute to deck.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 1)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one. PASSED\n");
      }else printf("P1 hand count decreased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2) == post_deckCountP2){
         printf("P2 deck count remianed the same. PASSED\n");
      }else printf("P2 deck count remianed the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif


/*
*
* This test is based on the next player having zero cards.
* Current player will gain nothing.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
      printf ("Starting game for test 7.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   while(G.deckCount[1] > 0){
      drawCard(nextPlayer, &G);
   }
   while(G.handCount[1] > 0){
      discardCard(0, nextPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
      if (G.handCount[1] == 0 && G.deckCount[1] == 0 && G.discardCount[1] == 0){
         printf("P2 has zero cards. PASSED\n");
      }else printf("P2 has zero cards. !!!FAILED!!!\n");        
#endif


#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player has zero cards.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct == post_numAct){
         printf("P1 gained zero actions. PASSED\n");
      }else printf("P1 gained zero actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 0){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one. PASSED\n");
      }else printf("P1 hand count decreased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2) == post_deckCountP2){
         printf("P2 deck count remianed the same. PASSED\n");
      }else printf("P2 deck count remianed the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif

/*
*
* This test is based on the next player having two cards in the discard pile.
* Current player will gain 2 coins and 2 actions.
*
*/

#if (NOISY_TEST == 1)
      printf ("\n\n\nTESTING tributeEffect():\n");
      printf ("Starting game for test 8.\n");        
#endif
      
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
      if (r == 0){
         printf("Game initialized. PASSED\n");
      }else printf("Game initialized. !!!FAILED!!!\n");        
#endif
   
   currentPlayer = whoseTurn(&G);
   nextPlayer = currentPlayer + 1;

   while(numHandCards(&G) > 0){              //Clear entire hand
      discardCard(0, currentPlayer, &G, 0);
   }
   while(G.deckCount[1] > 0){
      drawCard(nextPlayer, &G);
   }
   while(G.handCount[1] > 0){
      discardCard(0, nextPlayer, &G, 0);
   }

#if (NOISY_TEST == 1)
      if (G.handCount[1] == 0 && G.deckCount[1] == 0 && G.discardCount[1] == 0){
         printf("P2 has zero cards. PASSED\n");
      }else printf("P2 has zero cards. !!!FAILED!!!\n");        
#endif


#if (NOISY_TEST == 1)
   printf ("Current player's hand discarded.\n");
   printf ("Current player's hand count equals: %i\n", G.handCount[currentPlayer]);   
#endif
   
   pre_deckCountNP = G.deckCount[nextPlayer];

   gainCard(tribute, &G, 2, currentPlayer);    //Gain the cards neede to test the first state
   gainCard(copper, &G, 0, nextPlayer);    //Gain the cards neede to test the first state
   gainCard(mine, &G, 0, nextPlayer);    //Gain the cards neede to test the first state
   updateCoins(currentPlayer, &G, 0);        //Update coins to 0

#if (NOISY_TEST == 1)    
   printf ("Next player gains one Copper and one Mine to the discard pile.\n");
   if (G.deckCount[nextPlayer] == (pre_deckCountNP + 2)){
      printf("Next player deck count incremented correctly. PASSED\n");
   }else printf("Next player deck count incremented correctly. !!!FAILED!!!\n"); 
#endif

   pre_trashCount = G.playedCardCount;
   pre_discardCountCP = G.discardCount[currentPlayer];
   pre_discardCountP2 = G.discardCount[1];
   pre_discardCountP3 = G.discardCount[2];
   pre_handCountCP = G.handCount[currentPlayer];
   pre_handCountP2 = G.handCount[1];
   pre_handCountP3 = G.handCount[2];
   pre_deckCountCP = G.deckCount[currentPlayer];
   pre_deckCountP2 = G.deckCount[1];
   pre_deckCountP3 = G.deckCount[2];
   pre_numAct = G.numActions;

   cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
   
   post_trashCount = G.playedCardCount;
   post_discardCountCP = G.discardCount[currentPlayer];
   post_discardCountP2 = G.discardCount[1];
   post_discardCountP3 = G.discardCount[2];
   post_handCountCP = G.handCount[currentPlayer];
   post_handCountP2 = G.handCount[1];
   post_handCountP3 = G.handCount[2];
   post_deckCountCP = G.deckCount[currentPlayer];
   post_deckCountP2 = G.deckCount[1];
   post_deckCountP3 = G.deckCount[2];
   post_numAct = G.numActions;

#if (NOISY_TEST == 1)   
   printf ("Next player discards top two cards in deck for current player to gain.\n");
#endif
#if (NOISY_TEST == 1)
      if (pre_numAct + 2 == post_numAct){
         printf("P1 gained two actions. PASSED\n");
      }else printf("P1 gained two actions. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (G.coins == 2){
         printf("P1 gained two coins. PASSED\n");
      }else printf("P1 gained two coins. !!!FAILED!!!%i\n", G.coins);        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountCP - 1 == post_handCountCP){
         printf("P1 hand count decreased by one. PASSED\n");
      }else printf("P1 hand count decreased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP2 == post_handCountP2){
         printf("P2 hand count did not change. PASSED\n");
      }else printf("P2 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (pre_handCountP3 == post_handCountP3){
         printf("P3 hand count did not change. PASSED\n");
      }else printf("P3 hand count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountCP + 1) == post_discardCountCP){
         printf("P1 discard count increased by one. PASSED\n");
      }else printf("P1 discard count increased by one. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP2) == post_discardCountP2){
         printf("P2 discard count increased by two. PASSED\n");
      }else printf("P2 discard count increased by two. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_discardCountP3) == post_discardCountP3){
         printf("P3 discard count did not change. PASSED\n");
      }else printf("P3 discard count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if (findCardInHand(tribute, currentPlayer, &G) == -1){
         printf("P1 tribute Discarded. PASSED\n");
      }else printf("P1 tribute Discarded. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
   if (pre_trashCount == post_trashCount){
      printf("NO CARDS TRASHED. PASSED \n");
   }else printf("NO CARDS TRASHED. !!!FAILED!!!\n");        
#endif  
#if (NOISY_TEST == 1)
      if ((pre_deckCountCP) == post_deckCountCP){
         printf("Current player deck count did not change. PASSED\n");
      }else printf("Current player deck count did not change. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP2) == post_deckCountP2){
         printf("P2 deck count remianed the same. PASSED\n");
      }else printf("P2 deck count remianed the same. !!!FAILED!!!\n");        
#endif
#if (NOISY_TEST == 1)
      if ((pre_deckCountP3) == post_deckCountP3){
         printf("P3 deck count did not change. PASSED\n");
      }else printf("P3 deck count did not change. !!!FAILED!!!\n");        
#endif


  return 0;
}
