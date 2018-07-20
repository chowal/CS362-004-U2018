/*
 * unittest4.c
 * function getWinners
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "getWinners"

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
    // the players f2r this test
    int players[MAX_PLAYERS];
	struct gameState G, testG, newGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

        
	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
	// ----------- TEST 1 --------------
	// DESCRIPTION: Score for everyone except winner is 0
    printf("TEST 1: defaulting all unused players' scores\n");
    gainCard(3, &testG, 2, 1);
    gainCard(3, &testG, 2, 1);
    int win_result = getWinners(players, &testG);
    
    int losers, i;
    for (i = 0; i < MAX_PLAYERS; i++){
        if (players[i] == 0)
            losers++;
    }
    assertInt(MAX_PLAYERS - 1, losers);
   
    printf("%s\n", spacing);
    
	// ----------- TEST 2 --------------
	// Description: Winner 1 = function returned 0
	printf("TEST 2: function returns 0\n");

    assertInt(win_result, 0); 

    printf("%s\n", spacing);

	// ----------- TEST 3 --------------
	// Description: player 2 wins
	printf("TEST 3: player 2 is the winner\n");

    memset(&newGame, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &newGame);

    int newPlayers[MAX_PLAYERS];
    // resetting hands
    gainCard(3, &newGame, 2, 1);
    gainCard(3, &newGame, 2, 1);
    gainCard(3, &newGame, 2, 1);
    int new_win_result = getWinners(newPlayers, &newGame);
    win_result = getWinners(newPlayers, &newGame);
    
    assertInt(newPlayers[1], 1); 
    assertInt(new_win_result, 0);

    printf("%s\n", spacing);

	printf("\n >>>>> Testing complete %s <<<<<\n", TESTFUNC);
	printf("\n >>>>> Pass: %d | Fail: %d <<<<<\n\n", passing, failing);

	return 0;
}
