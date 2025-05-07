// LIBRARY IMPORTS
#include <stdio.h>

// LOCAL IMPORTS
#include "include/rotations.h"

//-----------------------------------------------------------------------------------------------//

struct rotation2D newRotation2D(float h, float v){
    /*
    Roation struct construction.
    */

    struct rotation2D r;

    r.h = h;
    r.v = v;

    return r;

}

//-----------------------------------------------------------------------------------------------//
