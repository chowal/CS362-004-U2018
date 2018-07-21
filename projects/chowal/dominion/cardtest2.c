/*
 * cardtest2.c
 * smithy
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int passing = 0;
int failing = 0;

char spacing[20] = "~~~~~~~~~~~~~~~~~~~~";

void assertInt(int x, int y){
    if (x == y){
        printf("PASS\n");
        passing += 1;
    }
    else{
        printf("TEST FAILED\n");
        failing += 1;
    }   
}

void assertIntNE(int x, int y){
    if (x != y){
        printf("PASS\n");
        passing += 1;
    }
    else{
        printf("FAILED\n");
        failing += 1;
    }   
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	// DESCRIPTION: Check the current game state
	//              To test this, we need to see if the current player gets the new cards
	printf("TEST 1: current game state\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    // test that the number of cards drawn is equal to the game state
    // along with discard pile
	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

    assertInt(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

    printf("%s\n", spacing);

    // ----------- TEST 2--------------
    // Description: Test that the card count has increased
    //
	printf("TEST 2: card count increased\n");

    // Played card count has increased and different from original game
	printf("played card count = %d, expected = %d\n", testG.playedCardCount + 1, G.playedCardCount);

    assertIntNE(testG.playedCardCount, G.playedCardCount);

    printf("%s\n", spacing);

    // ----------- TEST 3--------------
    // Description: check that the deck has been decremented after drawing
    //
	printf("TEST 3: Deck has been decremented\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

    assertInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

    printf("%s\n", spacing);

    // ----------- TEST 4--------------
    // Description: Check that other player's state remains the same
    //
	printf("TEST 4: Other player's state remains the same\n");
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);

    assertInt(testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
    assertInt(testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);

    printf("%s\n", spacing);

    // ----------- TEST 5 --------------
    // Description: Check whether victory cards hae been changed
    //
	printf("TEST 5: victory cards have not changed\n");
    printf("estate = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]); 
    printf("duchy = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]); 
    printf("province = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]); 

    assertInt(testG.supplyCount[estate], G.supplyCount[estate]);
    assertInt(testG.supplyCount[duchy], G.supplyCount[duchy]);
    assertInt(testG.supplyCount[province], G.supplyCount[province]);

    printf("%s\n", spacing);

    // ----------- TEST 6 --------------
    // Description: Check whether kingdom cards hae been changed
    //
	printf("TEST 6: kingdom cards have not changed\n");
    int i;
    for (i = 0; i < 10 ; i++){
        printf("kingdom card(%d) = %d, expected = %d\n", k[i], testG.supplyCount[k[i]], G.supplyCount[k[i]]); 
        assertInt(testG.supplyCount[k[i]], G.supplyCount[k[i]]);
    }

    printf("%s\n", spacing);


	printf("\n >>>>> Testing complete %s <<<<<\n", TESTCARD);
	printf("\n >>>>> Pass: %d | Fail: %d <<<<<\n\n", passing, failing);
	return 0;
}
