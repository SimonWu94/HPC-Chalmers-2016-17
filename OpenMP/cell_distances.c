#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <malloc.h>
#include <unistd.h>

#ifndef LINESIZE
#define LINESIZE 24
#endif

/*******************************************************************************
                DISTANCE FUNCTION
 ******************************************************************************/
//Function declaration
int distance(const float* , const float* , const __m128* );

//Euclidean Distance calculation 
int distance(const float* restrict apple , const float* restrict banana , const __m128* restrict decimalShifter ) {
    const __m128 R1  = _mm_loadu_ps(apple);
    const __m128 R2  = _mm_loadu_ps(banana);
    const __m128 rounder = _mm_set1_ps(0.5f);
    __m128 tmp = _mm_sub_ps(R1,R2);
    tmp = _mm_mul_ps(tmp, tmp);
    tmp = _mm_hadd_ps(tmp, tmp);
    tmp = _mm_hadd_ps(tmp, tmp);
    tmp = _mm_sqrt_ss(tmp);
    tmp = _mm_mul_ps(*decimalShifter, tmp);
    return _mm_cvttss_si32(_mm_add_ps(tmp,rounder));
}

/*******************************************************************************
                MAIN FUNCTION
 ******************************************************************************/
int main( int argc, char ** argv ) {
    
//Define number of threads
    int nThreads;

    if (sscanf(argv[1], "-t%d", &nThreads) == EOF ){
        fprintf(stderr, "Please format input as -t[thread n umber]\n");
        exit(EOF);
    }
    
//Determine number of coordinates
    struct stat st;
    stat("cells", &st);
    const long int fileSize = st.st_size;
    const long int numPts = fileSize/LINESIZE; 
    
//Data storage allocation
    char* buffer = (char*) malloc (fileSize);
    
//Read file into allocated memory
    FILE * fp;
    fp = fopen("cells","r");
    int result;
    result = fread(buffer, 1, fileSize, fp);
    if(result!=fileSize) {printf("Error occured during read-in");}
    fclose (fp);
    

//Allocate float pointers of pointers coordinate storage space 
    float** coord = (float**) malloc(numPts*sizeof(float*));

//Parse coordinates to numbers
    long int idx;
    float absoluteX, absoluteY, absoluteZ;
    int signX, signY, signZ;
    char * ptrbuffer = buffer;
    for (idx= 0; idx<numPts ; idx ++){
        
        coord[idx] = (float*) malloc(4*sizeof(float));
        
        absoluteX   = 10.*ptrbuffer[1]+ 1.*ptrbuffer[2]
	                      + 0.1*ptrbuffer[4]+ 0.01*ptrbuffer[5]
	                      + 0.001*ptrbuffer[6] - 533.328;
        signX       = 44 - ptrbuffer[0];
        absoluteY   = 10.*ptrbuffer[9]+ 1.*ptrbuffer[10]
	                      + 0.1*ptrbuffer[12]+ 0.01*ptrbuffer[13]
	                      + 0.001*ptrbuffer[14] - 533.328;
        signY       = 44 - ptrbuffer[8];
        absoluteZ   = 10.*ptrbuffer[17]+ 1.*ptrbuffer[18]
	                      + 0.1*ptrbuffer[20]+ 0.01*ptrbuffer[21]
	                      + 0.001*ptrbuffer[22] - 533.328;
        signZ       = 44 - ptrbuffer[16];
        
        coord[idx][0]    = absoluteX*signX;
        coord[idx][1]    = absoluteY*signY;
        coord[idx][2]    = absoluteZ*signZ;
        coord[idx][3]    = 0;
        ptrbuffer += LINESIZE;
    }
    
    free(buffer);

//The furthest distance we can have is  20*sqrt(3) = 34.64
//So we only have to define 3465*nThreads counter

    int** nCounter=(int**) malloc(nThreads* sizeof(int*));
   
    for (int index =0; index < nThreads ; index++){
        nCounter[index] = (int*) calloc(3466, sizeof(int));
        }
        
        
    omp_set_num_threads(nThreads);
    const __m128 decshifter = _mm_set1_ps(100.0f);
    
#pragma omp parallel for schedule(dynamic)
    for(int i=0 ; i< numPts ; i++){
        for(int j=i+1 ; j<numPts ; j++){
            ++nCounter[omp_get_thread_num()][distance(coord[i], coord[j], &decshifter)]; 
        }
    } 

    //Output
    if(nThreads >1){
#pragma omp parallel for schedule(static)  
    for(int i= 0 ; i <3466 ; i++){
        for(int j=1; j< nThreads; j++){
            nCounter[0][i] += nCounter[j][i];
            }
        }
 
}    
    for(int i=0 ; i<3466; i++){
	if (nCounter[0][i]!=0) { printf("%02d.%02d %d\n",i/100,i%100, nCounter[0][i]);}
	}
        

    
    return 0;
}
