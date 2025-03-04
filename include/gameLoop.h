//-----------------------------------------------------------------------------------------------//
//CONSTANTS

#define numSect 4
#define numWall 16
#define FPS 30.0
#define FRAME_TIME 1000.0 / FPS
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct{
    float cos[360];
    float sin[360];
} math; math M;

typedef struct {
    int x1, y1;
    int x2, y2;
    int c; // colour
}walls; walls W[30];

typedef struct {
    int ws, we;
    int z1, z2;
    int d;
    int c1, c2;
    int surf[WINDOW_WIDTH];
    int surface;
}sectors; sectors S[30];

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

//-----------------------------------------------------------------------------------------------//







