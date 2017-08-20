# Assignment 4: OpenCL #

OpenCL allows us to do heterogeneous computations on CPUs, GPUs or even FPGAs. It involves a host that builds up the program, and other connected devices to share the computations. OpenCL allows us to leverage the large amounts of parallel workers a GPU has to do parallel computations, such as heat diffusion equations as discussed in this homework.  

## Heat Equation ##
Following from the discretized heat equation, we update the point `h(i,j)` with:
`h(i,j) + c * ( (h(i-1,j) + h(i+1,j) + h(i,j-1) + h(i,j+1))/4 - h(i,j) )`
at each time step. We can see from the equations that at each time step, the calculation for each `h(i,j)` is independent of one another. This allows us to distribute each calculation to on worker on a given GPU. 

## Pseudo Code ##
The pseudo code of `heat_diffusion.c` is as follows:
```sh
1. initialise variables for OpenCL (platform, devices, kernel read ins).
2. Build two heat matrices as 2 one dimensional arrays. The middle is initialised as given.
3. Read the heat matrices into the GPU memory.
4. Enqueue the calculations using offsets {1,1} as well as swapping two heat matrices alternatively.
5. Read the heat matrix from GPU to CPU.
6. Calculate the average and absolute average on CPU.
```
The pseudo code of `kernels.cl` is as follows:
```sh
1. Function overhead with __global heat matrix1, __global heat matrix2, diffusion constant and width
2. code that calculates `h(i,j) + c * ( (h(i-1,j) + h(i+1,j) + h(i,j-1) + h(i,j+1))/4 - h(i,j) )`
```

## Tricks ##
Optimisation tricks used:
1. Swapping of heat matrices so that the function just reads in two different cl_mem pointers.
2. omitted if statements in kernel. We used offsets to increase speed during enqueueing. 
3. We changed the size of the system during calculation if the heat doesn't spread completely to the whole body.

## Compiling ##
The script `heat_diffusion.c` was compiled with the following command:
```sh
gcc -O2 -march=native heat_diffusion.c -I/usr/local/cuda-7.5/targets/x86_64-linux/include -L/usr/local/cuda-7.5/targets/x86_64-linux/lib -lOpenCL -lm -o heat_diffusion
```

## Timings ##
The following were the timings for the various requirements using a pyhton script similar to the test script:

| width | height | init value | diff constant | nIterations |Repetitions| Time (s)  | Required Time (s)  | 
| - |-| -  | - | - | - |  - | -|
|100|100|1e20|0.01|100000|10 |1.573|7.26|
|10000|10000|1e10|0.2|1000|10|28.208|100|
|100000|100|1e10|0.6|200|50|0.577|7.0|

The low times compared to the requirements can be explained due to the fact that the startup time for the nvidia drivers have probably changed due to the upgrade. However, since we have performed similarly as the example script. We assume we have met the requirements nonetheless. 

