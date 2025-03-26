// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "../src/include/constants.h"
#include "include/input.h"
#include "include/editor.h"

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

    int displays = SDL_GetNumVideoDisplays();

    window = SDL_CreateWindow(
        "LEVEL EDITOR",
        SDL_WINDOWPOS_CENTERED_DISPLAY(displays),
        SDL_WINDOWPOS_CENTERED_DISPLAY(displays),
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
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

    editorInput(event);

}

//-----------------------------------------------------------------------------------------------//

void setup(){

    for (int i = 0; i < 360; i++){
        M.cos[i] = cos(i / 180.0 * M_PI);
        M.sin[i] = sin(i / 180.0 * M_PI);
    }

    struct level l = newLevel(0, 0, 0);
    currentLevel = l;
    currentSector = currentLevel.levelSectors[0];
    currentWall = currentSector.sectorWalls[0];

}

//-----------------------------------------------------------------------------------------------//

void update(){

    /* // ONLY NEEDED FOR A CAPPED FRAME RATE
    int waitTime = FRAME_TIME - (SDL_GetTicks() / lastFrame);
    if (waitTime > 0 && waitTime < FRAME_TIME){ SDL_Delay(waitTime); }
    */

    // float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;

    // lastFrame = SDL_GetTicks();

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//

void drawWalls(){

    for (int i = 0; i < MAX_SECTORS; i++){
        if (i == currentSectorPos){
            SDL_SetRenderDrawColor(renderer, 10, 255, 20, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 10, 130, 30, 30);
        }
        for (int j = 0; j < MAX_WALLS; j++){
            if (i == currentSectorPos && j == currentWallPos){
                SDL_SetRenderDrawColor(renderer, 0, 25, 255, 255);
            }
            struct wall w = currentLevel.levelSectors[i].sectorWalls[j];
            drawWall(w);
        }
    }



}

//-----------------------------------------------------------------------------------------------//

void drawWall(struct wall w){

    if (w.x1 != -1 && w.y1 != -1 && w.x2 != -1 && w.y2 != -1){
        SDL_RenderDrawLine(renderer, w.x1, w.y1, w.x2, w.y2);
    }

}

//-----------------------------------------------------------------------------------------------//

void render(){

    // Screen colour
    SDL_SetRenderDrawColor(renderer, 0, 0, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);

    for (int row = 0; row < WINDOW_HEIGHT; row += gridSize){
        SDL_RenderDrawLine(renderer, 0, row, WINDOW_WIDTH, row);
    }

    for (int col = 0; col < WINDOW_WIDTH; col += gridSize){
        SDL_RenderDrawLine(renderer, col, 0, col, WINDOW_HEIGHT);
    }

    int closestX = round(mX / gridSize) * gridSize;
    int closestY = round(mY / gridSize) * gridSize;

    SDL_Rect rect = {closestX - 5, closestY - 5, 10, 10};

    SDL_SetRenderDrawColor(renderer, 10, 30, 250, 255);

    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 10, 255, 20, 255);
    if (currentWall.x1 != -1 && currentWall.x2 != -1){
        currentLevel.levelSectors[currentSectorPos].sectorWalls[currentWallPos] = newWall(currentWall.x1, currentWall.y1,
                                                            currentWall.x2, currentWall.y2, 0);
    } else if (currentWall.x1 != -1 && currentWall.x2 == -1){
        SDL_RenderDrawLine(renderer, currentWall.x1, currentWall.y1, closestX, closestY);
    }

    drawWalls();

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

/*
left and right to switch between current wall, sector and level.
up and down to change max z of current sector
shift up and down to change min z of current sector
figure out good delete controls
r to reset draw wall
later we can make some buttons, but for now just use keybord stuff

when writting to file obviously skip over uninitialised walls / secotrs / levels and deleted ones
deleted ones representation tbd

command + s exits editor and re writes level files


May want to scale down wall coords at write time
currently in editor 1 = 25
in renderer 1 = 8
 */