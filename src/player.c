// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/player.h"
#include "include/constants.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//
// Key press triggers

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
    /*
    Initialisations for player attributes.
    */

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

void playerInput(SDL_Event event){
    /*
    Handles player key input.
    */

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
            case SDLK_DOWN:
                if (SDL_GetTicks() - lastHeal > 20000){ lastHeal = SDL_GetTicks();}
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

int detectCollision(struct vector2D pc, struct vector2D pn,
                    struct vector2D w1, struct vector2D w2){
    /*
    Checks if a collision will occur between a players current position, thier next postion
    and a wall, normally the closest wall is used for this.
    */

    // Cross product is calculated for the wall and player postions.
    // This gives us the side of the wall the points are on.
    int c1 = crossProduct2D(pc, w1, w2);
    int c2 = crossProduct2D(pn, w1, w2);

    // If the points are on opposite sides of the wall then it means a collision will occur.
    // We also check the player proximity to the wall as the cross product acts as if the wall
    // extends for infintiy in both directions.
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

void checkDemonBulletProximity(){
    /*
    Checks if the player is hit by a demon bullet, if so the bullet is delted and the
    player takes damage.
     */

    for (int b = 0; b < MAX_BULLETS; b++){

        if (bullets[b].init == 0){ continue;}
        if (bullets[b].type != 2){ continue;} // Checks the bullet isnt from the player.

        if (euclidianDistance2D(newVector2D(bullets[b].x, bullets[b].y),
                                newVector2D(round(pPos.x), round(pPos.y)))  < 60){
            bullets[b] = newBullet(-1, -1, -1, -1, 0); // Replaces the bullet hit with a null one.
            pHP -= 10;
        }

    }

}

//-----------------------------------------------------------------------------------------------//

int playerUpdate(float deltaTime){
    /*
    Main function to handle all player updates.
    Acts on all currently registered key presses for movement.
    Also calls other functions for collision and hit registration.
     */

    checkDemonBulletProximity();

    float movX = 0;
    float movY = 0;

    // Calculates movement for x and y directions.
    // Note: 170 is the effective movement speed.
    float dx = M.sin[(int)pRot.h] * 170.0 * deltaTime;
    float dy = M.cos[(int)pRot.h] * 170.0 * deltaTime;

    // Checks if player is dashing and boosts their speed if so.
    if (SDL_GetTicks() - dashTime < 200){
        dx *= 6;
        dy *= 6;
    }

    // Checks if the player is shooting and spawns new bullet if so.
    if ((SDL_GetTicks() - lastBullet < 100) && (bullets[0].init == 0)){
        bullets[0] = newBullet(pPos.x, pPos.y, pRot.h, 1, 1);
    }

    // Checks if the player is heal and heals the player if so.
    if (SDL_GetTicks() - lastHeal < 100){
        pHP += 20; if (pHP > 150){pHP = 150;}
    }

    // Jump handling
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

    // Horizontal movement handling
    if (wDown){ movX += dx; movY += dy;}
    if (sDown){ movX -= dx; movY -= dy;}
    if (dDown){ movX += dy * 1.2; movY -= dx * 1.2;}
    if (aDown){ movX -= dy * 1.2; movY += dx * 1.2;}

    // Gets the next position of the player to be used for a collision check.
    float newX = pPos.x + movX;
    float newY = pPos.y + movY;

    // Collision check, new position only applied if we pass the check.
    if (nearWall != NULL && detectCollision(newVector2D(pPos.x, pPos.y), newVector2D(newX, newY),
                                            newVector2D(nearWall->x1, nearWall->y1),
                                            newVector2D(nearWall->x2, nearWall->y2)) == 0){
        pPos.x += movX;
        pPos.y += movY;
    }

    // horizontal rotation (look controls) handling.
    if (leftDown){
        pRot.h -= 120 * deltaTime;
        if (pRot.h < 0){pRot.h += 360;};
    }
    if (rightDown){
        pRot.h += 120 * deltaTime;
        if (pRot.h > 359){pRot.h -= 360;};
    }

    if (pHP <= 0){
        return 0;
    }

    return 1;

}

//-----------------------------------------------------------------------------------------------//
