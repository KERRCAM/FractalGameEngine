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
bool spaceDown = false;

//-----------------------------------------------------------------------------------------------//

void playerSetup(){

    pPos.x = 250;
    pPos.y = 250;
    pPos.z = 40;

    pRot.h = 0;
    pRot.v = 0;

    inAir = false;

}

//-----------------------------------------------------------------------------------------------//

void playerInput(SDL_Event event){

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
            case SDLK_SPACE:
                spaceDown = true;
            break;
            case SDLK_LSHIFT:
                if (SDL_GetTicks() - dashTime > 2500){ dashTime = SDL_GetTicks();}
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
            case SDLK_SPACE:
                spaceDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void playerUpdate(float deltaTime){

    float dx = M.sin[(int)pRot.h] * 150.0 * deltaTime;
    float dy = M.cos[(int)pRot.h] * 150.0 * deltaTime;

    if (SDL_GetTicks() - dashTime < 200){
        dx *= 6;
        dy *= 6;
    }

    if (spaceDown && pPos.z == 40){
        vertAcc = 6;
        inAir = true;
    }

    if (inAir){
        int newZ = pPos.z - (vertAcc * 30.0 * deltaTime);
        if (newZ > 40){ pPos.z = 40; inAir = false;}
        else (pPos.z = newZ);
        vertAcc -= 30.0 * deltaTime;
    }

    if (wDown){ pPos.x += dx; pPos.y += dy;}
    if (sDown){ pPos.x -= dx; pPos.y -= dy;}
    if (dDown){ pPos.x += dy * 1.2; pPos.y -= dx * 1.2;}
    if (aDown){ pPos.x -= dy * 1.2; pPos.y += dx * 1.2;}

    // Look left right keys
    if (leftDown){
        pRot.h -= 120 * deltaTime;
        if (pRot.h < 0){pRot.h += 360;};
    }
    if (rightDown){
        pRot.h += 120 * deltaTime;
        if (pRot.h > 359){pRot.h -= 360;};
    }

}

//-----------------------------------------------------------------------------------------------//
