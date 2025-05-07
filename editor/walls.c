// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/walls.h"

//-----------------------------------------------------------------------------------------------//

struct wall newWall(int x1, int y1, int x2, int y2, int colour, int init){
    /*
    Wall struct constructor.
    */

    struct wall w;

    w.x1 = x1;
    w.y1 = y1;
    w.x2 = x2;
    w.y2 = y2;
    w.colour = colour;
    w.init = init;

    return w;

}

//-----------------------------------------------------------------------------------------------//
