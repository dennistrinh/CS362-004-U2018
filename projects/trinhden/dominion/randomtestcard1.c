#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include <stdlib.h>

// Globals
int fails = 0;

int checkSmithy(int x, struct gameState *post) {
  int bonus = 0;

  // Like testDrawCard, game state variable that allow
  // manual testing of function actions
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  // Call smithy card effect
  cardEffect(smithy, 0, 0, 0, post, 0, &bonus);  

  // Break apart the smithy function into multiple parts
  // It draws 3 cards and discards itself.
  drawCard(x, &pre);
  drawCard(x, &pre);
  drawCard(x, &pre);
  discardCard(0, x, &pre, 0);

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
    printf("Test success.\n");
  } else {
    fails++;
  }

}

int main () {

  printf("\nRandom Test for Smithy Card\n");
  
  // Initialize the game varibles
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int tests = 5000;
  struct gameState G;
  int i, j, p;
  srand(time(NULL));

  // Randomize the game state
  for (i = 0; i < tests; i++) {
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * MAX_PLAYERS);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.whoseTurn = p;
    checkSmithy(p, &G);
  }
  
  // Print out results of random test.
  printf("\nResults of the tests\n");
  printf("FAILS: Hand or Deck Count doesn't match: %d\n", fails);
  printf("SUCCESS: Tests passed - %d\n\n", tests - fails);

  return 0;
}
