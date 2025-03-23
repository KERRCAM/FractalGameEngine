// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

// LOCAL IMPORTS
#include "include/input.h"
#include "include/editor.h"

//-----------------------------------------------------------------------------------------------//

bool upDown = false;
bool downDown = false;
bool sDown = false;
bool lDown = false;
bool leftShiftDown = false;

//-----------------------------------------------------------------------------------------------//

void editorInput(SDL_Event event){

    if (event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&mX, &mY);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
            if (currentWall.x1 == -1 && currentWall.x2 == -1){
                currentWall.x1 = round(mX / gridSize) * gridSize;
                currentWall.y1 = round(mY / gridSize) * gridSize;
            } else if (currentWall.x2 == -1) {
                currentWall.x2 = round(mX / gridSize) * gridSize;
                currentWall.y2 = round(mY / gridSize) * gridSize;
            }
            printf("x1 = %d, y1 = %d\n", currentWall.x1, currentWall.y1);
            printf("x2 = %d, y2 = %d\n", currentWall.x2, currentWall.y2);
        }
    }

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_UP:
                upDown = true;
            break;
            case SDLK_DOWN:
                downDown = true;
            break;
            case SDLK_LEFT:
                currentWallPos -= 1;
                if (currentWallPos < 0){ currentWallPos = MAX_WALLS - 1; }
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current wall pos = %d\n", currentWallPos);
            break;
            case SDLK_RIGHT:
                currentWallPos += 1;
                if (currentWallPos == MAX_WALLS) { currentWallPos = 0; }
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current wall pos = %d\n", currentWallPos);
            break;
            case SDLK_LSHIFT:
                leftShiftDown = true;
            break;
            case SDLK_s:
                sDown = true;
            break;
            case SDLK_l:
                lDown = true;
            break;
            case SDLK_r:
                currentWall.x1 = -1;
                currentWall.y1 = -1;
                currentWall.x2 = -1;
                currentWall.y2 = -1;

            break;
        }
    }

    if (event.type == SDL_KEYUP){
        switch (event.key.keysym.sym){
            case SDLK_UP:
                upDown = false;
            case SDLK_DOWN:
                downDown = false;
            case SDLK_LSHIFT:
                leftShiftDown = false;
            case SDLK_s:
                sDown = false;
            case SDLK_l:
                lDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//
