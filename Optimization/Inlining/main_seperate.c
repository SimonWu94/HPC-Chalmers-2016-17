#include<stdio.h>
#include<stdlib.h>
#include<seperate.h>

//This should not be here?
//void mul_cpx_ext( double *a_re, double * a_im, double * b_re, double * b_im, double * c_re, double * c_im);

int main(){


double a_re[30000];
double a_im[30000];
double b_re[30000];
double b_im[30000];
double c_re[30000];
double c_im[30000];



double a =5.;
for (int i=0; i<30000;i++){
b_re[i]=((float)rand()/(float)(RAND_MAX))*a; 
b_im[i]=((float)rand()/(float)(RAND_MAX))*a;
c_re[i]=((float)rand()/(float)(RAND_MAX))*a;
c_im[i]=((float)rand()/(float)(RAND_MAX))*a;
a_re[i]=0.;
a_im[i]=0.;
};

for (int k=0; k<30000;k++){
mul_cpx_ext(&a_re[k],&a_im[k],&b_re[k],&b_im[k],&c_re[k],&c_im[k]);
/*printf("Real part is: %G \n",a_re[k]);
printf("Imaginary part is: %G \n ", a_im[k]);
*/};

return 0;}

