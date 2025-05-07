// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/constants.h"
#include "include/player.h"
#include "include/draw.h"
#include "include/globals.h"
#include "include/ui.h"

//-----------------------------------------------------------------------------------------------//
// INITIALISATIONS

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Window* windowEND = NULL;
SDL_Renderer* rendererEND = NULL;

int gameRunning = 0;
int lastFrame = 0;
int endScreen = 0;

//-----------------------------------------------------------------------------------------------//

int initialize_window(void){
    /*
    Sets up game winodw.
    */

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initialising SDL\n");
        return 0;
    }

    window = SDL_CreateWindow(
        "TEST BUILD",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    if (!window){
        fprintf(stderr, "Error creating SDL window\n");
        return 0;
    }

    // -1 for default driver, 0 for no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        fprintf(stderr, "Error creating SDL renderer\n");
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------//

void processInput(){
    /*
    Handles all game inputs, including player controls and window quitting.
    */

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            gameRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                gameRunning = 0;
            }
            break;
    }

    playerInput(event);

}

//-----------------------------------------------------------------------------------------------//

void setup(){
    /*
    Sets up so global values for the game and initialises various game aspects.
     */

    for (int i = 0; i < 360; i++){
        M.cos[i] = cos(i / 180.0 * M_PI);
        M.sin[i] = sin(i / 180.0 * M_PI);
    }

    gameStartTime = SDL_GetTicks();

    playerSetup();
    drawSetup();
    demonSetup();
    bulletSetup();

}

//-----------------------------------------------------------------------------------------------//

void update(){
    /*
    Handles all required game updates ran each frame.
    */

    /* // ONLY NEEDED FOR A CAPPED FRAME RATE
    int waitTime = FRAME_TIME - (SDL_GetTicks() / lastFrame);
    if (waitTime > 0 && waitTime < FRAME_TIME){ SDL_Delay(waitTime); }
    */

    deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;

    lastFrame = SDL_GetTicks();

    if (playerUpdate(deltaTime) == 0){ endScreen = 1; timeOfDeath = SDL_GetTicks();}
    if (score >= 10000){ endScreen = 1;}

    demonUpdate();
    bulletUpdate();

}

//-----------------------------------------------------------------------------------------------//

void render(){
    /*
    Handle all render calls for the game.
    */

    // Screen colour
    SDL_SetRenderDrawColor(renderer, 0, 0, 60, 255);
    SDL_RenderClear(renderer);
    renderWorld(renderer);
    renderUI(renderer);
    SDL_RenderPresent(renderer);

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){
    /*
    Destorys game renderer and window.
    */

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

//-----------------------------------------------------------------------------------------------//

int main(){
    /*
    Main game loop.
    */

    gameRunning = initialize_window();

    setup();

    // Game loop, on player death the score pauses all updates stop, but the game continues to
    // to render so the player can see their score and take input so they can quit the window.
    while (gameRunning){

        if (endScreen){
            processInput();
            render();
        } else {
            processInput();
            update();
            render();
        }

    }

    destroyWindow();

    return 0;

}

//-----------------------------------------------------------------------------------------------//
