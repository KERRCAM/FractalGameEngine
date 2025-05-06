#pragma once
// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define MAX_SECTORS 12
#define MAX_WALLS 12
#define FPS 30.0
#define FRAME_TIME 1000.0 / FPS
//#define WINDOW_WIDTH 3840
//#define WINDOW_HEIGHT 2160
#define WINDOW_WIDTH 1512
#define WINDOW_HEIGHT 982
#define FOV 550
#define MAX_DEMONS 10
#define MAX_BULLETS 50

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct{
    float cos[360];
    float sin[360];
} math; math M;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//
