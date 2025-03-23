// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "levels.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define gridSize 25.0

//-----------------------------------------------------------------------------------------------//
//STRUCTS

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
