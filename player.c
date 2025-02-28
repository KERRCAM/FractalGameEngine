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
    player.width = 100;
    player.height = 100;

    return player;

}

//-----------------------------------------------------------------------------------------------//

struct vector2D playerMovement(struct player *player){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_KEYDOWN:
            printf("%s", "key pressed\n");
            if (event.key.keysym.sym == SDLK_w){
                printf("%s", "w pressed\n");
                playerDirection.y = 1;
            } else if (event.key.keysym.sym == SDLK_s){
                playerDirection.y = -1;
            } else if (event.key.keysym.sym == SDLK_a){
                playerDirection.x = -1;
            } else if (event.key.keysym.sym == SDLK_d){
                playerDirection.x = 1;
            }
        break;
    }

    return playerDirection;
}

//-----------------------------------------------------------------------------------------------//