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
bool zDown = false;
bool xDown = false;

//-----------------------------------------------------------------------------------------------//

void playerSetup(){

    pPos.x = 70;
    pPos.y = -110;
    pPos.z = 20;

    pRot.h = 0;
    pRot.v = 0;

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
            case SDLK_z:
                zDown = true;
            break;
            case SDLK_x:
                xDown = true;
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
            case SDLK_z:
                zDown = false;
            case SDLK_x:
                xDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void playerUpdate(float deltaTime){
    // may want to paramaterise speed values for x and y (or one overall for linear movement)

    if (aDown && !mDown){
        pRot.h -= 4 ;
        if (pRot.h < 0){pRot.h += 360;};
    }
    if (dDown && !mDown){
        pRot.h += 4;
        if (pRot.h > 359){pRot.h -= 360;};
    }

    int dx = M.sin[pRot.h] * 10.0;
    int dy = M.cos[pRot.h] * 10.0;

    if (wDown && !mDown){ pPos.x += dx; pPos.y += dy;}
    if (sDown && !mDown){ pPos.x -= dx; pPos.y -= dy;}

    if (xDown){ pPos.x += dy; pPos.y -= dx;}
    if (zDown){ pPos.x -= dy; pPos.y += dx;}

    if (aDown && mDown){ pRot.v -= 1;}
    if (dDown && mDown){ pRot.v += 1;}
    if (wDown && mDown){ pPos.z -= 4;}
    if (sDown && mDown){ pPos.z += 4;}

}

//-----------------------------------------------------------------------------------------------//
