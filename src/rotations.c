// also contain quaternions as part of operations for rotations
// quaternions describe a roation but are seperate to how to show a roation of a certain object

// LIBRARY IMPORTS
#include <stdio.h>

// LOCAL IMPORTS
#include "include/rotations.h"

//-----------------------------------------------------------------------------------------------//

struct rotation2D newRotation2D(float h, float v){

    struct rotation2D r;

    r.h = h;
    r.v = v;

    return r;

}

