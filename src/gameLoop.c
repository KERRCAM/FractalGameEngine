// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2_ttf/SDL_ttf.h>

// LOCAL IMPORTS
#include "include/constants.h"
#include "include/player.h"
#include "include/vectors.h"
#include "include/draw.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//
// INITIALISATIONS

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int gameRunning = 0;
int lastFrame = 0;

//-----------------------------------------------------------------------------------------------//

int initialize_window(void){

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

//    if (TTF_Init() == -1){
//        fprintf(stderr, "Error initialising TTF\n");
//        return 0;
//    }

    return 1;
}

//-----------------------------------------------------------------------------------------------//

void processInput(){

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

    for (int i = 0; i < 360; i++){
        M.cos[i] = cos(i / 180.0 * M_PI);
        M.sin[i] = sin(i / 180.0 * M_PI);
    }

    gameStartTime = SDL_GetTicks();

    playerSetup();
    drawSetup();

}

//-----------------------------------------------------------------------------------------------//

void update(){

    /* // ONLY NEEDED FOR A CAPPED FRAME RATE
    int waitTime = FRAME_TIME - (SDL_GetTicks() / lastFrame);
    if (waitTime > 0 && waitTime < FRAME_TIME){ SDL_Delay(waitTime); }
    */

    deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;

    lastFrame = SDL_GetTicks();

    if (playerUpdate(deltaTime) == 0){ gameRunning = 0;};

}

//-----------------------------------------------------------------------------------------------//

void render(){

    // Screen colour
    SDL_SetRenderDrawColor(renderer, 0, 0, 60, 255);
    SDL_RenderClear(renderer);
    floors(renderer);
    ceilings(renderer);
    renderWorld(renderer);
    drawNumber(renderer, 20, 20, 3);
    SDL_RenderPresent(renderer);

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //TTF_Quit();

}

//-----------------------------------------------------------------------------------------------//

int main(){

    gameRunning = initialize_window();

    setup();

    while (gameRunning){

        processInput();
        update();
        render();

    }

    float timeSurvived = SDL_GetTicks() - gameStartTime;
    int survivalScore = timeSurvived / 1000.0;
    printf("Final score: %d\n", survivalScore + score);

    destroyWindow();

    return 0;

}

//-----------------------------------------------------------------------------------------------//
