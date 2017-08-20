CC = gcc
CFLAGS = -I.


.PHONY: all clean 

all: main seperate inlining

main: inlining.o seperate.o main.c
	$(CC) $(CFLAGS) inlining.o seperate.o main.c -o main.out

seperate: seperate.c
	$(CC) $(CFLAGS) seperate.c -o seperate.o

inlining: inlining.c
	$(CC) $(CFLAGS) inlining.c -o inlining.o

clean:
	rm -rf *.out *.o 
	@echo Cleaning Finished
