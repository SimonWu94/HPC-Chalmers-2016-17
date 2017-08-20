#include<stdio.h>

void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs)
{
  for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

int main(){

double mat[1000][1000];

for (int i=0; i<1000;i++){
        for (int j=0; j<1000; j++)
                mat[i][j] = i+1.;
}

double sum[1000];

col_sums(&sum,&mat,1000,1000);
for (int k=0; k<1000;k++)
        printf("The sum of columns gives :","%lf",sum[k])

return 0;
}

