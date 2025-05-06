#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS

struct demon{

    int x;
    int y;
    int z;
    int width;
    int height;
    int colour;
    int hp;
    int type;
    int distance;
    int init;

};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

struct demon newDemon(int x, int y, int z, int type, int init);

//-----------------------------------------------------------------------------------------------//
