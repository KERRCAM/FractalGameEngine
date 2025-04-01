// LIBRARY IMPORTS


// LOCAL IMPORTS
#pragma once


//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define MAX_SECTORS 32
#define MAX_WALLS 12
#define FPS 30.0
#define FRAME_TIME 1000.0 / FPS
// #define WINDOW_WIDTH 3840
// #define WINDOW_HEIGHT 2160
#define WINDOW_WIDTH 1512
#define WINDOW_HEIGHT 982
#define FOV 550

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct{
    float cos[360];
    float sin[360];
} math; math M;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//
