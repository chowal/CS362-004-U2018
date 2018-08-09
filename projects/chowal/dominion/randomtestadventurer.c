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
void assertIntNE(int x, int y){
    if (x != y){
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
    treasure_c};

int main() {
    srand(time(NULL));

    int bonus = 0; 
    struct gameState baseG;
    struct gameState test_a;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, 
                sea_hag, tribute, smithy, council_room};

    
    int currentState = 0;
    int i, j, t, thisPlayer, effect, treasureCount, currentCard, numPlayers;
    int n, base_t;
    for (i = 0; i < 1000; i++){
        switch (currentState){
            case start:
                // initilize game
                numPlayers = (rand() % 4);
                initializeGame(numPlayers, k, 10000, &baseG);
                thisPlayer = 0;
                test_a.handCount[thisPlayer] = (rand() % MAX_HAND);
                test_a.deckCount[thisPlayer] = (rand() % MAX_DECK);
                test_a.discardCount[thisPlayer] = (rand() % MAX_DECK);
                test_a.playedCardCount = (rand() % MAX_DECK);
                test_a.numBuys = (rand() % 3);
                test_a.whoseTurn = thisPlayer;
                test_a.playedCards[thisPlayer] = (rand() % MAX_DECK);
                //treasureLimit = (rand() % test_a.deckCount[thisPlayer]); 
                for (j = 0; j < test_a.handCount[thisPlayer]; j++){
                    test_a.deck[thisPlayer][j] = copper;
                    test_a.deck[thisPlayer][j] = silver;
                    test_a.deck[thisPlayer][j] = gold;
                }
                memcpy(&baseG, &test_a, sizeof(struct gameState));

                effect = cardEffect(adventurer, 0, 0, 0, &test_a, 0, &bonus); 
                if (effect != 0)
                    fail++;
                currentState++;
            case deck_c:
                if (debug)
                    printf("deck %d, base: %d\n", test_a.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 2);
                assertInt(test_a.deckCount[thisPlayer], baseG.deckCount[thisPlayer] - 2);
                currentState++;
            case discard_c:
                if (debug) 
                    printf("DISCARD deck %d, base: %d\n", test_a.playedCardCount, baseG.playedCardCount);
                assertInt(test_a.playedCardCount, baseG.playedCardCount);
                currentState++;
            case hand_c: 
                if (debug)
                    printf("HAND deck %d, base: %d\n", test_a.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                assertInt(test_a.handCount[thisPlayer], baseG.handCount[thisPlayer] + 3);
                currentState++;
            case treasure_c:
                for(t = 0; t < test_a.handCount[thisPlayer]; t++){
                    currentCard = test_a.hand[thisPlayer][t]; 
                    if (currentCard == copper || currentCard == silver || currentCard == gold){
                        treasureCount++;
                    }     
                }
                for(n = 0; n < baseG.handCount[thisPlayer]; n++){
                    currentCard = baseG.hand[thisPlayer][n]; 
                    if (currentCard == copper || currentCard == silver || currentCard == gold){
                        base_t++;
                    }     
                }
                if (debug)
                    printf("treasure %d\n", treasureCount);
                assertIntNE(treasureCount, base_t);
                endTurn(&test_a);
                currentState = start;  
        } // end of for loop
    }
   
    printf("~~~~~~~~~~TEST COMPLETE~~~~~~~~~~~~~~~ \n");
    printf("Pass: %d, Fail: %d\n\n", pass, fail);
    return 0;
}
