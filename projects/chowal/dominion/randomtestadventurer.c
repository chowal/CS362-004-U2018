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
    treasure_c};

int main() {
    srand(time(NULL));

    int bonus = 0; 
    struct gameState baseG;
    struct gameState test_a;
    
    int currentState = 0;
    int i, j, k, thisPlayer, effect, treasureCount, currentCard;
    for (i = 0; i < 10; i++){
        switch (currentState){
            case start:
                // initilize game
                thisPlayer = 0;
                test_a.handCount[thisPlayer] = (rand() % MAX_HAND);
                test_a.deckCount[thisPlayer] = (rand() % MAX_DECK);
                test_a.discardCount[thisPlayer] = (rand() % MAX_DECK);
                test_a.playedCardCount = 3;
                //treasureLimit = (rand() % test_a.deckCount[thisPlayer]); 
                for (j = 0; j < test_a.deckCount[thisPlayer]; j++){
                    test_a.deck[thisPlayer][j] = copper;
                    test_a.deck[thisPlayer][j] = silver;
                    test_a.deck[thisPlayer][j] = gold;
                }
                test_a.whoseTurn = thisPlayer;
                memcpy(&baseG, &test_a, sizeof(struct gameState));

                effect = cardEffect(adventurer, 0, 0, 0, &test_a, 0, &bonus); 
                if (effect != 0)
                    fail++;
                currentState++;
            case deck_c:
                printf("deck %d, base: %d\n", test_a.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 2);
                assertInt(test_a.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 2);
                currentState++;
            case discard_c:
                printf("DISCARD deck %d, base: %d\n", test_a.playedCardCount, baseG.playedCardCount);
                assertInt(test_a.playedCardCount, baseG.playedCardCount);
                currentState++;
            case hand_c: 
                printf("HAND deck %d, base: %d\n", test_a.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                assertInt(test_a.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                currentState++;
            case treasure_c:
                for(k = 0; k < test_a.handCount[thisPlayer]; k++){
                    currentCard = test_a.hand[thisPlayer][k]; 
                    if (currentCard == copper || currentCard == silver || currentCard == gold){
                        treasureCount++;
                    }     
                }
                printf("treasure %d\n", treasureCount);
                currentState = start;  
        } // end of for loop
    }

    printf("~~~~~~~~~~TEST COMPLETE~~~~~~~~~~~~~~~ \n");
    printf("Pass: %d, Fail: %d\n\n", pass, fail);
    return 0;
}
