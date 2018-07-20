/*
 * cardtest3.c
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
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
    int xtraCoins = 0;
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
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Test how many cards are drawn --------------
	// Description: Need to check deck count and shuffles
	printf("TEST 1: Desk count and shuffle\n");

	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);

	assertInt(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertInt(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    printf("%s\n", spacing);

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	// Description: Testing how much treasure was give grom the adventurer
	printf("TEST 2: Drawn treasure\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertInt(testG.coins, G.coins + xtraCoins);
    printf("%s\n", spacing);

	// ----------- TEST 3: Check removing top card--------------
	// Description: Check that the top card is not the same as previously
	printf("TEST 3: Check the top card\n");

    memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("top card = %d, expected = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], G.hand[thisPlayer][G.handCount[thisPlayer]-1]);

    assertInt(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], G.hand[thisPlayer][G.handCount[thisPlayer]-1]);

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


