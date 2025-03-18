// LIBRARY IMPORTS
#include <stdio.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/vectors.h"

//-----------------------------------------------------------------------------------------------//

struct vector2D newVector2D(float x, float y){

    struct vector2D v;

    v.x = x;
    v.y = y;

    return v;

}

//-----------------------------------------------------------------------------------------------//

struct vector3D newVector3D(float x, float y, float z){

    struct vector3D v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;

}

//-----------------------------------------------------------------------------------------------//

float manhattanLength2D(struct vector2D v){

    return v.x + v.y;

}

//-----------------------------------------------------------------------------------------------//

float manhattanLength3D(struct vector3D v){

    return v.x + v.y + v.z;

}

//-----------------------------------------------------------------------------------------------//

float manhattanDistance2D(struct vector2D v1, struct vector2D v2){

    return (v2.x - v1.x) + (v2.y - v1.y);

}

//-----------------------------------------------------------------------------------------------//

float manhattanDistance3D(struct vector3D v1, struct vector3D v2){

    return (v2.x - v1.x) + (v2.y - v1.y) + (v2.z - v1.z);

}

//-----------------------------------------------------------------------------------------------//

float euclidianLength2D(struct vector2D v){

    return sqrt(pow(v.x, 2) + pow(v.y, 2));

}

//-----------------------------------------------------------------------------------------------//

float euclidianLength3D(struct vector3D v){

    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));

}

//-----------------------------------------------------------------------------------------------//

float euclidianDistance2D(struct vector2D v1, struct vector2D v2){

    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));

}

//-----------------------------------------------------------------------------------------------//

float euclidianDistance3D(struct vector3D v1, struct vector3D v2){

    return sqrt(pow(v2.x - v2.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));

}

//-----------------------------------------------------------------------------------------------//

float dotProduct2D(struct vector2D v1, struct vector2D v2){

    return (v1.x * v2.x) + (v1.y * v2.y);

}

//-----------------------------------------------------------------------------------------------//

float dotProduct3D(struct vector3D v1, struct vector3D v2){

    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

}

//-----------------------------------------------------------------------------------------------//

struct vector3D crossProduct(struct vector3D v1, struct vector3D v2){

    int x = (v1.y * v2.z) - (v1.z * v2.y);
    int y = (v1.z * v2.x) - (v1.x * v2.z);
    int z = (v1.x * v2.y) - (v1.y * v2.x);

    return newVector3D(x, y, z);

}

//-----------------------------------------------------------------------------------------------//
