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
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy, council_room};
  int player = 0;
  int toFlag = 0;
  // Initialize the state
  struct gameState state;
  memset(&state, 23, sizeof(struct gameState));
  
  // Initialize the game 
  initializeGame(numPlayers, k, seed, &state);

  // Testing
  printf("Testing: gainCard()\n");
  
  // If a supply pile is empty, return -1.
  printf("\nTest: There are no more adventurer cards, cannot gain a card.\n");
  state.supplyCount[adventurer] = 0;
  assertTrue(gainCard(adventurer, &state, toFlag, player), -1);

  // If adding a card to the deck, deck count should increase by 1 (toFlag = 1)
  toFlag = 1;
  state.supplyCount[adventurer] = 5;
  printf("\nTest: Adding an adventurer to the player's deck, deck size increased by 1\n");
  int before = state.deckCount[player];
  gainCard(adventurer, &state, toFlag, player);
  assertTrue(state.deckCount[player], before + 1);
  
  // If toFlag = 2 [add to hand], the hand count of the player should increase by 1.
  toFlag = 2;
  printf("\nTest: Adding an adventurer to the player's hand, hand size increased by 1\n");
  before = state.handCount[player];
  gainCard(adventurer, &state, toFlag, player);
  assertTrue(state.handCount[player], before + 1);

  // Otherwise if toFlag = 0, discard count should increase by 1.
  toFlag = 0;
  printf("\nTest: Adding an adventurer to the player's discard, discard size increased by 1\n");
  before = state.discardCount[player];
  gainCard(adventurer, &state, toFlag, player);
  assertTrue(state.discardCount[player], before + 1);

  return 0;

}
