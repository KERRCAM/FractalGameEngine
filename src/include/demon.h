#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "constants.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

int lastFired[MAX_DEMONS];

struct demon{

    int x;
    int y;
    int z;
    int width;
    int height;
    int scale;
    int colour;
    int hp;
    int bounty;
    float speed;
    int type;
    int distance;
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
