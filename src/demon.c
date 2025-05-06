// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/demon.h"

//-----------------------------------------------------------------------------------------------//

struct demon newDemon(int x, int y, int z, int type, int init){

    struct demon d;

    d.x = x;
    d.y = y;
    d.z = z;

    if (type == 1){
        d.width = 50;
        d.height = 50;
        d.colour = 9;
        d.hp = 100;
    } else if (type == 2){
        d.width = 35;
        d.height = 35;
        d.colour = 6;
        d.hp = 60;
    }

    d.type = type;
    d.distance = 0;
    d.init = init;

    return d;

}

//-----------------------------------------------------------------------------------------------//
