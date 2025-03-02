// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>

// LOCAL IMPORTS
#include "include/player.h"

//-----------------------------------------------------------------------------------------------//

const double FPS = 60.0;
const double FRAME_TIME = 1000.0 / FPS; // In MS
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;
const double PI = 3.14159265358979323846;

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
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

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

    playerSetup();

}

//-----------------------------------------------------------------------------------------------//

void update(){

    /* ONLY NEEDED FOR A CAPPED FRAME RATE
    int waitTime = FRAME_TIME - (SDL_GetTicks() / lastFrame);
    if (waitTime > 0 && waitTime < FRAME_TIME){ SDL_Delay(waitTime); }
    */

    float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;

    lastFrame = SDL_GetTicks();

    playerUpdate(deltaTime);

}

//-----------------------------------------------------------------------------------------------//

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Calls to draw objects to the screen
    // playerRender(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    float grid[WINDOW_HEIGHT][WINDOW_WIDTH];
    float angle;
    int size = 4;

    for (int i = 0; i < WINDOW_HEIGHT; i += 5){
        for (int j = 0; j < WINDOW_WIDTH; j += 5){
            angle = ((float)j / ((float)WINDOW_WIDTH / 10)) * PI;
            grid[i][j] = angle;

            SDL_RenderDrawPoint(renderer, i, j);

            int targetX = round(i + (sin(angle)) * size);
            int targetY = round(j + (cos(angle)) * size);

            SDL_RenderDrawLine(renderer, i, j, targetX, targetY);
        }
    }

    SDL_RenderPresent(renderer);

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

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

    destroyWindow();

    return 0;

}

//-----------------------------------------------------------------------------------------------//
