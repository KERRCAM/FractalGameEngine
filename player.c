// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

// LOCAL IMPORTS
#include "include/player.h"

//-----------------------------------------------------------------------------------------------//

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;
int playerX = 0;
int playerY = 0;

//-----------------------------------------------------------------------------------------------//

void playerSetup(){
    // may want to paramaterise

    player.x = 50;
    player.y = 50;
    player.width = 50;
    player.height = 50;

}

//-----------------------------------------------------------------------------------------------//

void playerInput(SDL_Event event){

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_w:
                wDown = true;
            break;
            case SDLK_s:
                sDown = true;
            break;
            case SDLK_a:
                aDown = true;
            break;
            case SDLK_d:
                dDown = true;
            break;
        }
    }

    if (event.type == SDL_KEYUP){
        switch (event.key.keysym.sym){
            case SDLK_w:
                wDown = false;
            case SDLK_s:
                sDown = false;
            case SDLK_a:
                aDown = false;
            case SDLK_d:
                dDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void playerUpdate(float deltaTime){
    // may want to paramaterise speed values for x and y (or one overall for linear movement)

    if (wDown){
        playerY = -50;
    } else if (sDown){
        playerY = 50;
    } else{
        playerY = 0;
    }

    if (aDown){
        playerX = -50;
    } else if (dDown){
        playerX = 50;
    } else{
        playerX = 0;
    }

    player.x += playerX * deltaTime;
    player.y += playerY * deltaTime;

}

//-----------------------------------------------------------------------------------------------//

void playerRender(SDL_Renderer* renderer){
    // could paramaterise colour but liekly to change to sprite or something later anyway

    SDL_Rect playerRect = {
        (int)player.x,
        (int)player.y,
        (int)player.width,
        (int)player.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);

}

//-----------------------------------------------------------------------------------------------//