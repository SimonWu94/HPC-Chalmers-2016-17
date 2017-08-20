CC=gcc -std=c99
CFLAGS = -I.
ASSEMBLY = -S 

.PHONY: all check clean

all: leak 

leak: leak.c
	$(CC) $(CFLAGS) leak.c -o leak.out

check:
	valgrind --tool=memcheck ./leak.out

clean: 
	-rm -f  *.o *.out *.s
	@echo Finished Cleaning!
