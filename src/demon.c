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

// Set locations that demons can spawn at - roughly works out to 2 spots for eahc 4 quadrents.
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
    /*
    Demon struct constructor.
    */

    struct demon d;

    d.x = x;
    d.y = y;
    d.z = z;

    // Assigns some values based on the demon type.
    if (type == 1){
        d.width = 50;
        d.height = 80;
        d.colour = 5;
        d.hp = 100;
        d.scale = 2;
        d.bounty = 200;
        d.speed = 0.18;
    } else if (type == 2){
        d.width = 35;
        d.height = 80;
        d.colour = 4;
        d.hp = 60;
        d.scale = 3;
        d.bounty = 120;
        d.speed = 0.3;
    }

    d.type = type;
    d.distance = 0;
    d.lastFired = SDL_GetTicks();
    d.init = init;

    return d;

}

//-----------------------------------------------------------------------------------------------//

void demonSetup(){
    /*
    Demon setup function.
    Fills demon array with nulls and sets the spawn rates.
    */

    lastSpawned = -1;
    spawnRate = INITIAL_SPAWN_RATE;

    for (int d = 0; d < MAX_DEMONS; d++){
        demons[d] = newDemon(-1, -1, -1, -1, 0);
    }

}

//-----------------------------------------------------------------------------------------------//

int checkPlayerBulletProximity(struct demon* d){
    /*
    Checks if teh given demon is being hit by any player bullets,
    if so deleting the bullet and return if there was a hit or not for damage.
     */

    for (int b = 0; b < MAX_BULLETS; b++){

        if (bullets[b].init == 0){ continue;}
        if (bullets[b].type != 1){ continue;} // Checks the bullet is a player bullet.

        // Checks if bullet is hitting the deomon.
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
    /*
    Checks if a demon needs spawned.
    If so it picks a random spawn location and demon type.
    Spawn is deffered if demons is full.
    */

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
    /*
    Checks if the demon has line of sight on the player by checking dot products with the demon,
    player and walls.
    If the demon can see the playe they move towards them at a speed dependant on their type.
    */

    if (d -> init == 0){
        return;
    }

    int lineOfSight = 1;

    // Loop checking for line of sight on the player.
    for (int w = 0; w < wallsSize; w++){
        struct vector2D pl = newVector2D(pPos.x, pPos.y);
        struct vector2D dp = newVector2D(d -> x, d -> y);
        if (allWalls[w] -> init == 0){ continue;}
        if (detectCollision(pl, dp, newVector2D(allWalls[w] -> x1, allWalls[w] -> y1),
                            newVector2D(allWalls[w] -> x2, allWalls[w] -> y2)) == 1){
            lineOfSight = 0;
        }

    }

    // Applies movement if their is line of sight.
    if (lineOfSight == 1){
        int dx = pPos.x - d -> x;
        int dy = pPos.y - d -> y;

        d -> x += dx * deltaTime * d -> speed;
        d -> y += dy * deltaTime * d -> speed;
    }

}

//-----------------------------------------------------------------------------------------------//

void calculateDemonDistances(){
    /*
    Calcualted distnaces to from each demon to the player so they can be rendered in the correct
    order.
    Also make calls to their movement function to see if their position is to change first.
    Also checks if they are being hit by a bullet and if they die to that bullet.
    Done here for efficiency sakes.
    Also handles demons shooting.
     */

    int px = round(pPos.x);
    int py = round(pPos.y);
    int ph = round(pRot.h);

    // Looping over all demons
    for (int i = 0; i < MAX_DEMONS; i++){
        moveDemon(&demons[i], px, py, ph); // Position update

        if (demons[i].init == 0){ // Sets uninitialised demons to max distance.
            demons[i].distance = 999999999;
        } else {
            if (checkPlayerBulletProximity(&demons[i])){ // Checks bullet hits.
                demons[i].hp -= 10; // Takes damge if there was a hit.
                if (demons[i].hp <= 0){
                    score += demons[i].bounty;
                    demons[i] = newDemon(-1, -1, -1, -1, 0); // Resets demon if they died.
                    demons[i].distance = 999999999;
                }
            }
            // New distance calculation.
            demons[i].distance = euclidianDistance2D(   newVector2D(px, py),
                                                        newVector2D(demons[i].x, demons[i].y));
            if (demons[i].distance < 100){
                if (demons[i].type == 1){
                    pHP -= 0.1;
                } else {
                    pHP -= 0.25;
                }
            }
            // Type one demons can shoot player if bullet isnt full.
            if (demons[i].type == 1 && bullets[0].init == 0){
                int rot = ph + 180; if (rot > 359){ rot -= 360;}
                if (SDL_GetTicks() - demons[i].lastFired > 1000){
                    bullets[0] = newBullet(demons[i].x, demons[i].y, rot, 2, 1);
                    demons[i].lastFired = SDL_GetTicks();
                }
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void sortDemons(){
    /*
    Sorts demons by distance to player for renering order reasons.
    */

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
    /*
    Calls demon update functions.
    */

    spawnDemon();
    calculateDemonDistances();
    sortDemons();

}

//-----------------------------------------------------------------------------------------------//
