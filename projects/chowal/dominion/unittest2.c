/*
 * unittest2.c
 * function updatecoins 
 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "updateCoins"

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
    int thisPlayer = 0;
	struct gameState G;
    int bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};
    
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int mixed[MAX_HAND];
    int i,j;
    for(i = 0; i < MAX_HAND; i++){
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    for(j = 0; j < MAX_HAND; j++){
        if (j < 160){
            mixed[j] = copper;
        } else if (j > 160){
            mixed[j] = gold;
        } else {
            mixed[j] = silver;
        }
    }

    int handCount = 5;

	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
    // NOTE: Test 1-3 are similar to the example that was given
    // initialize a game state and player cards
    memset(&G, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    G.handCount[thisPlayer] = handCount;
    
	// ----------- TEST 1 --------------
	// DESCRIPTION: test that copper coins were added to the entire hand
    printf("TEST 1: Copper coins\n");
    memcpy(G.hand[thisPlayer], coppers, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 1 + bonus);
	
    printf("%s\n", spacing);

	// ----------- TEST 2 --------------
	// DESCRIPTION: test that silver coins were added to the entire hand
    printf("TEST 2: Silver coins\n");
    memcpy(G.hand[thisPlayer], silvers, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 2 + bonus);
	
    printf("%s\n", spacing);

	// ----------- TEST 3 --------------
	// DESCRIPTION: test that gold coins were added to the entire hand
    printf("TEST 3: Gold coins\n");
    memcpy(G.hand[thisPlayer], golds, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 3 + bonus);
	
    printf("%s\n", spacing);

	// ----------- TEST 4 --------------
	// DESCRIPTION: Test an addition of a bonus 
    printf("TEST 4: Test adding a bonus\n");
    bonus = 3;
    memcpy(G.hand[thisPlayer], coppers, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 1 + bonus);
	
    printf("%s\n", spacing);

    // ----------- TEST 5 --------------
	// DESCRIPTION: Test the max amount of bonus
    printf("TEST 5: Test max bonus\n");
    bonus = 10;
    memcpy(G.hand[thisPlayer], coppers, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 1 + bonus);
	
    printf("%s\n", spacing);

    // ----------- TEST 6 --------------
	// DESCRIPTION: Test the max amount of bonus
    printf("TEST 6: Test min bonus\n");
    bonus = 1;
    memcpy(G.hand[thisPlayer], coppers, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount * 1 + bonus);
	
    printf("%s\n", spacing);

	// ----------- TEST 7 --------------
	// DESCRIPTION: test that gold coins were added to the entire hand
    printf("TEST 7: Mixed amount of coins\n");
    bonus = 0;
    memcpy(G.hand[thisPlayer], mixed, sizeof(int) * handCount);
    updateCoins(thisPlayer, &G, bonus);
    assertInt(G.coins, handCount);
	
    printf("%s\n", spacing);


	printf("\n >>>>> Testing complete %s <<<<<\n", TESTFUNC);
	printf("\n >>>>> Pass: %d | Fail: %d <<<<<\n\n", passing, failing);

	return 0;
}
