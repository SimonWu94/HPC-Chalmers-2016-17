//******************* INCLUDES ******************
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

//******************* MACROS ******************
#define INFTY 1000000

//******************* FUNCTION DECLARATIONS ******************

inline void getWeights(const char filename[100], 
					int* weights);

inline void getGraphData(const char filename[100],
					int* degree,
					int* numVertex);

inline int gloToLoc(const int global, const int begin);

inline int locToglo(const int local,  const int begin);

inline bool isInProcess(const int index,
					const int here, const int there);

inline int gloToWeightsIndx(const int global, const int degree);


//******************* MAIN FUNCTION ******************

int main (int argc, char* argv[]){
	
// OpenMPI 	
	MPI_Init(&argc, &argv);
	int world_rank;
	int world_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);


// Parse Command Line
	if (argc != 4){
		fprintf(stderr, "command line accepts 3 arguments\n");
   		exit(1);
	}

	int start = atoi(argv[1]);
	int end   = atoi(argv[2]);
	char filename[100];
	strcpy(filename, argv[3]);

// Get Graph Data
	int degree    = 1;
	int numVertex = 1;
	getGraphData(filename, &degree, &numVertex);

// Work received for each process
	int sizeOfProc  = numVertex/world_size;
	int startVertex = sizeOfProc * world_rank;
	int endVertex   = sizeOfProc * (world_rank+1);

// Load Graph
	int* weights = (int*) malloc(2*numVertex*degree*sizeof(int));
	if(world_rank == 0){
		getWeights(filename, weights);
	}

	MPI_Bcast(weights, 2*numVertex*degree, MPI_INT, 0, MPI_COMM_WORLD);
	
//

	int* alreadyVisisted   = (int*) malloc(sizeOfProc*sizeof(int));
	int* distToSource = (int*) malloc(sizeOfProc*sizeof(int));
	int* prev = (int *) malloc(sizeOfProc*sizeof(int));

//  Initialise 
//  aleadyVisisted to {0, 0, 0, 0,...}
//  distToSource to {INFINTY, INFINTY, ...}
	for(int i=0 ; i<sizeOfProc ; i++){
		alreadyVisisted[i] = 0;
		distToSource[i]= INFTY;
		prev[i] = -1;
	}

	int numUnvisited = sizeOfProc;

	if( isInProcess(start, startVertex, endVertex) ){
		distToSource[gloToLoc(start,startVertex)]    = 0;
	}

	int procMin;
	int procMinIndx;
	
	int* procData = (int*) malloc(2 * sizeof(int));
	int* allData  = (int*) malloc(2 * sizeof(int));

	while(numUnvisited !=0){

	procMin = INFTY;
	procMinIndx = -1;
// Find minimum in process
		for(int i = 0 ; i < sizeOfProc ; i++){
			if(alreadyVisisted[i] == 0 && distToSource[i]<procMin){
				procMin = distToSource[i];
				procMinIndx = locToglo(i,startVertex);
			}
		}

	

	procData[0] = procMin;
	procData[1] = procMinIndx;

// Find global Minima of all process minimums
	MPI_Allreduce(procData, allData, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);	

	procMin = allData[0];
	procMinIndx = allData[1];
	
	if(procMinIndx == end ){break;}
	if (isInProcess(procMinIndx, startVertex, endVertex)){
		distToSource[gloToLoc(procMinIndx,startVertex)] = procMin;
		alreadyVisisted[gloToLoc(procMinIndx,startVertex)] = 1;
		numUnvisited--;
	}
	
	int* neighbours = &weights[gloToWeightsIndx(procMinIndx,degree)];

	for (int i = 0 ; i < degree ; i++){
		int neighbour = *neighbours;
		
		if(isInProcess(neighbour, startVertex, endVertex)){
			int localIndx = gloToLoc(neighbour,startVertex);
			int addition  = *(neighbours+1);
			if( !alreadyVisisted[localIndx] && distToSource[localIndx] > procMin + addition ){
				distToSource[localIndx] = procMin + addition;
				prev[localIndx] = procMinIndx;
			}
		}
		neighbours += 2;
	}
	}

// Copy back all data from processes to master process
	int* allPrevious     = (int*) malloc(numVertex * sizeof(int));
	int* allDistToSource = (int*) malloc(numVertex * sizeof(int));
	MPI_Gather(prev, sizeOfProc, MPI_INT, allPrevious, sizeOfProc, MPI_INT,  0, MPI_COMM_WORLD);
	MPI_Gather(distToSource, sizeOfProc, MPI_INT, allDistToSource, sizeOfProc, MPI_INT, 0, MPI_COMM_WORLD);

	if(world_rank == 0 ){
		
		int list[3000];
		int count = 0 ;
		list[0] = end;
		int current = end;
		while(current != start){
			count++;
			list[count] = allPrevious[current];
			current  = allPrevious[current]; 
if(current == -1){break;}
		}
		printf("Shortest path of length %i:\n", allDistToSource[end]);
		while(count != 0){
			printf("%i -> ", list[count]);
			count--;
		}
		
		printf("%i \n", end);
}
	free(weights);
	free(alreadyVisisted);
	free(distToSource);
	free(prev);
	free(procData);
	free(allData);
	free(allPrevious);
	free(allDistToSource);

	MPI_Finalize();
	return 0;
}



//******************* FUNCTION DEFINITIONS ******************

void getWeights(const char filename[100], 
				int* weights){

	FILE *fp;
	fp = fopen(filename, "r");
	int begin, end, cost;
	while (fscanf(fp, "%d %d %d\n", &begin, &end , &cost) == 3) {
    	*weights = end;
    	weights++;
    	*weights = cost;
    	weights++;

    }
    fclose(fp);
}

void getGraphData(const char filename[100],
					int* degree,
					int* numNodes){

	for (int i=0; i<atoi(&filename[41]); ++i) {
        *degree *= 10;
    }
    for (int i=0; i<atoi(&filename[45]); ++i) {
        *numNodes *= 10;
    }

}

int gloToLoc(const int global, const int begin){
	return global-begin;
}

int locToglo(const int local,  const int begin){
	return local+begin;
}

bool isInProcess(const int index,
					const int here, const int there){
	return (here<=index && index< there) ;
}

int gloToWeightsIndx(const int global, const int degree){
	return global * 2 * degree;
}





