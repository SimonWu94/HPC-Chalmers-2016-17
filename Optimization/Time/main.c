#include <stdio.h>

int main() {

unsigned long int a;
a= 0;

for (unsigned long int i=0; i<= 1000000000 ; i++){
a += i;}

printf("The sum of the first 1 billion integers is: %lu \n", a);

return 0;
}
