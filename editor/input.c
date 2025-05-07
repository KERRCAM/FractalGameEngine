// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

// LOCAL IMPORTS
#include "include/input.h"
#include "include/editor.h"

//-----------------------------------------------------------------------------------------------//

void editorInput(SDL_Event event){
    /*
    Handles all input for the level editor.
    Not as complicated as it might look, all thats rally happening is changing some postions and
    struct values for each user input.
    Also makes prints to the terminal with information about currently selected walls, sectors,
    levels, colours, heights etc.
    */

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
            case SDLK_COMMA:
                currentLevelPos -= 1;
                if (currentLevelPos < 0){ currentLevelPos = MAX_LEVELS - 1; }
                currentLevel = levels[currentLevelPos];
                currentSector = currentLevel.levelSectors[0];
                currentSectorPos = 0;
                currentWall = currentSector.sectorWalls[0];
                currentWallPos = 0;
                printf("Current level pos = %d\n", currentLevelPos);
                break;
            case SDLK_PERIOD:
                currentLevelPos += 1;
                if (currentLevelPos == MAX_LEVELS){ currentLevelPos = 0; }
                currentLevel = levels[currentLevelPos];
                currentSector = currentLevel.levelSectors[0];
                currentSectorPos = 0;
                currentWall = currentSector.sectorWalls[0];
                currentSectorPos = 0;
                printf("Current level pos = %d\n", currentLevelPos);
                break;
            case SDLK_DOWN:
                currentSectorPos -= 1;
                if (currentSectorPos < 0){ currentSectorPos = MAX_SECTORS - 1; }
                currentSector = currentLevel.levelSectors[currentSectorPos];
                currentWall = currentSector.sectorWalls[0];
                currentWallPos = 0;
                printf("Current sector pos = %d\n", currentSectorPos);
                printf("minZ = %d, maxZ = %d\n", currentSector.minZ, currentSector.maxZ);
                break;
            case SDLK_UP:
                currentSectorPos += 1;
                if (currentSectorPos ==  MAX_SECTORS){ currentSectorPos = 0; }
                currentSector = currentLevel.levelSectors[currentSectorPos];
                currentWall = currentSector.sectorWalls[0];
                currentWallPos = 0;
                printf("Current sector pos = %d\n", currentSectorPos);
                printf("minZ = %d, maxZ = %d\n", currentSector.minZ, currentSector.maxZ);
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
            case SDLK_r:
                currentWall.x1 = -1;
                currentWall.y1 = -1;
                currentWall.x2 = -1;
                currentWall.y2 = -1;
            break;
            case SDLK_w:
                levels[currentLevelPos].levelSectors[currentSectorPos].maxZ += 5;
                printf("Current sector maxZ = %d\n",
                        levels[currentLevelPos].levelSectors[currentSectorPos].maxZ);
                break;
            case SDLK_s:
                levels[currentLevelPos].levelSectors[currentSectorPos].maxZ -= 5;
                printf("Current sector maxZ = %d\n",
                        levels[currentLevelPos].levelSectors[currentSectorPos].maxZ);
                break;
            case SDLK_c:
                if (levels[currentLevelPos].levelSectors[currentSectorPos].sectorWalls[currentWallPos].colour == 10){
                    levels[currentLevelPos].levelSectors[currentSectorPos].sectorWalls[currentWallPos].colour = 0;
                } else{
                    levels[currentLevelPos].levelSectors[currentSectorPos].sectorWalls[currentWallPos].colour += 1;
                }
                printf("Current wall colour = %d\n",
                        levels[currentLevelPos].levelSectors[currentSectorPos].sectorWalls[currentWallPos].colour);
                break;
        }
    }

}

//-----------------------------------------------------------------------------------------------//
