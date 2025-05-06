// LIBRARY IMPORTS
#include <SDL2/SDL.h>

// LOCAL IMPORTS
#include "include/bullet.h"
#include "include/constants.h"

//-----------------------------------------------------------------------------------------------//

struct bullet newBullet(int x, int y, int rot, int init){

    struct bullet b;

    b.x = x;
    b.y = y;
    b.z = 40;
    b.width = 20;
    b.height = 20;
    b.colour = 7;
    b.distance = 0;
    b.spawnTime = SDL_GetTicks();
    b.xSpeed = 20 * M.sin[rot];
    b.ySpeed = 20 * M.cos[rot];
    b.init = init;

    return b;

}

//-----------------------------------------------------------------------------------------------//
