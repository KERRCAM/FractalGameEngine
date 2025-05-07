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

struct wall* allWalls[MAX_SECTORS * MAX_WALLS];
struct demon demons[MAX_DEMONS];
struct bullet bullets[MAX_BULLETS];

float deltaTime;
float gameStartTime;
float lastSpawned; // Time a demon last spawned in
int spawnRate; // Current demon spawn rate
int wallsSize;
int timeOfDeath;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//
