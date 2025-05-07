#pragma once
// LIBRARY IMPORTS
#include <stdbool.h>

// LOCAL IMPORTS
#include "rotations.h"
#include "../editor/include/walls.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

struct pPos {
    float x, y, z;
} pPos;

struct rotation2D pRot;

int dashTime;
int vertAcc;
bool inAir;
int lastBullet;

struct wall* nearWall;

int pHP;
int score;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void playerSetup();

void playerInput(SDL_Event event);

int playerUpdate(float deltaTime);

//-----------------------------------------------------------------------------------------------//
