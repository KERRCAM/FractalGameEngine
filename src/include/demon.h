#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "constants.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

struct demon{

    int x;
    int y;
    int z;
    int width;
    int height;
    int scale; // Size of the demon.
    int colour;
    int hp;
    int bounty; // Score the player gets for killing the demon.
    float speed;
    int type; // Demon type, melee or ranged.
    int distance;
    int lastFired; // Time the demon last fired their weapon.
    int init;

};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct demon newDemon(int x, int y, int z, int type, int init);

void demonSetup();

void spawnDemon();

void moveDemon(struct demon* d, int px, int py, int ph);

int checkPlayerBulletProximity(struct demon* d);

void calculateDemonDistances();

void sortDemons();

void demonUpdate();

//-----------------------------------------------------------------------------------------------//
