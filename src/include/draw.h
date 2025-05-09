#pragma once
// LIBRARY IMPORTS
#include <SDL2/SDL.h>

// LOCAL IMPORTS
#include "constants.h"
#include "demon.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS



//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void drawSetup();

int dist(int x1, int y1, int x2, int y2);

void drawEntity(SDL_Renderer* renderer, int width, int height, int x, int y, int colour, int init);

float minDistance(int px, int py, int x1, int y1, int x2, int y2);

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2);

void floors(SDL_Renderer* renderer);

void ceilings(SDL_Renderer* renderer);

void drawWall(SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int colour);

void wallSetup(SDL_Renderer* renderer, int w);

int checkBulletProximity(struct demon* d);

void calculateWallDistances();

void sortWalls();

void renderWorldObjects(SDL_Renderer* renderer);

void renderWorld(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//