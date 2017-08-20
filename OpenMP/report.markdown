# Assignment 3: OpenMP # 

In this assignment, we were asked to generate a distance frequency
table from a given set of point coordinates.

## Distance calculation ##
We use the euclidean distance to calculate the distance between two points.
We made use of intrinsics found at https://msdn.microsoft.com/en-us/library/708ya3be(v=vs.90).aspx .
In order to use the intrinsics, we added the headers:
```sh
#include <xmmintrin.h>
#include <pmmintrin.h>
```
We first load the coordinates (x, y, z, -) into  `__m128` variables. This allows
us to then calculate the components at the same time. The last entry - is useless. 
The pseudo code is as follows:

```sh
1. Load coordinates into __m128
2. Subtract the two __m128 variables
3. Square the difference
4. Then sum across the __m128 difference (Thanks to https://gist.github.com/zhongwen/4003356 )
5. Shift the decimal place by 100 so as to represent the distance as an index of an arrays
6. add 0.5f to get correct rounding
7. return a converted integer
```

## Read in ##

We read in the file by storing the whole file in a `buffer` variable. And then parsing the characters 
line by line through the relation:
```sh
A number = character - 48
```

## OpenMP ##
Since the distance (i,j) = (j,i), we only need to calculate numPts * (numPts-1)/2.
This gives us a nested loop. As per the tips given. We naively just use the directive 
```sh
#pragma omp for schedule(dynamic)
for(...){
    for(...){}
}
```
To distribute the calculation through the number of threads we have. This turned out pretty well.

## Memory usage ##
The maximum memory usage is when we have the buffer and the coordinates at the same time.
This is approximately:
```sh
Total memory = file size + pointer of pointer array of type float * 16Bytes
             = 90MB approximately
 
```
This is under the requirement set of 1GB.

## Time ##
The following are the tested times.
| Number of points  | 10e4  | 10e5  |  10e5 | 10e5  |
|---|---|---|---|---|
| Number of Threads  | 1  |  5 |  10 | 20  |
|  Tested runtime (s) | 0.357  | 7.117 | 3.177  |  1.988 |

Which are under the required times.
