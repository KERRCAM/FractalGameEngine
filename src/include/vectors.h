// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

// may go back to ints, whatever is better later
struct vector2D {
    float x;
    float y;
};

struct vector3D {
    float x;
    float y;
    float z;
};

//-----------------------------------------------------------------------------------------------//
//FUNCTIONS

struct vector2D newVector2D(float x, float y);

struct vector3D newVector3D(float x, float y, float z);

float manhattanLength2D(struct vector2D v1);

float manhattanLength3D(struct vector3D v1);

float manhattanDistance2D(struct vector2D v1, struct vector2D v2);

float manhattanDistance3D(struct vector3D v1, struct vector3D v2);

float euclidianLength2D(struct vector2D v1);

float euclidianLength3D(struct vector3D v1);

float euclidianDistance2D(struct vector2D v1, struct vector2D v2);

float euclidianDistance3D(struct vector3D v1, struct vector3D v2);

float dotProduct2D(struct vector2D v1, struct vector2D v2);

float dotProduct3D(struct vector3D v1, struct vector3D v2);

int crossProduct2D(struct vector2D v1, struct vector2D v2, struct vector2D v3);

struct vector3D crossProduct3D(struct vector3D v1, struct vector3D v2);

//-----------------------------------------------------------------------------------------------//
