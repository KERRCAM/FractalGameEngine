// LIBRARY IMPORTS
#include <stdbool.h>

// LOCAL IMPORTS
#include "rotations.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct pPos {
    float x, y, z;
} pPos;

struct rotation2D pRot;

//-----------------------------------------------------------------------------------------------//
//FUNCTIONS

void playerSetup();

void playerInput(SDL_Event event);

void playerUpdate(float deltaTime);

//-----------------------------------------------------------------------------------------------//
