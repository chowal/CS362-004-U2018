/*
 *
 * Test for adventurer room card
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

#define TESTCARD "adventurer"

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
    hand_c,
    buy_c};

int main() {
    srand(time(NULL));

    int bonus = 0; 
    struct gameState baseG;
    struct gameState test_1;
    
    int currentState = 0;
    int i, thisPlayer, effect;
    for (i = 0; i < 8; i++){
        switch (currentState){
            case start:
                // initilize game
                thisPlayer = 0;
                test_1.handCount[thisPlayer] = (rand() % MAX_HAND);
                test_1.deckCount[thisPlayer] = (rand() % MAX_DECK);
                test_1.discardCount[thisPlayer] = (rand() % MAX_DECK);
                test_1.numBuys = (rand() % 3);
                test_1.playedCardCount = 3;
                test_1.whoseTurn = thisPlayer;
                memcpy(&baseG, &test_1, sizeof(struct gameState));

                //effect = cardEffect(adventurer, 0, 0, 0, &test_1, 0, &bonus); 
                effect = adventurer_f(0, test_1, thisPlayer); 
                if (effect != 0)
                    fail++;
                currentState++;
            case deck_c:
                printf("deck %d, base: %d\n", test_1.deckCount[thisPlayer], baseG.deckCount[thisPlayer]);
                assertInt(test_1.deckCount[thisPlayer], baseG.deckCount[thisPlayer]);
                currentState++;
            case discard_c:
                printf("DISCARD deck %d, base: %d\n", test_1.playedCardCount, baseG.playedCardCount + 1);
                assertInt(test_1.playedCardCount, baseG.playedCardCount + 1);
                currentState++;
            case hand_c:
                printf("deck %d, base: %d\n", test_1.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                assertInt(test_1.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                currentState++;
            case buy_c:
                printf("deck %d, base: %d\n", test_1.numBuys, baseG.numBuys + 1);
                assertInt(test_1.numBuys, baseG.numBuys + 1);
                currentState++;
        } // end of for loop
    }

    printf("~~~~~~~~~~TEST COMPLETE~~~~~~~~~~~~~~~ \n");
    printf("Pass: %d, Fail: %d\n\n", pass, fail);
    return 0;
}
