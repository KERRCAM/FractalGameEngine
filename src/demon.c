// LIBRARY IMPORTS
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/demon.h"
#include "include/globals.h"
#include "include/constants.h"
#include "include/player.h"

//-----------------------------------------------------------------------------------------------//

int SPAWN_LOCATIONS[8][2] = {
    {400, 400},
    {600, 600},
    {400, 1620},
    {600, 1500},
    {2600, 600},
    {2880, 400},
    {2700, 1550},
    {2880, 1620},
};

//-----------------------------------------------------------------------------------------------//

struct demon newDemon(int x, int y, int z, int type, int init){

    struct demon d;

    d.x = x;
    d.y = y;
    d.z = z;

    if (type == 1){
        d.width = 50;
        d.height = 80;
        d.colour = 5;
        d.hp = 100;
        d.scale = 2;
        d.bounty = 200;
    } else if (type == 2){
        d.width = 35;
        d.height = 80;
        d.colour = 4;
        d.hp = 60;
        d.scale = 3;
        d.bounty = 120;
    }

    d.type = type;
    d.distance = 0;
    d.init = init;

    return d;

}

//-----------------------------------------------------------------------------------------------//

void demonSetup(){

    lastSpawned = -1;
    spawnRate = INITIAL_SPAWN_RATE;

    for (int d = 0; d < MAX_DEMONS; d++){
        demons[d] = newDemon(-1, -1, -1, -1, 0);
    }

    struct demon test = newDemon(400, 400, 80, 1, 1);
    demons[0] = test;

}

//-----------------------------------------------------------------------------------------------//

int checkPlayerBulletProximity(struct demon* d){

    for (int b = 0; b < MAX_BULLETS; b++){

        if (bullets[b].init == 0){ continue;}

        if (euclidianDistance2D(newVector2D(bullets[b].x, bullets[b].y),
                                newVector2D(d -> x, d -> y))  < d -> width){
            bullets[b] = newBullet(-1, -1, -1, -1, 0);
            return 1;
        }

    }

    return 0;

}

//-----------------------------------------------------------------------------------------------//

void spawnDemon(){

    if (lastSpawned == -1 || SDL_GetTicks() - lastSpawned > spawnRate){

        int pos = rand() % 8;
        int type = (rand() % 2) + 1;

        if (demons[0].init != 1){
            demons[0] = newDemon(SPAWN_LOCATIONS[pos][0], SPAWN_LOCATIONS[pos][1], 80, type, 1);
        }

        spawnRate -= 1000; if (spawnRate < MAX_SPAWN_RATE) { spawnRate = MAX_SPAWN_RATE;}
        lastSpawned = SDL_GetTicks();
    }

}

//-----------------------------------------------------------------------------------------------//

void moveDemon(struct demon* d, int px, int py, int ph){

    int lineOfSight = 1;

    for (int w = 0; w < wallsSize; w++){
        struct vector2D pl = newVector2D(pPos.x, pPos.y);
        struct vector2D dp = newVector2D(d -> x, d -> y);
        if (allWalls[w] -> init == 0){ continue;} // euclidianDistance2D(pl, dp) < 300.0 &&
        if (detectCollision(pl, dp, newVector2D(allWalls[w] -> x1, allWalls[w] -> y1),
                            newVector2D(allWalls[w] -> x2, allWalls[w] -> y2)) == 1){
            lineOfSight = 0;
        }

    }



    if (lineOfSight == 1){
        int dx = pPos.x - d -> x;
        int dy = pPos.y - d -> y;

        d -> x += dx * deltaTime * 0.3;
        d -> y += dy * deltaTime * 0.3;
    }

}

//-----------------------------------------------------------------------------------------------//

void calculateDemonDistances(){

    int px = round(pPos.x);
    int py = round(pPos.y);
    int ph = round(pRot.h);

    for (int i = 0; i < MAX_DEMONS; i++){
        moveDemon(&demons[i], px, py, ph);

        if (demons[i].init == 0){
            demons[i].distance = 999999999;
        } else {
            if (checkPlayerBulletProximity(&demons[i])){
                demons[i].hp -= 10;
                if (demons[i].hp <= 0){
                    score += demons[i].bounty;
                    demons[i] = newDemon(-1, -1, -1, -1, 0);
                    demons[i].distance = 999999999;
                }
            }
            demons[i].distance = euclidianDistance2D(   newVector2D(px, py),
                                                        newVector2D(demons[i].x, demons[i].y));
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void sortDemons(){

    for (int i = 0; i < MAX_DEMONS; i++){
        for (int j = 0; j < MAX_DEMONS - i - 1; j++){
            if ((demons[j].distance < demons[j + 1].distance)){
                struct demon d = demons[j];
                demons[j] = demons[j + 1];
                demons[j + 1] = d;
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void demonUpdate(){

    spawnDemon();
    calculateDemonDistances();
    sortDemons();

}

//-----------------------------------------------------------------------------------------------//