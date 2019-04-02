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

  // Initialize the state
  struct gameState state;
  memset(&state, 23, sizeof(struct gameState));
  
  // Initialize the game 
  initializeGame(numPlayers, k, seed, &state);

  // Testing
  printf("Testing: shuffle()\n");
  
  // If player's deck is empty, cannot shuffle returns -1
  printf("\nTest: If deck is empty, shuffle returns -1\n");
  state.deckCount[player] = 0;
  assertTrue(shuffle(player, &state), -1);

  // Shuffling the deck should not affect the count of the discard pile
  printf("\nTest: Discard pile unchanged after shuffle\n");
  state.discardCount[player] = 5;
  shuffle(player, &state);
  assertTrue(state.discardCount[player], 5);

  // Shuffling the deck should result in the same number of cards in the deck
  printf("\nTest: Deck has same number of cards after shuffle\n");
  state.deckCount[player] = 5;
  shuffle(player, &state);
  assertTrue(state.deckCount[player], 5);

  // Check for shuffling
  printf("\nTest: Check to see if cards are shuffled.\n");
  int before = state.deck[player][2];
  shuffle(player, &state);
  int after = state.deck[player][2];
  if (before != after)
    assertTrue(0, 0);
  else
    assertTrue(0, 1);

  return 0;

}
