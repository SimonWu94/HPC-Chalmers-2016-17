#include <stdio.h>
#include <stdlib.h>

int* allocate(){
    
    int * lazy_array = (int *)malloc(sizeof(int)*1000);
    return lazy_array;
}



int main() {

unsigned long int a;
a= 0;

allocate();
for (unsigned long int i=0; i<= 1000000000 ; i++){
a += i;}

printf("The sum of the first 1 billion integers is: %lu \n", a);

return 0;
}
