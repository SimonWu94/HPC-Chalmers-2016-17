CC=gcc -std=c99 
GPROF = -I. -pg
GCOV = -I. -ftest-coverage -fprofile-arcs
ASSEMBLY = -S 

.PHONY: all clean gprof gcov

all: gprof gcov

gprof: main.c 
	$(CC) $(GPROF) main.c -o main_gprof.out
	
gcov: main.c
	$(CC) $(GCOV) main.c -o main_gcov.out

clean:
	-rm -f  *.o *.out *.s
	@echo Finished Cleaning!