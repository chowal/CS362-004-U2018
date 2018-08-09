#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"


int main() {
    int seed = 1000;
    
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    struct gameState G, testG;
    int thisPlayer = 0;

    initializeGame(2, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    G.whoseTurn = thisPlayer;
    printf("deck count: %d\n", G.deckCount[thisPlayer]);
    printf("discard count: %d\n", G.discardCount[thisPlayer]);
    printf("hand count: %d\n", G.handCount[thisPlayer]);
    printf("played Card count: %d\n", G.playedCardCount);
    printf("whose turn: %d\n", G.whoseTurn);


    return 0;
}
