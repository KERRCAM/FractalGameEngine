#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct bullet{

    int x;
    int y;
    int z;
    int width;
    int height;
    int colour;
    int type;
    int distance;
    int spawnTime;
    int xSpeed;
    int ySpeed;
    int init;

};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct bullet newBullet(int x, int y, int rot, int type, int init);

//-----------------------------------------------------------------------------------------------//
