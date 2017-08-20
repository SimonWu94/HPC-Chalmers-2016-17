CC = gcc -std=c99
CFLAGS = -I.


.PHONY: all clean time

all: inlining seperate main


inlining: inlining.c
	$(CC) $(CFLAGS) inlining.c -o inlining.out


seperate: main_seperate.o seperate.o
	$(CC) $(CFLAGS) main_seperate.o seperate.o -o seperate.out

main_seperate.o : main_seperate.c seperate.h
	$(CC) $(CFLAGS) -c main_seperate.c
seperate.o : seperate.c
	$(CC) $(CFLAGS) -c seperate.c


main: main.c
	$(CC) $(CFLAGS) main.c -o main.out


time:
	time -p bash -c "for i in {1..100}; do ./inlining.out ; done "
	time -p bash -c "for i in {1..100}; do ./seperate.out ; done "
	time -p bash -c "for i in {1..100}; do ./main.out ; done "


clean:
	rm -rf *.out *.o 
	@echo Cleaning Finished
