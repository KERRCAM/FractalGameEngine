// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/player.h"
#include "include/constants.h"
#include "include/vectors.h"

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

int detectCollision(struct vector2D pc, struct vector2D pn, struct vector2D w1, struct vector2D w2){

    int c1 = crossProduct2D(pc, w1, w2);
    int c2 = crossProduct2D(pn, w1, w2);

    if ((c1 == 1 && c2 == -1) || (c1 == -1 && c2 == 1)) {
        return 1;
    } else {
        return 0;
    }

}

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

    float movX = 0;
    float movY = 0;

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

    if (wDown){ movX += dx; movY += dy;}
    if (sDown){ movX -= dx; movY -= dy;}
    if (dDown){ movX += dy * 1.2; movY -= dx * 1.2;}
    if (aDown){ movX -= dy * 1.2; movY += dx * 1.2;}

    float newX = pPos.x + movX;
    float newY = pPos.y + movY;
    if (detectCollision(newVector2D(pPos.x, pPos.y), newVector2D(newX, newY), newVector2D(nearWall.x1, nearWall.y1), newVector2D(nearWall.x2, nearWall.y2)) == 0){
        pPos.x += movX;
        pPos.y += movY;
    }

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
