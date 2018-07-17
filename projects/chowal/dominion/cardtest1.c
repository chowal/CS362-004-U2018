/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

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
    int action = 1;
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
    memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1 --------------
	// DESCRIPTION: Check that the correct player is interacting with the card
	// 
    printf("TEST 1: Correct player is playing the %s card\n", TESTCARD);
    
	printf("current player = %d, expected = %d\n", testG.whoseTurn, G.whoseTurn);
    //assert(testG.whoseTurn == G.whoseTurn);
    assertInt(testG.whoseTurn, G.whoseTurn);
    printf("%s\n", spacing);
    
	// ----------- TEST 2 --------------
	// DESCRIPTION: Check that the player has 1 more card
	// 
	printf("TEST 2: Player gets a new card\n");
	
	newCards = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    assertInt(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

	//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
    assertInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    printf("%s\n", spacing);

	// ----------- TEST 3: choice1 = 2 = +2 coins --------------
	// DESCRIPTION: Check that the player has 1 more action
	//
	printf("TEST 3: Player gets a new action\n");

	newCards = 1;
	printf("player actions = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	//assert(testG.numActions == G.numActions + action);
    assertInt(testG.numActions, G.numActions + action);
    printf("%s\n", spacing);

    // ----------- TEST 4: No changes to victory cards--------------
    // Description: Check whether victory cards hae been changed
	printf("TEST 4: victory cards have not changed\n");
    printf("estate = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]); 
    printf("duchy = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]); 
    printf("province = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]); 

    assertInt(testG.supplyCount[estate], G.supplyCount[estate]);
    assertInt(testG.supplyCount[duchy], G.supplyCount[duchy]);
    assertInt(testG.supplyCount[province], G.supplyCount[province]);

    printf("%s\n", spacing);

    // ----------- TEST 5: No changes to kingdom cards--------------
    // Description: Check whether kingdom cards hae been changed
	printf("TEST 5: kingdom cards have not changed\n");
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
