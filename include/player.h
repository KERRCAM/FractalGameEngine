// LIBRARY IMPORTS
#include <stdbool.h>

// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct vector2D {
    int x;
    int y;
};

struct player {
    float x;
    float y;
    float width;
    float height;
} player;

//-----------------------------------------------------------------------------------------------//
//FUNCTIONS

void playerSetup();

void playerInput(SDL_Event event);

void playerUpdate(float deltaTime);

void playerRender(SDL_Renderer* renderer);

//-----------------------------------------------------------------------------------------------//