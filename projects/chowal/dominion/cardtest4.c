/*
 * cardtest4.c
 * council_room
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"
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
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1 --------------
	// Description: Check the number of buys were given
	//
	printf("TEST 1: Check # of buys\n");
	printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
	assertInt(testG.numBuys, G.numBuys + 1);

    printf("%s\n", spacing);

	// ----------- TEST 2--------------
	// Description: Testing that 4 cards were drawn
	//
	printf("TEST 2: Deck count\n");
    newCards = 4;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

    assertInt(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

    printf("%s\n", spacing);

	// ----------- TEST 3--------------
	// Description: Check that the players deck has been decremented
	//
	printf("TEST 3: Decrement deck after drawing\n");
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);

    assertInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    
    printf("%s\n", spacing);

    // TODO this test doesnt work.  Only occurs when a turn has ended!!
    /*
	// ----------- TEST 4: Card has been discarded--------------
	// Descritpion: Test whether card has been discarded after playing
	printf("TEST 4: Card has been discarded\n");
    printf("deck count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
    assertInt(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);

    printf("%s\n", spacing);*/

    // ----------- TEST 5--------------
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

    // ----------- TEST 6--------------
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
