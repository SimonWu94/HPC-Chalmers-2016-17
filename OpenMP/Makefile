CC = gcc 
CFLAGS = -fopenmp -march=native -msse3
OPTIMISATION = -O3
DEB = -pg

.PHONY: all clean time debug test

all: cell_distances

cell_distances: cell_distances.c
	$(CC) $(CFLAGS) $(OPTIMISATION) cell_distances.c -o cell_distances 

debug: cell_distances.c
	$(CC) $(CFLAGS) $(DEB) $(OPTIMISATION) cell_distances.c -o cell_distances 
clean: 
	rm -f *.out cell_distances

delete:
	rm -f cell_distances.c
	vi cell_distances.c

test:
	time ./cell_distances -t5

assembly:
	$(CC) $(CFLAGS) $(OPTIMISATION) $(VEC) cell_distances.c -S cell_distances
