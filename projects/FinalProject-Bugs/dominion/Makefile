CFLAGS= -Wall -fpic -fprofile-arcs -ftest-coverage -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest: unittest1.c unittest3.c unittest2.c unittest4.c unittest5.c unittest6.c unittest7.c unittest8.c unittest9.c unittest10.c unittest11.c dominion.o interface.o
	echo "unittest1.c:" >> unittestresult.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest2.c:" >> unittestresult.out
	gcc -o unittest2 dominion.c rngs.c interface.c unittest2.c $(CFLAGS)
	unittest2 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest3.c:" >> unittestresult.out
	gcc -o unittest3 dominion.c rngs.c interface.c unittest3.c $(CFLAGS)
	unittest3 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest4.c:" >> unittestresult.out
	gcc -o unittest4 dominion.c rngs.c interface.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest5.c:" >> unittestresult.out
	gcc -o unittest5 dominion.c rngs.c unittest5.c $(CFLAGS)
	unittest5 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest6.c:" >> unittestresult.out
	gcc -o unittest6 dominion.c rngs.c unittest6.c $(CFLAGS)
	unittest6 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest7.c:" >> unittestresult.out
	gcc -o unittest7 dominion.c rngs.c unittest7.c $(CFLAGS)
	unittest7 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 
	
	echo "unittest8.c:" >> unittestresult.out
	gcc -o unittest8 dominion.c rngs.c unittest8.c $(CFLAGS)
	unittest8 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest9.c:" >> unittestresult.out
	gcc -o unittest9 dominion.c rngs.c interface.c unittest9.c $(CFLAGS)
	unittest9 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest10.c:" >> unittestresult.out
	gcc -o unittest10 dominion.c rngs.c unittest10.c $(CFLAGS)
	unittest10 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

	echo "unittest11.c:" >> unittestresult.out
	gcc -o unittest11 dominion.c rngs.c unittest11.c $(CFLAGS)
	unittest11 >> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out 

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10 unittest11 

