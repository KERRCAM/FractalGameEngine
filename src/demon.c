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
        d.height = 80;
        d.colour = 5;
        d.hp = 100;
        d.scale = 2;
        d.bounty = 200;
    } else if (type == 2){
        d.width = 35;
        d.height = 80;
        d.colour = 4;
        d.hp = 60;
        d.scale = 3;
        d.bounty = 120;
    }

    d.type = type;
    d.distance = 0;
    d.init = init;

    return d;

}

//-----------------------------------------------------------------------------------------------//
