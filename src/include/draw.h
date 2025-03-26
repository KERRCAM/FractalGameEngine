// LIBRARY IMPORTS
#include <SDL2/SDL.h>

// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define WINDOW_WIDTH 1200

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct {
    int x1, y1;
    int x2, y2;
    int c; // colour
}walls; walls W[30];

typedef struct {
    int ws, we;
    int z1, z2;
    int d;
    int c1, c2;
    int surf[WINDOW_WIDTH];
    int surface;
}sectors; sectors S[30];

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void sectorSetup();

int dist(int x1, int y1, int x2, int y2);

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2);

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int s);

void sectorRender(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//