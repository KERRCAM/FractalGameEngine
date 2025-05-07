// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/characters.h"
#include "include/player.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//

void drawNumber(SDL_Renderer* renderer, int xPos, int yPos, int n){
    /*
    Draws a number 0 - 150 (Also has 3 letter layout for HP=, SCO and RE=) from a texture map.
    Map is for single pixels so we scale the characters up.

    This is from 3D sages doom tutorial, i only added the scaling.
    */

    int x,y;
    int characterSize = 15;

    // Loop over the texture map for x and y values.
    for (y = 0; y < 5; y++){
        int y2 = ((5 - y - 1) + 5 * n) * 3 * 12;

        for(x = 0; x < 12; x++){
            int x2 = x * 3;
            if(CHARACTERS[y2 + x2] == 0){ continue;}
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            int currX = xPos + (characterSize * x);
            int currY = yPos - (characterSize * y) + 100;

            for (int p = 0; p < characterSize; p++){ // Extra loop for scaling
                SDL_RenderDrawLine(renderer, x + currX + p, y + currY, x + currX + p, y + currY + characterSize);
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void renderScore(SDL_Renderer* renderer){
    /*
    Handles the draw calls and positioning for score display.
    */

    // Draws SCORE=
    drawNumber(renderer, 10, -30, 152);
    drawNumber(renderer, 200, -30, 153);

    float timeSurvived;

    // Calculates the current score as score + time survived.
    // Also has condition for time of death - start time for after the game has ended.
    if (pHP > 0){
        timeSurvived = SDL_GetTicks() - gameStartTime;
    } else {
        timeSurvived = timeOfDeath - gameStartTime;
    }
    int survivalScore = timeSurvived / 1000.0;
    int scoreToScreen = score + survivalScore;

    // Score prints.
    if (scoreToScreen < 1000){
        drawNumber(renderer, 333, -30, scoreToScreen / 10);
        drawNumber(renderer, 400, -30, scoreToScreen % 10);
    } else if (scoreToScreen < 10000){
        drawNumber(renderer, 333, -30, scoreToScreen / 100);
        int r = scoreToScreen % 100;
        if (r < 10){
            drawNumber(renderer, 400, -30, 0);
            drawNumber(renderer, 467, -30, r);
        } else {
            drawNumber(renderer, 467, -30, scoreToScreen % 100);
        }

    }


}

//-----------------------------------------------------------------------------------------------//

void renderHP(SDL_Renderer* renderer){
    /*
    Handles the draw calls and positioning for HP display.
    */

    // Draws HP=
    drawNumber(renderer, 10, 60, 151);

    drawNumber(renderer, 200, 60, round(pHP));

}

//-----------------------------------------------------------------------------------------------//

void renderUI(SDL_Renderer* renderer){
    /*
    Function for handling all UI draw calls.
    */

    renderScore(renderer);
    renderHP(renderer);

}

//-----------------------------------------------------------------------------------------------//
