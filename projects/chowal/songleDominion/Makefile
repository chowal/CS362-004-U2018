CFLAGS = -g -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer: randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)	
	
randomtestcard1: randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)	

defaults: getFirstGame.c
	gcc -o getFirst getFirstGame.c dominion.o rngs.o $(CFLAGS)	

cardtest1: cardtest1.c
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)	
	
cardtest2: cardtest2.c
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)	
	
cardtest4: cardtest4.c
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)	

# playCard
unittest1: unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)	

#updateCoins
unittest2: unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)	

#isGameOver
unittest3: unittest3.c
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)	

#gameWinner
unittest4: unittest4.c
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)	

testcard: cardtest1 cardtest2 cardtest3 cardtest4
	./cardtest1 &> cardtest.out
	gcov dominion.c -b >> cardtest.out
	cat dominion.c.gcov >> cardtest.out
	./cardtest2 >> cardtest.out
	gcov dominion.c -b >> cardtest.out
	cat dominion.c.gcov >> cardtest.out
	./cardtest3 >> cardtest.out
	gcov dominion.c -b >> cardtest.out
	cat dominion.c.gcov >> cardtest.out
	./cardtest4 >> cardtest.out
	gcov dominion.c -b >> cardtest.out
	cat dominion.c.gcov >> cardtest.out

testunit: unittest1 unittest2 unittest3 unittest4
	./unittest1 &> unittest.out
	gcov dominion.c -b >> unittest.out
	cat dominion.c.gcov >> unittest.out
	./unittest2 >> unittest.out
	gcov dominion.c -b >> unittest.out
	cat dominion.c.gcov >> unittest.out
	./unittest3 >> unittest.out
	gcov dominion.c -b >> unittest.out
	cat dominion.c.gcov >> unittest.out
	./unittest4 >> unittest.out
	gcov dominion.c -b >> unittest.out
	cat dominion.c.gcov >> unittest.out

testrandom: randomtestadventurer randomtestcard1 randomtestcard2 
	./randomtestadventurer &> randomtest.out
	gcov dominion.c -b >> randomtest.out
	cat dominion.c.gcov >> randomtest.out
	./randomtestcard1 >> randomtest.out
	gcov dominion.c -b >> randomtest.out
	cat dominion.c.gcov >> randomtest.out
	./randomtestcard2 >> randomtest.out
	gcov dominion.c -b >> randomtest.out
	cat dominion.c.gcov >> randomtest.out

allTests: testcard testunit testrandom

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestadventurer randomtestcard1 randomtestcard2
