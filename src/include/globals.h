#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "demon.h"
#include "bullet.h"
#include "constants.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

struct demon demons[MAX_DEMONS];
struct bullet bullets[MAX_BULLETS];

float deltaTime;
float gameStartTime;
float lastSpawned;
int spawnRate;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//
