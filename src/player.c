// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/player.h"
#include "include/constants.h"

//-----------------------------------------------------------------------------------------------//

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;
bool mDown = false;
bool leftDown = false;
bool rightDown = false;
bool upDown = false;
bool downDown = false;

//-----------------------------------------------------------------------------------------------//

void playerSetup(){

    pPos.x = 250;
    pPos.y = 250;
    pPos.z = 40;

    pRot.h = 0;
    pRot.v = 0;

    lmX = WINDOW_WIDTH / 2;
    lmY = WINDOW_HEIGHT / 2;

}

//-----------------------------------------------------------------------------------------------//

void playerInput(SDL_Event event){

    if (event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&mX, &mY);
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
            case SDLK_m:
                mDown = true;
            break;
            case SDLK_LEFT:
                leftDown = true;
            break;
            case SDLK_RIGHT:
                rightDown = true;
            break;
            case SDLK_UP:
                upDown = true;
            break;
            case SDLK_DOWN:
                downDown = true;
            break;
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
            case SDLK_m:
                mDown = false;
            case SDLK_LEFT:
                leftDown = false;
            case SDLK_RIGHT:
                rightDown = false;
            case SDLK_UP:
                upDown = false;
            case SDLK_DOWN:
                downDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void playerUpdate(float deltaTime){
    // may want to paramaterise speed values for x and y (or one overall for linear movement)

    float dx = M.sin[(int)pRot.h] * 150.0 * deltaTime;
    float dy = M.cos[(int)pRot.h] * 150.0 * deltaTime;

    if (wDown){ pPos.x += dx; pPos.y += dy;}
    if (sDown){ pPos.x -= dx; pPos.y -= dy;}

    if (dDown){ pPos.x += dy * 1.2; pPos.y -= dx * 1.2;}
    if (aDown){ pPos.x -= dy * 1.2; pPos.y += dx * 1.2;}





    // pitch up down keys
    if (downDown){ pRot.v -= 15 * deltaTime;}
    if (upDown){ pRot.v += 15 * deltaTime;}

    // move up down keys
    //if (wDown && mDown){ pPos.z -= 60 * deltaTime;}
    //if (sDown && mDown){ pPos.z += 60 * deltaTime;}

    // Look left right keys
    if (leftDown){
        pRot.h -= 120 * deltaTime;
        if (pRot.h < 0){pRot.h += 360;};
    }
    if (rightDown){
        pRot.h += 120 * deltaTime;
        if (pRot.h > 359){pRot.h -= 360;};
    }

    lmX = mX;
    lmY = mY;

        // Look left right mouse
//
//    int dmX = mX - lmX;
//    int dmY = mY - lmY;
//
//    if (dmX != 0){
//        int rX = dmX * 8 * deltaTime;
//        pRot.h += rX;
//        if (pRot.h < 0){pRot.h += 360;};
//        if (pRot.h > 359){pRot.h -= 360;};
//    }
//
//    if (dmY != 0){
//        int rY = dmY * 8 * deltaTime;
//        pRot.v += rY;
//    }

}

//-----------------------------------------------------------------------------------------------//
