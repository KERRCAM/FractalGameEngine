#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS


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
    int scale;
    int colour;
    int hp;
    int bounty;
    int type;
    int distance;
    int init;

};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct demon newDemon(int x, int y, int z, int type, int init);

//-----------------------------------------------------------------------------------------------//
