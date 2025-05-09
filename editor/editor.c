// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/input.h"
#include "include/editor.h"
#include "include/write.h"
#include "../levels/level1.h"

//-----------------------------------------------------------------------------------------------//
// INITIALISATIONS

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int gameRunning = 0;
int lastFrame = 0;

//-----------------------------------------------------------------------------------------------//

int initialize_window(void){
    /*
    Sets up the window for the editor.
    */

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
    /*
    Handles input for the editor.
    */

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            gameRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                saveLevels();
                gameRunning = 0;
            }
            break;
    }

    editorInput(event);

}

//-----------------------------------------------------------------------------------------------//

void setup(){
    /*
    Sets up edtor arrays for all the levels, their sectors and walls.
    */

    for (int i = 0; i < 360; i++){
        M.cos[i] = cos(i / 180.0 * M_PI);
        M.sin[i] = sin(i / 180.0 * M_PI);
    }

    for (int i = 0; i < MAX_LEVELS; i++){
        levels[i] = newLevel(0, 0, 0, 0);
    }

    currentLevel = levels[0];
    currentSector = currentLevel.levelSectors[0];
    currentWall = currentSector.sectorWalls[0];

    // Existing level loading
    ///*
    for (int k = 0; k < 1; k++){ // needs to be replaced with MAX_LEVEL later
        for (int i = 0; i < MAX_SECTORS; i++){
            levels[k].levelSectors[i].minZ = sectors[i][0];
            levels[k].levelSectors[i].maxZ = sectors[i][1];
            levels[k].levelSectors[i].floorColour = sectors[i][2];
            levels[k].levelSectors[i].ceilingColour = sectors[i][3];
            levels[k].levelSectors[i].init = sectors[i][4];

            for (int j = 0; j < MAX_WALLS; j++){
                levels[k].levelSectors[i].sectorWalls[j].x1 = walls[i][j][0];
                levels[k].levelSectors[i].sectorWalls[j].y1 = walls[i][j][1];
                levels[k].levelSectors[i].sectorWalls[j].x2 = walls[i][j][2];
                levels[k].levelSectors[i].sectorWalls[j].y2 = walls[i][j][3];
                levels[k].levelSectors[i].sectorWalls[j].colour = walls[i][j][4];
                levels[k].levelSectors[i].sectorWalls[j].init = walls[i][j][5];
            }
        }
    }
    //*/

}

//-----------------------------------------------------------------------------------------------//

void drawWalls(){
    /*
    Draws the walls of the currently selected level onto the editor window.
    Highlights the currently selected sector and wall differntly.
    */

    for (int i = 0; i < MAX_SECTORS; i++){
        for (int j = 0; j < MAX_WALLS; j++){
            if (i == currentSectorPos){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 10, 130, 30, 30);
            }
            if (i == currentSectorPos && j == currentWallPos){
                SDL_SetRenderDrawColor(renderer, 0, 25, 255, 255);
            }
            struct wall w = levels[currentLevelPos].levelSectors[i].sectorWalls[j];
            drawWall(w);
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void drawWall(struct wall w){
    /*
    Individual wall drawing. Each is only single pixel thick lines so fairly simple.
    */

    if (w.x1 != -1 && w.y1 != -1 && w.x2 != -1 && w.y2 != -1){
        SDL_RenderDrawLine(renderer, w.x1, w.y1, w.x2, w.y2);
    }

}

//-----------------------------------------------------------------------------------------------//

void render(){
    /*
    Main render loop for the level editor.
    */

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

    // Getting the closest grid point so we can put a cube cersor on it for the user.
    int closestX = round(mX / gridSize) * gridSize;
    int closestY = round(mY / gridSize) * gridSize;

    SDL_Rect rect = {closestX - 5, closestY - 5, 10, 10}; // cube cersor on the grid.

    SDL_SetRenderDrawColor(renderer, 10, 30, 250, 255);

    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);

    // Drawing the grid lines.
    SDL_SetRenderDrawColor(renderer, 10, 255, 20, 255);
    if (currentWall.x1 != -1 && currentWall.x2 != -1){
        levels[currentLevelPos].levelSectors[currentSectorPos].sectorWalls[currentWallPos] = newWall(currentWall.x1, currentWall.y1,
                                                            currentWall.x2, currentWall.y2, 0, 1);
        levels[currentLevelPos].levelSectors[currentSectorPos].minZ = 0;
        levels[currentLevelPos].levelSectors[currentSectorPos].init = 1;
    } else if (currentWall.x1 != -1 && currentWall.x2 == -1){
        SDL_RenderDrawLine(renderer, currentWall.x1, currentWall.y1, closestX, closestY);
    }

    drawWalls();

    SDL_RenderPresent(renderer);

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){
    /*
    Destorys renderer and window for the editor.
    */

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

//-----------------------------------------------------------------------------------------------//

int main(){
    /*
    Editor loop.
    */

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
