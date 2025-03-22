#include <stdio.h>
#include <math.h>


int main(){

    int x = 99;
    float a = x / 25.0;
    float b = round(a);
    int nx = b * 25;

    printf("x = %d\n", nx);

    return 0;

}