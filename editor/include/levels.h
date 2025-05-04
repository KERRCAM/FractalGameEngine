// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "sectors.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define MAX_LEVELS 16
#define MAX_SECTORS 12

//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct level {
    int pX, pY, pZ;
    int init;
    struct sector levelSectors[MAX_SECTORS];
};

struct level levels[MAX_LEVELS];

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct level newLevel(int pX, int pY, int pZ, int init);

//-----------------------------------------------------------------------------------------------//
