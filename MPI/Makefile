CC =mpicc -std=c11
CFLAGS = -O2 -march=native
DEBUGGER = -Wall
.PHONY: all time clean test tests
EXE = dijkstra

all: $(EXE)

dijkstra: dijkstra.c
	$(CC) $(CFLAGS) $(DEBUGGER) dijkstra.c -o dijkstra
clean: 
	rm -f $(EXE)
	@echo "finished cleaning"

time:
	python3 ./timer.py dijkstra	

tests:
	ln -sf /home/hpc01/a5_grading/test_data/
	@echo "Answer"
	mpirun -n 1 /home/hpc01/a5_grading/example/dijkstra 9 82  test_data/graph_de1_ne3_we2
	@echo "Our answer"
	mpirun -n 1 dijkstra 9 82 /home/hpc01/a5_grading/test_data/graph_de1_ne3_we2
	@echo "Answer"
	mpirun -n 1 /home/hpc01/a5_grading/example/dijkstra 17 40 test_data/graph_de2_ne4_we2
	@echo "Our answer"
	mpirun -n 1 dijkstra 17 40 /home/hpc01/a5_grading/test_data/graph_de2_ne4_we2
	@echo "Answer"
	mpirun -n 4 /home/hpc01/a5_grading/example/dijkstra 17 18 test_data/graph_de2_ne4_we2
	@echo "Our answer"
	mpirun -n 4 dijkstra 17 18 /home/hpc01/a5_grading/test_data/graph_de2_ne4_we2
	@echo "Answer"
	mpirun -n 10 /home/hpc01/a5_grading/example/dijkstra 107 0 test_data/graph_de2_ne5_we2
	@echo "Our answer"
	mpirun -n 10 dijkstra 107 0 /home/hpc01/a5_grading/test_data/graph_de2_ne5_we2
	@echo "Answer"
	mpirun -n 20 /home/hpc01/a5_grading/example/dijkstra 4 5 test_data/graph_de3_ne5_we3
	@echo "Our answer"
	mpirun -n 20 dijkstra 4 5 /home/hpc01/a5_grading/test_data/graph_de3_ne5_we3
test:
	mpirun -n 10 dijkstra 17 18 /home/hpc01/a5_grading/test_data/graph_de2_ne4_we2
