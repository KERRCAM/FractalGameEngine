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

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2);

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int s, int colour);

void sectorRender(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//