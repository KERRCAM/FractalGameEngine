// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "walls.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define MAX_WALLS 32

//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct sector {
    int minZ, maxZ;
    int floorColour, ceilingColour;
    struct wall sectorWalls[MAX_WALLS];
    int dis;
    int surf[1200];
    int surface;
};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct sector newSector(int minZ, int maxZ, int floorColour, int ceilingColour);

//-----------------------------------------------------------------------------------------------//
