// LIBRARY IMPORTS
#include <stdbool.h>

// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct player {
    int x, y, z;
    int angleH;
    int angleV;
} player;

//-----------------------------------------------------------------------------------------------//
//FUNCTIONS

void playerSetup();

void playerInput(SDL_Event event);

void playerUpdate(float deltaTime);

void playerRender(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//