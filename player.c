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
    // may want to paramaterise

    player.x = 70;
    player.y = -110;
    player.z = 20;
    player.angleH = 0;
    player.angleV = 0;

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
        player.angleH -= 4;
        if (player.angleH < 0){player.angleH += 360;};
    }
    if (dDown && !mDown){
        player.angleH += 4;
        if (player.angleH > 359){player.angleH -= 360;};
    }

    int dx = M.sin[player.angleH] * 10.0;
    int dy = M.cos[player.angleH] * 10.0;

    if (wDown && !mDown){ player.x += dx; player.y += dy;}
    if (sDown && !mDown){ player.x -= dx; player.y -= dy;}

    if (xDown){ player.x += dy; player.y -= dx;}
    if (zDown){ player.x -= dy; player.y += dx;}

    if (aDown && mDown){ player.angleV -= 1;}
    if (dDown && mDown){ player.angleV += 1;}
    if (wDown && mDown){ player.z -= 4;}
    if (sDown && mDown){ player.z += 4;}

}

//-----------------------------------------------------------------------------------------------//

