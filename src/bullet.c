// LIBRARY IMPORTS
#include <SDL2/SDL.h>

// LOCAL IMPORTS
#include "include/bullet.h"
#include "include/constants.h"

//-----------------------------------------------------------------------------------------------//

struct bullet newBullet(int x, int y, int rot, int type, int init){

    struct bullet b;

    b.x = x;
    b.y = y;
    b.z = 40;
    b.width = 20;
    b.height = 20;

    if (type == 1){
        b.colour = 4;
    } else {
        b.colour = 7;
    }

    b.scale = 5;
    b.distance = 0;
    b.spawnTime = SDL_GetTicks();
    b.xSpeed = 10 * M.sin[rot];
    b.ySpeed = 10 * M.cos[rot];
    b.init = init;

    return b;

}

//-----------------------------------------------------------------------------------------------//
