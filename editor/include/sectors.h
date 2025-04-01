// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "walls.h"
#include "../src/include/constants.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct sector {
    int minZ, maxZ;
    int floorColour, ceilingColour;
    struct wall sectorWalls[MAX_WALLS];
    float mpx;
    float mpy;
    float distance;
    struct wall closestWall;
    int surf[WINDOW_WIDTH];
    int surface;
    int init;
};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct sector newSector(int minZ, int maxZ, int floorColour, int ceilingColour, int init);

//-----------------------------------------------------------------------------------------------//
