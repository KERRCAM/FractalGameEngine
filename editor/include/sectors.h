// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "walls.h"
#include "../src/include/constants.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define MAX_WALLS 32

//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct sector {
    int ws, we;
    int minZ, maxZ;
    int floorColour, ceilingColour;
    struct wall sectorWalls[MAX_WALLS];
    int distance;
    int surf[WINDOW_WIDTH];
    int surface;
};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct sector newSector(int minZ, int maxZ, int floorColour, int ceilingColour);

//-----------------------------------------------------------------------------------------------//
