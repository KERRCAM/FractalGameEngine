// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

// LOCAL IMPORTS
#include "include/input.h"

//-----------------------------------------------------------------------------------------------//

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;
bool lClick = false;

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
            case SDLK_w:
                wDown = true;
            break;
            case SDLK_s:
                sDown = true;
            break;
            case SDLK_a:
                aDown = true;
            break;
            case SDLK_d:
                dDown = true;
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
            case SDLK_w:
                wDown = false;
            case SDLK_s:
                sDown = false;
            case SDLK_a:
                aDown = false;
            case SDLK_d:
                dDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//
