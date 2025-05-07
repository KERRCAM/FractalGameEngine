// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/player.h"
#include "include/constants.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;
bool mDown = false;
bool leftDown = false;
bool rightDown = false;
bool spaceDown = false;
bool canShoot = false;

//-----------------------------------------------------------------------------------------------//

void playerSetup(){

    pPos.x = 250;
    pPos.y = 250;
    pPos.z = 40;

    pRot.h = 0;
    pRot.v = 0;

    inAir = false;
    nearWall = NULL;

    pHP = 150;
    score = 0;

}

//-----------------------------------------------------------------------------------------------//

int detectCollision(struct vector2D pc, struct vector2D pn, struct vector2D w1, struct vector2D w2){

    int c1 = crossProduct2D(pc, w1, w2);
    int c2 = crossProduct2D(pn, w1, w2);

    if (c1 != c2
        && (euclidianDistance2D(pn,w1) < euclidianDistance2D(w1,w2))
        && (euclidianDistance2D(pn,w2) < euclidianDistance2D(w1,w2))
        ){
        return 1;
    } else {
        return 0;
    }

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
            case SDLK_UP:
                if (SDL_GetTicks() - lastBullet > 800){ lastBullet = SDL_GetTicks();}
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

int playerUpdate(float deltaTime){

    if (pHP <= 0){
        return 0;
    }

    float movX = 0;
    float movY = 0;

    float dx = M.sin[(int)pRot.h] * 150.0 * deltaTime;
    float dy = M.cos[(int)pRot.h] * 150.0 * deltaTime;

    if (SDL_GetTicks() - dashTime < 200){
        dx *= 6;
        dy *= 6;
    }

    if (SDL_GetTicks() - lastBullet < 100){
        if (bullets[0].init == 0){
            bullets[0] = newBullet(pPos.x, pPos.y, pRot.h, 1, 1);
        }

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

    if (nearWall != NULL && detectCollision(newVector2D(pPos.x, pPos.y), newVector2D(newX, newY),
                                            newVector2D(nearWall->x1, nearWall->y1),
                                            newVector2D(nearWall->x2, nearWall->y2)) == 0){
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

    return 1;

}

//-----------------------------------------------------------------------------------------------//
