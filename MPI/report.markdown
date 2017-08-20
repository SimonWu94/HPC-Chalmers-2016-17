# Assignment 5: MPI #

Message Passing Interface is a very useful method for High Performance Computing. The main idea behind is that each parallelised job is a process (as opposed to threads we had done before). To communicate with each process, MPI is used, with methods such as `MPI_Bcast` etc. This allows us to easily increase the number of processes for example by adding one more node to the existing cluster. 

## Dijkstra's Algorithm ##

Dijkstra's Algorithm is used to find the shorted distance between nodes of a graph (with positive weights). The graph can represent traffic roads, internet routers, and many more. The unparallised version, which could be found on wikipedia is as follows:
```
 1  function Dijkstra(Graph, source):
 2
 3      create vertex set Q
 4
 5      for each vertex v in Graph:             // Initialization
 6          dist[v] ← INFINITY                  // Unknown distance from source to v
 7          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
 8          add v to Q                          // All nodes initially in Q (unvisited nodes)
 9
10      dist[source] ← 0                        // Distance from source to source
11      
12      while Q is not empty:
13          u ← vertex in Q with min dist[u]    // Node with the least distance will be selected first
14          remove u from Q 
15          
16          for each neighbor v of u:           // where v is still in Q.
17              alt ← dist[u] + length(u, v)
18              if alt < dist[v]:               // A shorter path to v has been found
19                  dist[v] ← alt 
20                  prev[v] ← u 
21
22      return dist[], prev[]
```
Ref: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

The place where MPI comes in handy is from 12-22. We find the minumum is each process for dist[u]. Then use MPI to compare all the minimas using the method `MPI_Allreduce(procData, allData, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);` which returns the index of the global minimum. Then we proceed to update all the neighbours of this minima. The global minimum will be marked as visited and the algorithm repeated until all nodes have been visited or our target node has been found. Once a node is visited, we will not visit it again.

## Pseudo Code ##
The pseudo code of `dijkstra.c` is as follows:
```sh
1. initialise the MPI environment
2. master process reads-in the graph, inialises the weights, Bcast to all
3. each process executes the parallised dijkstra version starting with the starting node
4. all the distances are gatheres using `MPI_Gather`
5. the distance and the path is printed following the array allPrevious[].
```

## Compiling ##
The script `dijkstra.c` was compiled with the following command:
```sh
mpicc -O2 -march=native dijkstra.c -o dijkstra
```

# Makefile commands#
The makefile includes the commands:
make: builds the executable dijkstra
tests: tests the results of the path against the example program
test: runs on test
time: calls the timer.py script to get average execution time
clean: cleans everything
## Timings ##
The following where the timings for the various requirements using a pyhton script similar to the test script:

| Nodes | Vertices | Degree |Start | End |Repetitions| Time (s)  | Required Time (s)  | 
| - |-| -  | - | - | - |  - | -|
|1|1000|100|9|82|50 |0.109|0.26|
|1|10000|100|17|40|10|0.481|9.92|
|4|10000|100|17|18|10|0.437|2.64|
|10|100000|100|107|0|10|5.911|97|
|20|100000|1000|4|5|10|37.62|472|

We attribute the low times especially for the larger graphs to the fact that our algorithm terminates once the target node has been visited. Hence the times could vary between different target nodes.
