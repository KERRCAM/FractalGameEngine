#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

struct bullet{

    int x;
    int y;
    int z;
    int width;
    int height;
    int colour;
    int type;
    int distance;
    int spawnTime; // Time the bullet was made
    int xSpeed;
    int ySpeed;
    int scale; // Bullet size
    int init;

};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct bullet newBullet(int x, int y, int rot, int type, int init);

void bulletSetup();

void calculatedBulletDistances();

void sortBullets();

void bulletUpdate();

//-----------------------------------------------------------------------------------------------//
