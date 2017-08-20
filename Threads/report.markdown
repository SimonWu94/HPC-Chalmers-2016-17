# Assignment 2: Threads #

Threading is a very useful method to do many tasks in parallel. One creates so called threads which share certain computer resources, but are themselves independent processes. In the task of finding Newton basins and their corresponding convergence times (in terms of steps) one could efficiently make use of these threads, since each calculation is independent from another. However, threads could also access same variables by utilising mutexes.

## Newton's Method ##

From the Assignment description, we are able to find roots of functions efficiently by Newton's Method. The code below illustrates our implementation of this method for the function z^d-1:

We define a function of the type void *to pass into our pthread_create() function. 

```sh
void *newton ( void* threadarg ){

    1. Initialise thread arguments
    2. Initialise the starting guess values by using a mutex to know which row we are working on
    3. Run a while loop of the newton method until criteria is met as defined by Assignment
    4. Update the data arrays storing the attractor, convergent points as color 

}
```

## Thread Arguments ##

We defined a struct in order to store all the data we want to pass into the 
newton thread routine. The pseudo code is as follows:
```sh
struct thread_data{
    
    int  line_count; 
    char * attrData;
    char * convData;
    
};
```
The same was done for the output thread:

```sh
struct output_thread_data{
        
    int   line_count;
    int   degree;
    char* attrData;
    char* convData;
    
};
```
## Main function ##
In the main function we first allocate memory to store out color array using
macllo. Then we proceed to create the threads for calculating the data points.
This was done with the function:
```sh
pthread_create(address of thread address storage, NULL, pointer to function, 
thread arguments);
```

We then join the threads back with the function:
```sh 
pthread_join(address, NULL);
```
Lastly we output the color data as ppm files with the function `fwrite()`.

## Compiling ##
The newton.c file was compiled by issuing the command:
```sh
gcc -pthread -O2 -newton.c -o newton -lm
```
Where we linked the math library and used the `-O2` optimisation option.

## Timings ##
The following where the timings for the various requirements:

| Number of Threads | Number of Lines  | Degree d  | Time (s)  | 
| - |-| -  | - | 
|1 |1000 |1|0.0545|
| 1| 1000|2|0.121 |
| 1| 1000|5|0.502 |
| 1|1000 |7| 0.885|
| 1|1000 |5|0.502 |
| 2|1000 |5|0.277 |
| 3|1000 |5|0.194 |
| 4| 1000|5|0.158 |
| 10| 1000|7|0.122 |
| 10|50000 |7|208 |






