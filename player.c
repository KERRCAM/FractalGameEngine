// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

// LOCAL IMPORTS
#include "player.h"

void player_init(){
    SDL_Rect playerCharacter = {
        (int)player.x,
        (int)player.y,
        (int)player.width,
        (int)player.height
    };


}

vector2D playerMovement(player *player){
    SDL_Event event;
    SDL_PollEvent(&event);

    vector2D playerDirection = {
        (int) 0,
        (int) 0
    }

    switch (event.type){
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_W){
                playerDirection -> y = 1;
            } else if (event.key.keysym.sym == SDLK_S){
                playerDirection -> y = -1;
            } else if (event.key.keysym.sym == SDLK_A){
                playerDirection -> x = -1;
            } else if (event.key.keysym.sym == SDLK_D){
                playerDirection -> x = 1;
            }
        break;
    }
}