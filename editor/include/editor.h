// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "levels.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS

struct level levels[MAX_LEVELS];
#define gridSize 25.0

//-----------------------------------------------------------------------------------------------//
// STRUCTS ADN VARIABLES

struct level currentLevel;
struct sector currentSector;
struct wall currentWall;

int currentLevelPos;
int currentSectorPos;
int currentWallPos;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void drawWall(struct wall w);
void drawWalls();

//-----------------------------------------------------------------------------------------------//
