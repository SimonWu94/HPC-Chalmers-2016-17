#include <stdio.h>

void mul_cpx( double * a_re, double * a_im, double * b_re, double * b_im, double * c_re, double * c_im){


*a_re = (*b_re) * (*c_re) - (*b_im) * (*c_im) ;
*a_im = (*b_re) * (*c_im) + (*b_im) * (*c_re) ;


};

int main(){


double *a_re;
double *a_im;
double * b_re;
double * b_im;
double *c_re;
double * c_im;

double a=1.;
double b=1.;
double c=1.;
double d=1.;
double e=1.;
double f=1.;


a_re=&a;
a_im=&b;
b_re=&c;
b_im=&d;
c_re=&e;
c_im=&f;

mul_cpx(a_re,a_im,b_re,b_im,c_re,c_im);

double cc =*a_re;
double ca =*a_im;

printf("Real part is: %G \n",cc);
printf("Imaginary part is: %G \n ", ca);

return 0;
