/*
 *
 * Test for smithy room card
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

#define TESTCARD "smithy"

int pass = 0;
int fail = 0;

char spacing[20] = "~~~~~~~~~~~~~~~~~~~~";

void assertInt(int x, int y){
    if (x == y){
        printf("PASS\n");
        pass += 1;
    }
    else{
        printf("TEST FAILED\n");
        fail += 1;
    }   
}

enum STATE {
    start = 0,
    deck_c,
    discard_c,
    hand_c};

int main() {
    srand(time(NULL));

    int bonus = 0; 
    struct gameState baseG;
    struct gameState test_2;
    
    int currentState = 0;
    int i, thisPlayer, effect;
    for (i = 0; i < 10; i++){
        switch (currentState){
            case start:
                // initilize game
                thisPlayer = 0;
                test_2.handCount[thisPlayer] = (rand() % MAX_HAND);
                test_2.deckCount[thisPlayer] = (rand() % MAX_DECK);
                test_2.discardCount[thisPlayer] = (rand() % MAX_DECK);
                test_2.playedCardCount = 3;
                test_2.whoseTurn = thisPlayer;
                memcpy(&baseG, &test_2, sizeof(struct gameState));

                effect = cardEffect(smithy, 0, 0, 0, &test_2, 0, &bonus); 
                if (effect != 0)
                    fail++;
                currentState++;
            case deck_c:
                printf("deck %d, base: %d\n", test_2.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 3);
                assertInt(test_2.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 3);
                currentState++;
            case discard_c:
                printf("deck %d, base: %d\n", test_2.playedCardCount, baseG.playedCardCount + 1);
                assertInt(test_2.playedCardCount, baseG.playedCardCount + 1);
                currentState++;
            case hand_c:
                printf("deck %d, base: %d\n", test_2.handCount[thisPlayer], baseG.handCount[thisPlayer] + 2);
                assertInt(test_2.handCount[thisPlayer], baseG.handCount[thisPlayer] + 2);
                currentState = start;
        } // end of for loop
    }

    printf("~~~~~~~~~~TEST COMPLETE~~~~~~~~~~~~~~~ \n");
    printf("Pass: %d, Fail: %d\n\n", pass, fail);
    return 0;
}
