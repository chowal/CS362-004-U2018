/*
 *
 * Test for council room card
 *
 *
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TESTCARD "council_room"

int pass = 0;
int fail = 0;
int debug = 0;

char spacing[20] = "~~~~~~~~~~~~~~~~~~~~";

void assertInt(int x, int y){
    if (x == y){
        if (debug)
            printf("PASS\n");
        pass += 1;
    }
    else{
        if (debug)
            printf("TEST FAILED\n");
        fail += 1;
    }   
}

enum STATE {
    start = 0,
    deck_c,
    discard_c,
    hand_c,
    buy_c};

int main() {
    srand(time(NULL));

    int bonus = 0; 
    struct gameState baseG;
    struct gameState test_1;
   
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
                sea_hag, tribute, smithy, council_room};
    
    int currentState = 0;
    int i, thisPlayer, numPlayers, effect, end;
    int old_d, old_h, old_b, old_p;
    
    numPlayers = (rand() % MAX_PLAYERS);
    initializeGame(numPlayers, k, 10000, &baseG);
    memcpy(&test_1, &baseG, sizeof(struct gameState));
    for (i = 0; i < 10000; i++){
        switch (currentState){
            case start:
                // initilize game
                
                thisPlayer = 0;
                test_1.handCount[thisPlayer] = (rand() % MAX_HAND);
                old_h = test_1.handCount[thisPlayer];
                test_1.deckCount[thisPlayer] = (rand() % MAX_DECK);
                old_d = test_1.deckCount[thisPlayer];
                test_1.discardCount[thisPlayer] = (rand() % MAX_DECK);
                test_1.numBuys = (rand() % 3);
                old_b = test_1.numBuys;
                test_1.whoseTurn = thisPlayer;
                test_1.playedCards[thisPlayer] = (rand() % MAX_DECK);
                test_1.playedCardCount = (rand() % MAX_DECK);
                old_p = test_1.playedCardCount;
        
                buyCard(council_room, &test_1); 
                effect = cardEffect(council_room, 0, 0, 0, &test_1, 0, &bonus); 

                if (effect != 0)
                    fail++;
                currentState++;
            case deck_c:
                if (debug)
                    printf("DECK old %d, current %d\n", old_d, test_1.deckCount[thisPlayer]);
                assertInt(test_1.deckCount[thisPlayer], old_d - 4);
                currentState++;
            case discard_c:
                if (debug)
                    //printf("DISCARD deck %d, base: %d\n", test_1.playedCardCount, baseG.playedCardCount + 1);
                    printf("DISCARD old %d, current %d\n", old_p, test_1.playedCardCount);
                //assertInt(test_1.playedCardCount, baseG.playedCardCount + 1);
                assertInt(test_1.playedCardCount, old_p + 1);
                currentState++;
            case hand_c:
                if (debug)
                    printf("HAND old %d, current %d\n", old_h, test_1.handCount[thisPlayer]);
                assertInt(test_1.handCount[thisPlayer], old_h + 3);
                currentState++;
            case buy_c:
                if (debug)
                    printf("BUY old %d, current %d\n", old_b, test_1.numBuys);
                assertInt(test_1.numBuys, old_b + 1);
                end = endTurn(&test_1);
                assertInt(end, 0);
                isGameOver(&test_1);
                currentState = start;
        } // end of for loop
    }

    printf("~~~~~~~~~~TEST COMPLETE~~~~~~~~~~~~~~~ \n");
    printf("Pass: %d, Fail: %d\n\n", pass, fail);
    return 0;
}
