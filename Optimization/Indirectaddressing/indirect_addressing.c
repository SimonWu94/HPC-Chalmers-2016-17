#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(){


//------Variables-------
//size_t n = 1000000; too big for CLoud9....
size_t n =100000; 
size_t m = 1000; //We don't use m.

//----------------Vector generation---------------------
double x[n]; 
double y[n];
double norm=5.;  //normalization factor ( [0,a] interval )
double a= ((double)rand()/RAND_MAX) *norm;

for (int ix; ix < n; ++ix){
    x[ix] = ((double)rand()/RAND_MAX) *norm;
    y[ix] = ((double)rand()/RAND_MAX) *norm;
}

// --------------Vector Table Generation----------------
int p[n];
for (int ix=0; ix < n; ++ix){
    p[ix] = ix;
}


//-------------Time variables---------------------------
  clock_t start_indirect, end_indirect, start_direct, end_direct;
  double cpu_time_used_indirect;
  double cpu_time_used_direct;

int tn = 10000;
double time_indirect[tn],time_direct[tn];


//------------------Indirect Access---------------------

for (int ix=0; ix< tn; ix++){
// -----calculation------
start_indirect = clock();

for (int kx=0; kx < n; ++kx) {
  int jx = p[kx];
  y[jx] += a * x[jx];}

end_indirect = clock();


//----------------------Direct Access------------------- 

//------calculations--------

start_direct = clock();

for (int jx=0; jx < n; ++jx) {
  y[jx] += a * x[jx];
}
end_direct = clock();



//------------------------Timing-------------------------

time_indirect[ix] = ((double) (end_indirect- start_indirect)) / CLOCKS_PER_SEC;
time_direct[ix] = ((double) (end_direct- start_direct)) / CLOCKS_PER_SEC;

}


double sum1,sum2;
sum1=0.;
sum2=0.;
for (int ix=0; ix<tn; ix++){
  sum1 += time_indirect[ix];
  sum2 += time_direct[ix];
}
sum1=sum1/tn;
sum2=sum2/tn;

printf("Time used for Indirect Addressing %f \n", sum1);
printf("Time used for Direct Addressing %f \n", sum2);


return 0;
}

