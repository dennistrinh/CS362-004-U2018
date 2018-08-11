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
  int handpos = 5, choice1 = 0, choice2 = 5, choice3 = 0, bonus = 0;
  int player1 = 0;
  int player2 = 1;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy, council_room};

  // Records the state before and after a card effect
  struct gameState before, after;
  memset(&before, 23, sizeof(struct gameState));
  memset(&after, 23, sizeof(struct gameState));
  
  // Initialize the game and copy the state to "before" 
  initializeGame(numPlayers, k, seed, &after);
  memcpy(&before, &after, sizeof(struct gameState));

  // Testing
  printf("Testing: Mine\n");
  cardEffect(mine, choice1, choice2, choice3, &after, handpos, &bonus);

  // Check if the player drew 0 cards 
  printf("\nTest: Player 1 should not have drawn additional cards\n");
  assertTrue(after.handCount[player1], before.handCount[player1]);

  // Player should have gained a new treasure
  printf("\nPlayer 1 should have a new treasure (silver).\n");
  int i, currentCard;
  int afterC = 0, afterS = 0, afterG = 0;
  int beforeC = 0, beforeS = 0, beforeG = 0;

  // See how many treasures were gained by mine card
  for (i = 0; i < after.handCount[player1]; i++) {
    currentCard = after.hand[player1][i];
    if (currentCard == copper)
      afterC++;
    else if (currentCard == silver)
      afterS++;
    else if (currentCard == gold)
      afterG++;	
  }

  // See how many treasures the player had before mine was played
  for (i = 0; i < before.handCount[player1]; i++) {
    currentCard = before.hand[player1][i];
    if (currentCard == copper) 
      beforeC++;
    else if (currentCard == silver)
      beforeS++;
    else if (currentCard == gold)
      beforeG++;
  }
  
  printf("Test: Player 1 should have one less copper\n");
  assertTrue(afterC, beforeC - 1);
  printf("Test: Player 1 should have one more silver\n");
  assertTrue(afterS, beforeS + 1);
  printf("Test: Player 1 should have the same amount of gold\n");
  assertTrue(afterG, beforeG);

  // Player 2's state should remain unchanged
  printf("\nPlayer 2 should remain unchanged\n");
  printf("Test: Player 2's Deck Count\n");
  assertTrue(after.deckCount[player2], before.deckCount[player2]);
  printf("Test: Player 2's Hand Count\n");
  assertTrue(after.handCount[player2], before.handCount[player2]);
  
  // The kingdom supply should be unchanged
  printf("\nThe kingdom supply should be unchanged\n");
  printf("This should return 10 successful tests\n");
  for (i = 0; i < 10; i++) {
    printf("Test %d: ", i);
    assertTrue(after.supplyCount[k[i]], before.supplyCount[k[i]]);
  }

  // Victory cards should remain unchanged
  printf("\nThe victory card supply should remain unchanged\n");
  // Estate supply
  printf("Test: Estate quantity\n");
  assertTrue(after.supplyCount[estate], before.supplyCount[estate]);
  // Duchy supply
  printf("Test: Duchy quantity\n");
  assertTrue(after.supplyCount[duchy], before.supplyCount[duchy]);
  // Province supply
  printf("Test: Province quantity\n");
  assertTrue(after.supplyCount[province], before.supplyCount[province]);

  return 0;

}
