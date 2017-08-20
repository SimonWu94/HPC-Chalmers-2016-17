# Timing
As required by the assignment, we started by writing a function that naively computes the sum of the first one billion integers. We wrote a `for` loop 
for this and incremented the integer by one at each step of the loop. We chose the type `unsigned long int` in order to avoid overflow.

In the Makefile, we included the targets `time` and `assembler` in order to generate the timings,
as well as the assembler code, for convenience. We compiled the `main.c` file with the optimisation options -O0 -O1 -O2 -O3 -Os -Og. The time target of the Makefile was done by invoking the bash command as follows, and running each executable
100 times to compensate for the fluctuation:

```sh
    time -p bash -c "for i in {1..100}; do ./main0.out ; done " 
```

By invoking the command:
```sh
make time
```
The following timings are obtained:


| Opimization  | Timing for 100 runs (s) |
| ------------- | ------------- |
|-O0    |   285.64      |
|-O1    |   38.52       |
|-O2    |   0.07        |
|-O3    |   0.06        |
|-Os    |   0.06        |
|-Og    |   38.53       |



By invoking the command:
```sh
make assembler
```
The assembly code is outputted.

Looking at the assembly output file for optimisation -O0, we see that the assembly code still compares the index with the number 1 billion.
The for loop is still being executed. This is reflected in the timing.

For the assembly output for -O1, we find out that an empty for loop is being executed from 0 to 1 billion. The answer is actually already predicted by the compiler and is just copied to the ouput.
Hence, this explains the faster time than -O0 but longer time than -O2 or -O3. 

For -O2, -O3 the assembly code is almost identical. The compiler skips the for loop and just ouputs the answer directly to stdout. The compiler recognised the triangle formula. 
This is reflected in the fast time.

For -Os, a similar optimisation was done apart from minor differences. 

For -Og, the optimisation is similar to -O1, where an empty for loop is run.

# Inlining
We wrote three programs. All of them perform the operation of multiplying two complex numbers.
We investigated the effect of placing the function inside, outside or inlined in the `main()`.

By invoking the command:
```sh
make time
```
The following timings are obtained:

| Inline Options | Timing for 100000 runs (s) |
| ------------- | ------------- |
| Function inlined by hand  |     287.74    |
| Function in seperate file  |     314.11    |
| Function In main() file  |    295.87     |

We see here that calling the function from a seperate file takes the longest, and inlining the computation inside the `main()` is the fastest. This seems logical, since inlining a function eliminated the function call overhead and saves time. 
Whereas calling the function from a seperate file hides optimisation possibilities from the compiler. 

# Locality

We have written in the file `locality.c` code to generate a 1000x1000 matrix 
of type `double` with the data stucture of row first order. The way we made our matrix was to define a pointer of pointers
called `matrix` allocating the appropriate space with `malloc()`:

```sh
double **matrix = (double **)malloc(sizeof(double *)*nrs)};

for(int ix=0; ix < ncs; ix++){
     matrix[ix] = (double *)malloc(sizeof(double)*ncs); }
```
     
Then we can proceed to initialise the matrix similar to the way we initialise a 2-dimensional array. 

We run the column sum and row sum naive implementations provided in the assignment.
Additionally we provide an improvement for the column sums. We define a pointer that
skips through the matrix at intervals of 1000 (the size of the rows). The code is
as follows:

```sh
void col_sums_improved(double * sums, const double ** matrix, size_t nrs, size_t ncs)
{ for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0.;
    double * ptr = &matrix[0][jx];
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += *ptr;
      ptr+=1000;
    sums[jx] = sum; }}
```

Invoking the command:
```sh
make time
```
we obtain the timing of the executables.

| Sum Option | -O0 |-O1 |-O2|-O3|-Os|-Og|none|
|-|-|-|-|-|-|-|-|
| Row Sum  |  33.135   | 10.787  |  10.900 | 10.838 | 11.856  |  11.589 | 32.685 |
| Column Sum |  74.239     |  37.479 |    37.825  | 37.676 | 40.258  |  39.528|57.413 |
| Improved Column Sum | 32.730     |  10.613 | 10.490 | 5.239  |  11.178 | 10.9  |  32.427 |

We can see that the fastest is the improved column sum. This is due to the fact that we directly access the matrix with arrays.
Column sum calculations take longer than the row sum calculations when using the same algorithm is explained by the fact that we construct the matrix in row first order.
Hence, naturally the naive implementation is faster with row sums. 



# Indirect Addressing

##### Timing of 10000 runs (s)

| Addressing Option | -O0 |-O1 |-O2|-O3|-Os|-Og|none|
|-|-|-|-|-|-|-|-|
| Indirect  |  43.3   |  12.8 |  11.1 | 11.0  | 14.9  |  13.6 | 42.9 | 
| Direct  |     31.9  |  10.3 | 8.6  | 7.3  |  10.6 | 10.9  |  31.7 |

We see that in all cases, direct addressing is faster than indirect ones. This comes naturally, since indirect addressing requires one more step. 

# Valgrind 

We run the command
```sh
valgrind --tool=memcheck ./leak.out
```
through the Makefile with the target "check". Running the commands below:
```sh
make
make check
```
We obtain the Valgrind output:
```sh
==51889== HEAP SUMMARY:
==51889==     in use at exit: 4,000 bytes in 1 blocks
==51889==   total heap usage: 2 allocs, 1 frees, 5,024 bytes allocated
==51889==
==51889== LEAK SUMMARY:
==51889==    definitely lost: 4,000 bytes in 1 blocks
==51889==    indirectly lost: 0 bytes in 0 blocks
==51889==      possibly lost: 0 bytes in 0 blocks
==51889==    still reachable: 0 bytes in 0 blocks
==51889==         suppressed: 0 bytes in 0 blocks
==51889== Rerun with --leak-check=full to see details of leaked memory
==51889==
==51889== For counts of detected and suppressed errors, rerun with: -v
==51889== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
We see clearly that we definitely lost out 1000 int array. This is due to the fact that `main()` finished but the pointer was still alive at time of termination.
Better coding style would require us to free the unused memory.

# Profiling

## gprof 
We obtain the gprof generated profile after running the executable
```sh
gprof -b main.c gmon.out
```

```sh
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total
 time   seconds   seconds    calls  ms/call  ms/call  name
 33.46      0.01     0.01        1    10.04    10.04  col_sums
 33.46      0.02     0.01        1    10.04    10.04  col_sums_improved
 33.46      0.03     0.01        1    10.04    10.04  row_sums


                        Call graph


granularity: each sample hit covers 2 byte(s) for 33.21% of 0.03 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    0.03                 main [1]
                0.01    0.00       1/1           row_sums [4]
                0.01    0.00       1/1           col_sums [2]
                0.01    0.00       1/1           col_sums_improved [3]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[2]     33.3    0.01    0.00       1         col_sums [2]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[3]     33.3    0.01    0.00       1         col_sums_improved [3]
-----------------------------------------------
                0.01    0.00       1/1           main [1]
[4]     33.3    0.01    0.00       1         row_sums [4]
-----------------------------------------------


Index by function name

   [2] col_sums                [3] col_sums_improved       [4] row_sums
   ```
   
From the ouput, we see that the program spends equal amounts of time to call the functions. We see that we call all three functions the same amount of time. 
This makes sense. 

## gcov

By compiling main.c with the appropriate options. We can generate a main.c.gcov file that dispays information about our program. 
Comparing with bash timings, we see that there is no timing. Only steps. This might be biased, if some steps take longer than others.
The parts that are most frequently run are the for loops. 
 
 
 