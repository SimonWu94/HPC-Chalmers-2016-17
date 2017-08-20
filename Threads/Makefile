CC = gcc -std=c99
CFLAGS = -pthread
MATHLIB = -lm
DEBUG = -g -lm

.PHONY: all clean time report debug

newton: newton.c
	$(CC) $(CFLAGS) -O3 newton.c -o newton $(MATHLIB)

debug: newton.c
	$(CC) $(CFLAGS) newton.c $(DEBUG)

time:
	time -p bash -c "for i in {1..100}; do ./newton -t1 -l1000 1 ; done " 
	time -p bash -c "for i in {1..100}; do ./newton -t1 -l1000 2 ; done " 
	time ./newton -t1 -l1000 5
	time ./newton -t1 -l1000 7
	time ./newton -t1 -l1000 5
	time ./newton -t2 -l1000 5
	time ./newton -t3 -l1000 5
	time ./newton -t4 -l1000 5
	time ./newton -t10 -l1000 7
	time ./newton -t10 -l50000 7
	

clean:
	rm -f *.o newton
	@echo Cleaning Finished
	

