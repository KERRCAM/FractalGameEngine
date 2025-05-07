// LIBRARY IMPORTS
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/bullet.h"
#include "include/constants.h"
#include "include/vectors.h"
#include "include/player.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//

struct bullet newBullet(int x, int y, int rot, int type, int init){

    struct bullet b;

    b.x = x;
    b.y = y;
    b.z = 40;
    b.width = 20;
    b.height = 20;

    if (type == 1){
        b.colour = 1;
    } else {
        b.colour = 0;
    }

    b.scale = 5;
    b.distance = 0;
    b.spawnTime = SDL_GetTicks();
    b.xSpeed = 250 * M.sin[rot] * deltaTime;
    b.ySpeed = 250 * M.cos[rot] * deltaTime;
    b.init = init;

    return b;

}

//-----------------------------------------------------------------------------------------------//

void bulletSetup(){

    for (int b = 0; b < MAX_BULLETS; b++){
        bullets[b] = newBullet(-1, -1, -1, -1, 0);
    }

}
//-----------------------------------------------------------------------------------------------//

void calculatedBulletDistances(){

    int px = round(pPos.x);
    int py = round(pPos.y);

    for (int i = 0; i < MAX_BULLETS; i++){
        if (bullets[i].init == 0){
            bullets[i].distance = 999999999;
        } else if (SDL_GetTicks() - bullets[i].spawnTime > 5000){
            bullets[i] = newBullet(-1, -1, -1, -1, 0);
            bullets[i].distance = 999999999;
        } else  {
            bullets[i].x += bullets[i].xSpeed;
            bullets[i].y += bullets[i].ySpeed;

            bullets[i].distance = euclidianDistance2D(  newVector2D(px, py),
                                                        newVector2D(bullets[i].x, bullets[i].y));
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void sortBullets(){

    for (int i = 0; i < MAX_BULLETS; i++){
        for (int j = 0; j < MAX_BULLETS - i - 1; j++){
            if ((bullets[j].distance < bullets[j + 1].distance)){
                struct bullet b = bullets[j];
                bullets[j] = bullets[j + 1];
                bullets[j + 1] = b;
            }
        }
    }

}


//-----------------------------------------------------------------------------------------------//

void bulletUpdate(){

    calculatedBulletDistances();
    sortBullets();

}

//-----------------------------------------------------------------------------------------------//
