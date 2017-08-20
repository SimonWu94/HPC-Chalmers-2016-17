#include <stdio.h>
#include<stdlib.h>

void row_sums(double (*sums)[1000], const double (**matrix)[1000][1000], size_t nrs, size_t ncs)
{
  for ( size_t ix=0; ix < nrs; ++ix ) {
    double sum = 0;
    for ( size_t jx=0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}


int main(){

double mat[1000][1000];

for (int i=0; i<1000;i++){
	for (int j=0; j<1000; j++)
		mat[i][j] = i+1.;
}

//double M[1000][1000] = mat;
double sums[1000];

row_sums(sums,mat,1000,1000);
for (int k=0; k<1000;k++)
	printf("The sum of rows gives :","%lf",sums[k]);

return 0;
}
