#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include <stdlib.h>

// Globals
int failsCount = 0; // Accounts for hand/deck miscount
int failsTreasure = 0; // Accounts for treasure mismatch

int checkAdventurer(int x, struct gameState *post) {
  int bonus = 0;

  // Like testDrawCard, game state variable that allow
  // manual testing of function actions
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  // Call the adventurer card effect
  cardEffect(adventurer, 0, 0, 0, post, 0, &bonus);  

  // Break apart the adventurer function into multiple parts
  // It reveals cards until 2 treasure cards are shown.
  // It then discards itself and the cards that are not treasures.
  int treasure = 0; // Number of treasures drawn
  int topCard; // Card drawn
  int a = 0;
  int temp[MAX_HAND];
  while (treasure < 2) {
    // Shuffle if deck is empty
    if (pre.deckCount[x] == 0) {
      shuffle(x, &pre);
    }

    // Draw a card
    drawCard(x, &pre);
    topCard = pre.hand[x][pre.handCount[x] - 1];

    // If treasure is drawn, store it and increment
    if (topCard == copper || topCard == silver || topCard == gold) {
      treasure++;

    // Otherwise, remove the card.
    } else {
      temp[a] = topCard;
      pre.handCount[x]--;
      a++;
    }
  }
  // From the playAdventurer function to discard.
  while (a - 1 >= 0) {
    pre.discard[x][pre.discardCount[x]++] = temp[a - 1];
    a--;
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
    //printf("Test success.\n");
  } else {
    failsCount++;
  }

  // Count the treasure count created by test.
  int i, currentCard;
  int preTreasure = 0;
  for (i = 0; i < pre.handCount[x]; i++) {
    currentCard = pre.hand[x][i];
    if (currentCard == copper || currentCard == silver || currentCard == gold) {
      preTreasure++;
    }
  }
  
  // Count the treasure called by cardEffect
  int postTreasure = 0;
  for (i = 0; i < post->handCount[x]; i++) {
    currentCard = post->hand[x][i];
    if (currentCard == copper || currentCard == silver || currentCard == gold) {
      postTreasure++;
    }
  }

  // Compare the two counts
  if (preTreasure != postTreasure) {
    failsTreasure++;
  } 
}

int main () {

  printf("\nRandom Test for Smithy Card\n");
  
  // Initialize the game varibles
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int tests = 5000;
  struct gameState G;
  int i, j, l, p, treasures;
  int supp[] = {copper, silver, gold};
  srand(time(NULL));
  int req = 3; // Required at least 3 cards for adventurer card to work.
  // Randomize the game state
  for (i = 0; i < tests; i++) {
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * MAX_PLAYERS);
    G.deckCount[p] = floor(Random() * ((MAX_DECK - req) + 1) + req);
    G.discardCount[p] = floor(Random() * ((MAX_DECK - req) + 1) + req);
    G.handCount[p] = floor(Random() * ((MAX_HAND - req) + 1) + req);
    G.whoseTurn = p;
    treasures = floor(Random() * ((G.deckCount[p] - req) + 1) + req);
    for (l = 0; l < treasures; l++) {
      G.deck[p][l] = supp[rand() % 3];
    }
    checkAdventurer(p, &G);
  }
  
  // Print out results of random test.
  printf("\nResults of the tests\n");
  printf("FAILS: Hand or Deck Count doesn't match: %d\n", failsCount);
  printf("SUCCESS: Tests passed - %d\n\n", tests - failsCount);
  printf("FAILS: Improper amount of treasures: %d\n", failsTreasure);
  printf("SUCCESS: Treasures are the correct amount: %d\n", tests - failsTreasure);

  return 0;
}
