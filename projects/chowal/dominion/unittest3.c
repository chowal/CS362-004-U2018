/*
 * unittest3.c
 * function isGameOver 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "isGameOver"

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
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    
	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
	// ----------- TEST 1 --------------
	// DESCRIPTION: Check Province cards 
    printf("TEST 1: Province card desk check\n");
    
	printf("province cards = %d\n", testG.supplyCount[province]);
    testG.supplyCount[province] = 0; 
    printf("Supply count reduced\n");
	printf("province cards = %d\n", testG.supplyCount[province]);
    
    assertInt(isGameOver(&testG), 1);

    // resetting supply count for next tests
    testG.supplyCount[province] = 8; 

    printf("%s\n", spacing);
    
	// ----------- TEST 2 --------------
	// DESCRIPTION: 3 supply piles are at 0, the game ends 
	printf("TEST 2: Check 3 supply piles, Game ends\n");
    
    printf("coppers = %d, silvers = %d, golds = %d\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);     
    
    testG.supplyCount[copper] = 0;
    testG.supplyCount[silver] = 0;
    testG.supplyCount[gold] = 0;

    printf("Supply count reduced\n");
    printf("coppers = %d, silvers = %d, golds = %d\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);     
    assertInt(isGameOver(&testG), 1);    

    // resetting coins for the next test
    testG.supplyCount[copper] = 46;
    testG.supplyCount[silver] = 40;
    testG.supplyCount[gold] = 30;

    printf("%s\n", spacing);

    // ----------- TEST 3 --------------
	// DESCRIPTION: 2 supply piles are at 0, game does NOT end
	printf("TEST 3: Check 2 piles, Game does NOT end\n");
    
    printf("coppers = %d, silvers = %d\n", testG.supplyCount[copper], testG.supplyCount[silver]);
    
    testG.supplyCount[copper] = 0;
    testG.supplyCount[silver] = 0;

    printf("Supply count reduced\n");
    printf("coppers = %d, silvers = %d\n", testG.supplyCount[copper], testG.supplyCount[silver]);
    assertInt(isGameOver(&testG), 0);

    // resetting coins for the next test
    testG.supplyCount[copper] = 46;
    testG.supplyCount[silver] = 40;

    printf("%s\n", spacing);

    // ----------- TEST 4 --------------
	// DESCRIPTION: 4 supply piles are at 0, game does ends
	printf("TEST 4: Check 4 piles, Game ends\n");
    
    printf("coppers = %d, silvers = %d, golds = %d, adventurer = %d\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold], testG.supplyCount[adventurer]);
    
    testG.supplyCount[copper] = 0;
    testG.supplyCount[silver] = 0;
    testG.supplyCount[gold] = 0;
    testG.supplyCount[adventurer] = 0;

    printf("Supply count reduced\n");
    printf("coppers = %d, silvers = %d, golds = %d, adventurer = %d\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold], testG.supplyCount[adventurer]);
    assertInt(isGameOver(&testG), 1);

    printf("%s\n", spacing);
    

	printf("\n >>>>> Testing complete %s <<<<<\n", TESTFUNC);
	printf("\n >>>>> Pass: %d | Fail: %d <<<<<\n\n", passing, failing);

	return 0;
}
