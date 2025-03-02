// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

// may go back to ints, whatever is better later
struct vector2D {
    int x;
    int y;
};

struct vector3D {
    int x;
    int y;
    int z;
};

//-----------------------------------------------------------------------------------------------//
//FUNCTIONS

struct vector2D newVector2D(int x, int y);

struct vector3D newVector3D(int x, int y, int z);

int manhattanLength2D(struct vector2D v1);

int manhattanLength3D(struct vector3D v1);

int manhattanDistance2D(struct vector2D v1, struct vector2D v2);

int manhattanDistance3D(struct vector3D v1, struct vector3D v2);

float euclidianLength2D(struct vector2D v1);

float euclidianLength3D(struct vector3D v1);

float euclidianDistance2D(struct vector2D v1, struct vector2D v2);

float euclidianDistance3D(struct vector3D v1, struct vector3D v2);

float dotProduct2D(struct vector2D v1, struct vector2D v2);

float dotProduct3D(struct vector3D v1, struct vector3D v2);

struct vector3D crossProduct(struct vector3D v1, struct vector3D v2);

//-----------------------------------------------------------------------------------------------//
