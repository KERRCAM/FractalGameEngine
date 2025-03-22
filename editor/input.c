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
bool leftDown = false;
bool rightDown = false;
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
            if (eX == -1 && sX == -1){
                sX = round(mX / gridSize) * gridSize;
                sY = round(mY / gridSize) * gridSize;
            } else if (eX == -1) {
                eX = round(mX / gridSize) * gridSize;
                eY = round(mY / gridSize) * gridSize;
            }
            printf("x1 = %d, y1 = %d\n", sX, sY);
            printf("x2 = %d, y2 = %d\n", eX, eY);
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
                leftDown = true;
            break;
            case SDLK_RIGHT:
                rightDown = true;
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
                sX = -1;
                sY = -1;
                eX = -1;
                eY = -1;
        }
    }

    if (event.type == SDL_KEYUP){
        switch (event.key.keysym.sym){
            case SDLK_UP:
                upDown = false;
            case SDLK_DOWN:
                downDown = false;
            case SDLK_LEFT:
                leftDown = false;
            case SDLK_RIGHT:
                rightDown = false;
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
