// LIBRARY IMPORTS
#include <SDL2/SDL.h>

// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS



//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void sectorSetup();

int dist(int x1, int y1, int x2, int y2);

float minDistance(int px, int py, int x1, int y1, int x2, int y2);

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2);

void floors(SDL_Renderer* renderer);

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int s, int w, int frontBack, int colour);

void sectorRender(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//