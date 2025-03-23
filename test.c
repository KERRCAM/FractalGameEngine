#include <stdio.h>
#include <math.h>


struct sector {
    int x, y;
    int w[32];
};


int main(){

    struct sector s = {3, 6, {}};

    s.x = 7;
    s.w[0] = 3;
    s.w[100] = 6;

    printf("%d\n", s.w[0]);
    printf("%d\n", s.w[100]);


    return 0;
}