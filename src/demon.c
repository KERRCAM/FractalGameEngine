// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/demon.h"

//-----------------------------------------------------------------------------------------------//

struct demon newDemon(int x, int y, int z, int width, int height, int colour, int type, int init){

    struct demon d;

    d.x = x;
    d.y = y;
    d.z = z;
    d.width = width;
    d.height = height;
    d.colour = colour;
    d.type = type;
    d.distance = 0;
    d.init = init;

    return d;

}

//-----------------------------------------------------------------------------------------------//
