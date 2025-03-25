// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

// LOCAL IMPORTS
#include "include/input.h"
#include "include/editor.h"

//-----------------------------------------------------------------------------------------------//



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

            break;
            case SDLK_DOWN:

            break;
            case SDLK_LEFT:
                currentWallPos -= 1;
                if (currentWallPos < 0){ currentWallPos = MAX_WALLS - 1; }
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current wall pos = %d\n", currentWallPos);
                printf("x1 = %d, y1 = %d\n", currentWall.x1, currentWall.y1);
                printf("x2 = %d, y2 = %d\n", currentWall.x2, currentWall.y2);
            break;
            case SDLK_RIGHT:
                currentWallPos += 1;
                if (currentWallPos == MAX_WALLS) { currentWallPos = 0; }
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current wall pos = %d\n", currentWallPos);
                printf("x1 = %d, y1 = %d\n", currentWall.x1, currentWall.y1);
                printf("x2 = %d, y2 = %d\n", currentWall.x2, currentWall.y2);
            break;
            case SDLK_COMMA:
                currentSectorPos -= 1;
                if (currentSectorPos < 0){ currentSectorPos = MAX_SECTORS - 1; }
                currentSector = currentLevel.levelSectors[currentSectorPos];
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current sector pos = %d\n", currentSectorPos);
                printf("minZ = %d, maxZ = %d\n", currentSector.minZ, currentSector.maxZ);
            break;
            case SDLK_PERIOD:
                currentSectorPos += 1;
                if (currentSectorPos ==  MAX_SECTORS){ currentSectorPos = 0; }
                currentSector = currentLevel.levelSectors[currentSectorPos];
                currentWall = currentSector.sectorWalls[currentWallPos];
                printf("Current sector pos = %d\n", currentSectorPos);
                printf("minZ = %d, maxZ = %d\n", currentSector.minZ, currentSector.maxZ);
            break;
            case SDLK_l:

            break;
            case SDLK_r:
                currentWall.x1 = -1;
                currentWall.y1 = -1;
                currentWall.x2 = -1;
                currentWall.y2 = -1;
            break;
        }
    }

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//
