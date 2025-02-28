// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

// LOCAL IMPORTS
#include "include/player.h"

struct vector2D playerDirection = {
    (int) 0,
    (int) 0
};

//-----------------------------------------------------------------------------------------------//

struct player player_init(){

    player.x = 50;
    player.y = 50;
    player.width = 50;
    player.height = 50;

    return player;

}

//-----------------------------------------------------------------------------------------------//

struct vector2D playerMovement(struct player *player){
    SDL_Event event;
    SDL_PollEvent(&event);



    return playerDirection;
}

//-----------------------------------------------------------------------------------------------//