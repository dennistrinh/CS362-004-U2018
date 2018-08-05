#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include <stdlib.h>

// Globals (One to count hand/deck error, one for buy phase)
int failsCount = 0;
int failsBuy = 0;
int failsOtherPlayer = 0;

int checkCouncil(int x, struct gameState *post) {
  int bonus = 0;

  // Like testDrawCard, game state variable that allow
  // manual testing of function actions
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  // Call council room card effect
  cardEffect(council_room, 0, 0, 0, post, 0, &bonus);  

  // Break apart the council room effect into multiple parts
  // It draws 4 cards, adds a buy phase, and discards itself.
  drawCard(x, &pre);
  drawCard(x, &pre);
  drawCard(x, &pre);
  drawCard(x, &pre);
  pre.numBuys++;
  discardCard(0, x, &pre, 0);

  // Have every other player draw a card
  int i;
  for (i = 0; i < pre.numPlayers; i++) {
    if (i != x) {
      drawCard(i, &pre); 
    }
  }

  // Compare the other player hands pre and post game
  for (i = 0; i < pre.numPlayers; i++) {
    if (i != x) {
      if (!(pre.handCount[i] == post->handCount[i] &&
            pre.deckCount[i] == post->deckCount[i])) {
              failsOtherPlayer++;
      } 
    }
  }

  // Hand and deck counts
  // Booleans to determine equality
  int handCount = 0;
  int deckCount = 0;

  // If the counts are equal return true (1)
  if (pre.handCount[x] == post->handCount[x]) {
    handCount = 1;
  }
  if (pre.deckCount[x] == post->deckCount[x]) {
    deckCount = 1;
  }

  // If both true, test is okay. Otherwise, increment fails.
  if (handCount == 1 && deckCount == 1) {
    //printf("Test for hand/deck count success.\n");
  } else {
    failsCount++;
  }

  // If buy count is equal, test is okay. Otherwise, increment fails.
  if (pre.numBuys != post->numBuys) {
    failsBuy++;
  }
}

int main () {

  printf("\nRandom Test for Council Room Card\n");
  
  // Initialize the game varibles
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int tests = 5000;
  struct gameState G;
  int i, j, l, p;
  int deckCount, discardCount, handCount;
  srand(time(NULL));

  // Randomize the game state
  for (i = 0; i < tests; i++) {
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    G.numPlayers = (rand() % 4) + 1;
    //printf("Players: %d\n", G.numPlayers);
    G.numBuys = 1;
    p = rand() % 4;
    deckCount = floor(Random() * MAX_DECK);
    discardCount = floor(Random() * MAX_DECK);
    handCount = floor(Random() * MAX_HAND);
    G.whoseTurn = p;
    G.playedCardCount = floor(Random() * (MAX_DECK));
    for (l = 0; l < G.numPlayers; l++) {
      G.deckCount[l] = deckCount;
      G.discardCount[l] = discardCount;
      G.handCount[l] = handCount;
    }

    checkCouncil(p, &G);
  }
  
  // Print out results of random test.
  printf("\nResults of the tests\n");
  printf("FAILS: Hand or Deck Count doesn't match: %d\n", failsCount);
  printf("SUCCESS: Tests passed (Hand/Deck Count)- %d\n", tests - failsCount);
  printf("FAILS: Number of buys don't match: %d\n", failsBuy);
  printf("SUCCESS: Number of buys match - %d\n", tests - failsBuy);
  printf("FAILS: Other player draw unsuccessful: %d\n", failsOtherPlayer);
  printf("SUCCESS: Other player draw success: %d\n\n", tests - failsOtherPlayer);

  return 0;
}
