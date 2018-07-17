/*
 * unittest1.c
 * function playCard
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "playCard"

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
        printf("TEST FAILED\n");
        failing += 1;
    }   
}

void assertGT_LT(int x, int y, int GT_LT){
    // GT_LT == 0 -> Less than
    if (GT_LT == 0){
        if ( x < y ) {
            printf("PASS\n");
            passing += 1;
        }
        else {
            printf("TEST FAILED\n");
            failing += 1;
        }
    // GT_LT == 1 -> Greater than
    } else {
        if ( x > y ) {
            printf("PASS\n");
            passing += 1;
        }
        else {
            printf("TEST FAILED\n");
            failing += 1;
        }
    }
}

int main() {
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // giving player the smithy card to play
    int smithyPos = -1;
    int i;
    testG.hand[thisPlayer][5] = smithy;
    gainCard(smithy, &testG, 2, thisPlayer);
    gainCard(smithy, &G, 2, thisPlayer);
    for(i = 0; i < numHandCards(&testG); i++){
        if (handCard(i, &testG) == smithy)
            smithyPos = i;
    }

	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
	// ----------- TEST 1 --------------
	// DESCRIPTION: Check that the phase is correct
    printf("TEST 1: Phase is correct\n");
    
	printf("test game = %d, game = %d,  expected = 0\n", testG.phase, G.phase);
    assertInt(testG.phase, 0);
    assertInt(G.phase, 0);

    printf("%s\n", spacing);
    
	// ----------- TEST 2 --------------
	// DESCRIPTION: Check that the player has actions
    printf("TEST 2: Enough Actions?\n");
    printf("actions = %d, expected = 1\n", testG.numActions);
    assertInt(testG.numActions, 1);

    printf("%s\n", spacing);


// PLAY THE CARD HERE
    // for coin test
    int res = playCard(smithyPos, choice1, choice2, choice3, &testG);

	// ----------- TEST 3 --------------
	// DESCRIPTION: Getting the correct card in handpos 
    printf("TEST 3: Correct card is in hand\n");
    int tg = handCard(smithyPos, &testG);
    int g = handCard(smithyPos, &G);
    printf("card = %d, expected = %d\n", tg, g);
    assertInt(tg, g);

    printf("%s\n", spacing);

	// ----------- TEST 4 --------------
	// DESCRIPTION: check number of actions 
    printf("TEST 4: Test Actions after played\n");
    printf("actions = %d, expected = 0\n", testG.numActions);
    assertInt(testG.numActions, 0);

    printf("%s\n", spacing);
     
     // ----------- TEST 5 --------------
	// DESCRIPTION:Test smithy card was played 
    printf("TEST 5: Smithy card played\n");

    printf("card in pos: %d, expected: %d\n", testG.hand[thisPlayer][smithyPos], smithy);
    assertInt(testG.hand[thisPlayer][smithyPos], smithy);

    printf("%s\n", spacing);

    // ----------- TEST 6 --------------
	// DESCRIPTION: No errors after playcard 
	printf("TEST 6: no errors during playcard\n");
    printf("Errors %d, expected = 0\n", res);
    assertInt(res, 0);
    
    printf("%s\n", spacing);


	printf("\n >>>>> Testing complete %s <<<<<\n", TESTFUNC);
	printf("\n >>>>> Pass: %d | Fail: %d <<<<<\n\n", passing, failing);

	return 0;
}
