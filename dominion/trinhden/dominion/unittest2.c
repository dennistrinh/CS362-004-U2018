#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"


/*********************************************
 * void assertTrue(int, int)
 * This function checks for equality between
 * two values and lets the user know
 * if the test passed or not.
**********************************************/
void assertTrue(int x, int y) {
  if (x == y) {
    printf("TEST SUCCESSFULLY COMPLETED\n");
  } else {
    printf("TEST FAILED\n");
    printf("After: %d | Before: %d\n", x, y);
  }
}

int main() {
  // Declare all the necessary variables
  int seed = 1111;
  int numPlayers = 2;
  int player = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy, council_room};
  int handpos = 0;

  // Initialize the state
  struct gameState state;
  memset(&state, 23, sizeof(struct gameState));
  
  // Initialize the game 
  initializeGame(numPlayers, k, seed, &state);

  // Testing
  printf("Testing: discardCard()\n");
  
  // If trash flag is inactive, add to played pile
  printf("\nTest: Trash flag is 0, played card count should increase by 1\n");
  state.playedCardCount = 0;
  int before = state.playedCardCount;
  discardCard(handpos, player, &state, 0);
  assertTrue(state.playedCardCount, before + 1);

  // If handPos is the last card, decrement hand count
  handpos = state.handCount[player];
  discardCard(handpos, player, &state, 1);
  printf("\nTest: If handpos is the last card, handCount decrements by 1\n");
  assertTrue(state.handCount[player], handpos - 1);
  
  // Otherwise, replace the discarded card with last card in hand
  handpos = 1;
  before = state.hand[player][state.handCount[player] - 1];
  discardCard(handpos, player, &state, 1);
  printf("\nTest: handpos card is swapped with last card in hand\n");
  assertTrue(state.hand[player][handpos], before);

  // If there is only one card in the hand, just decrement
  state.handCount[player] = 1;
  discardCard(handpos, player, &state, 1);
  printf("\nTest: One card in hand, should result in no cards after discard\n");
  assertTrue(state.handCount[player], 0);

  return 0;

}
