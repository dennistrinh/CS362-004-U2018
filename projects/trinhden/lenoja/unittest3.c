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

  // Initialize the state
  struct gameState state;
  memset(&state, 23, sizeof(struct gameState));
  
  // Initialize the game 
  initializeGame(numPlayers, k, seed, &state);

  // Testing
  printf("Testing: isGameOver()\n");
  
  // Province cards are out, game should end.
  printf("\nTest: Province cards are out, game is over.\n"); 
  state.supplyCount[province] = 0;
  assertTrue(isGameOver(&state), 1);

  // Province cards still in play, game should continue.
  printf("\nTest: Province cards are okay, supply is fine, game is NOT over.\n"); 
  state.supplyCount[province] = 1;
  assertTrue(isGameOver(&state), 0);

  // Three supply are empty, game is over.
  printf("\nTest: Three supply piles are 0, game is over\n");
  state.supplyCount[0] = 0;
  state.supplyCount[1] = 0;
  state.supplyCount[2] = 0;
  assertTrue(isGameOver(&state), 1);
  
  // Two supply are empty, provinces okay, game should continue.
  printf("\nTest: Two supply piles empty, provinces okay, game should continue\n");
  state.supplyCount[0] = 2;
  assertTrue(isGameOver(&state), 0);
  
  return 0;

}
