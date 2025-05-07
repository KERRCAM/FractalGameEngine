// LIBRARY IMPORTS
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/draw.h"
#include "include/player.h"
#include "../levels/level3.h"
#include "../editor/include/levels.h"
#include "include/colours.h"
#include "include/demon.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//

// Working level struct while the game is running
// Level structs are split into sectors each contains walls.
struct level l;

//-----------------------------------------------------------------------------------------------//

void drawSetup(){
    /*
    Loads the selected level information into the working level struct.
    Also loads all the walls into the overall walls array and calculates it size.
    */

    struct level l1 = newLevel(0, 0, 0, 1);
    l = l1;

    // Loading sector and wall information into the levels struct.
    for (int i = 0; i < MAX_SECTORS; i++){
        l.levelSectors[i].minZ = sectors[i][0];
        l.levelSectors[i].maxZ = sectors[i][1];
        l.levelSectors[i].floorColour = sectors[i][2];
        l.levelSectors[i].ceilingColour = sectors[i][3];
        l.levelSectors[i].init = sectors[i][4];
        l.levelSectors[i].mpx = sectors[i][5];
        l.levelSectors[i].mpy = sectors[i][6];

        for (int j = 0; j < MAX_WALLS; j++){
            l.levelSectors[i].sectorWalls[j].x1 = walls[i][j][0];
            l.levelSectors[i].sectorWalls[j].y1 = walls[i][j][1];
            l.levelSectors[i].sectorWalls[j].x2 = walls[i][j][2];
            l.levelSectors[i].sectorWalls[j].y2 = walls[i][j][3];
            l.levelSectors[i].sectorWalls[j].colour = walls[i][j][4];
            l.levelSectors[i].sectorWalls[j].init = walls[i][j][5];
        }

        l.levelSectors[i].closestWall = l.levelSectors[i].sectorWalls[0];
    }

    int pos = 0;
    // walls array being filled
    for (int s = 0; s < MAX_SECTORS; s++){
        for (int w = 0; w < MAX_WALLS ; w++){
            allWalls[pos] = &l.levelSectors[s].sectorWalls[w];
            pos++;
        }
    }

    wallsSize = (sizeof(allWalls) / sizeof(allWalls[0]));

}

//-----------------------------------------------------------------------------------------------//

void drawEntity(SDL_Renderer* renderer, int width, int height, int x, int y, int colour, int init){
    /*
    Draw function used for demons and bullets.
    Differs slightly from wall drawing.
    */

    // We dont draw if the entity is uninitialised.
    if (init == 0){
        return;
    }

    // Getting int version of player float values.
    int px = round(pPos.x);
    int py = round(pPos.y);
    int pz = round(pPos.z);
    int pv = round(pRot.v);
    int ph = round(pRot.h);

    int wx[4], wy[4], wz[4];
    float CS = M.cos[ph], SN = M.sin[ph];

    int angle = ph + 90; if (angle > 359){ angle -= 360;}

    // Adjusting draw angles so the entity always faces the player view.
    float xComp = M.sin[(ph + 90) % 360];
    float yComp = M.cos[(ph + 90) % 360];

    // Setting size of enetity.
    int offX = (width * xComp) / 2;
    int offY = (height * yComp) / 2;

    int x1 = x - offX - px;
    int y1 = y - offY - py;
    int x2 = x + offX - px;
    int y2 = y + offY - py;

    // Adjusting perspective.
    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;
    wx[2] = wx[0];
    wx[3] = wx[1];

    wy[0] = y1 * CS + x1 * SN;
    wy[1] = y2 * CS + x2 * SN;
    wy[2] = wy[0];
    wy[3] = wy[1];

    wz[0] = 0 - pz + (pv * wy[0]) / 32.0;
    wz[1] = 0 - pz + (pv * wy[1]) / 32.0;
    wz[2] = wz[0] + height;
    wz[3] = wz[1] + height;

    // if the entity is out of view we dont draw.
    if (wy[0] < 1 && wy[1] < 1){ return;}

    // Clipping checks
    if (wy[0] < 1){
        clip(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);
        clip(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);
    }

    if (wy[1] < 1){
        clip(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);
        clip(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);
    }

    wx[0] = wx[0] * FOV / wy[0] + (WINDOW_WIDTH / 2);
    wy[0] = wz[0] * FOV / wy[0] + (WINDOW_HEIGHT / 2);
    wx[1] = wx[1] * FOV / wy[1] + (WINDOW_WIDTH / 2);
    wy[1] = wz[1] * FOV / wy[1] + (WINDOW_HEIGHT / 2);
    wx[2] = wx[2] * FOV / wy[2] + (WINDOW_WIDTH / 2);
    wy[2] = wz[2] * FOV / wy[2] + (WINDOW_HEIGHT / 2);
    wx[3] = wx[3] * FOV / wy[3] + (WINDOW_WIDTH / 2);
    wy[3] = wz[3] * FOV / wy[3] + (WINDOW_HEIGHT / 2);

    drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], colour);

}

//-----------------------------------------------------------------------------------------------//

float minDistance(int px, int py, int x1, int y1, int x2, int y2){
    /*
    Calculates the minimum distance between the player and wall.
    This is done by taking distance from the player to a sample of points along the
    wall and returning the smallest value amongst these.
    */

    // Calculating itervals.
    float min = -1;
    float intx = abs(x1 - x2) / 10.0;
    float inty = abs(y1 - y2) / 10.0;
    float cx, cy;
    float ex, ey;

    // Calculating start and end values for our loop.
    if (x1 < x2){
        cx = x1;
        ex = x2;
    } else {
        cx = x2;
        ex = x1;
    }

    if (y1 < y2){
        cy = y1;
        ey = y2;
    } else{
        cy = y2;
        ey = y1;
    }

    // Loops along the wall calculating distance to a new sample point each loop.
    while (cx < ex || cy < ey){
        float newDistance = euclidianDistance2D(newVector2D(px, py), newVector2D(cx, cy));
        if (newDistance < min || min == -1){
            min = newDistance;
        }
        cx += intx;
        cy += inty;
    }

    return min;
}

//-----------------------------------------------------------------------------------------------//

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2){
    /*
    Adjusts values for clipping to prevent rendering artefacts.
    */

    float da = *y1;
    float db = y2;
    float d = da - db;

    if (d == 0){ d = 1;}

    float s = da / d;
    *x1 = *x1 + s*(x2 - (*x1));
    *y1 = *y1 + s*(y2 - (*y1));

    if (*y1 == 0){ *y1 = 1;}
    *z1 = *z1 + s*(z2 - (*z1));

}

//-----------------------------------------------------------------------------------------------//

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int colour){
    /*
    Function for drawing walls or entities from given values.
    Done by drawing a sequence of straight vertical lines.
    */

    SDL_SetRenderDrawColor( renderer, colours[colour][0],
                            colours[colour][1], colours[colour][2], 255);

    int x;

    // Calculating base and top diffs.
    int dyb = b2 - b1;
    int dyt = t2 - t1;

    int dx = x2 - x1;
    if (dx == 0){ dx = 1;}
    int xs = x1;

    // Checks if values will go off the window.
    if (x1 < 0){ x1 = 0;}
    if (x2 < 0){ x2 = 0;}
    if (x1 > WINDOW_WIDTH){ x1 = WINDOW_WIDTH;}
    if (x2 > WINDOW_WIDTH){ x2 = WINDOW_WIDTH;}

    // Loop for drawing the lines that make up the wall.
    for (x = x1; x < x2; x++){
        int y1 = dyb * (x - xs + 0.5) / dx + b1;
        int y2 = dyt * (x - xs + 0.5) / dx + t1;

        if (y1 < 0){ y1 = 0;}
        if (y2 < 0){ y2 = 0;}
        if (y1 > WINDOW_HEIGHT){ y1 = WINDOW_HEIGHT;}
        if (y2 > WINDOW_HEIGHT){ y2 = WINDOW_HEIGHT;}

        SDL_RenderDrawLine(renderer, x, y1, x, y2);

    }
}

//-----------------------------------------------------------------------------------------------//

void floors(SDL_Renderer* renderer){
    /*
    Floor drwaing function.
    Done pixel by pixel rather than line by line to give better perspective with colours.
    */

    // Calcautes required values.
    int x;
    int y;
    int xo = WINDOW_WIDTH / 2;
    int yo = WINDOW_HEIGHT / 2;
    float upDown = pRot.v * 2; if (upDown > WINDOW_HEIGHT){upDown = WINDOW_HEIGHT;}
    int ph = round(pRot.h);
    float scale = 0.25;

    // Double loop for x and y to draw each pixel.
    for (y = upDown; y < yo; y += 2){
        for (x = -xo; x < xo; x += 2){
            float z = y + upDown; if (z == 0){ z = 0.0001;}
            float fx = x / z * scale;
            float fy = (float)FOV / z * scale;

            // So the floor stays fixed and doesnt rotate with the player.
            float rx = fx * M.cos[ph] + fy * M.sin[ph] + (pPos.x / 160.0);
            float ry = fx * M.sin[ph] - fy * M.cos[ph] - (pPos.y / 160.0);

            // Conditions position to work out colour.
            if (rx < 0){ rx = -rx + 1;}
            if (ry < 0){ ry = -ry + 1;}
            if ((int)rx % 2 == (int)ry % 2){
                SDL_SetRenderDrawColor(renderer, 0, 130, 0, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            } else{
                SDL_SetRenderDrawColor(renderer, 120, 120, 60, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void ceilings(SDL_Renderer* renderer){
    /*
    Very similar to floor drawing, mainly changes in rotations and positioning.
    */

    int x;
    int y;
    int xo = WINDOW_WIDTH / 2;
    int yo = WINDOW_HEIGHT / 2;
    float upDown = pRot.v * 2; if (upDown > WINDOW_HEIGHT){upDown = WINDOW_HEIGHT;}
    int ph = round(pRot.h);
    float scale = 0.25;

    for (y = -yo; y < -upDown; y += 2){
        for (x = -xo; x < xo; x += 2){
            float z = y + upDown; if (z == 0){ z = 0.0001;}
            float fx = x / z * scale;
            float fy = (float)FOV / z * scale;
            float rx = fx * M.sin[ph] - fy * M.cos[ph] + (pPos.y / 160.0);
            float ry = fx * M.cos[ph] + fy * M.sin[ph] - (pPos.x / 160.0);

            if (rx < 0){ rx = -rx + 1;}
            if (ry < 0){ ry = -ry + 1;}
            if ((int)rx % 2 == (int)ry % 2){
                SDL_SetRenderDrawColor(renderer, 255, 0, 60, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            } else{
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void wallSetup(SDL_Renderer* renderer, int w){
    /*
    Similar to draw entity but specifically sets up walls which are drawn slightly differntly.
    Mainly in thier relative sizes.
    */

    int px = round(pPos.x);
    int py = round(pPos.y);
    int pz = round(pPos.z);
    int pv = round(pRot.v);
    int ph = round(pRot.h);

    int wx[4], wy[4], wz[4];
    float CS = M.cos[ph], SN = M.sin[ph];

    if (allWalls[w] -> init == 0){ return;}

    int x1 = allWalls[w] -> x1 - px;
    int y1 = allWalls[w] -> y1 - py;
    int x2 = allWalls[w] -> x2 - px;
    int y2 = allWalls[w] -> y2 - py;

    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;
    wx[2] = wx[0];
    wx[3] = wx[1];

    wy[0] = y1 * CS + x1 * SN;
    wy[1] = y2 * CS + x2 * SN;
    wy[2] = wy[0];
    wy[3] = wy[1];

    wz[0] = 0 - pz + (pv * wy[0]) / 32.0;
    wz[1] = 0 - pz + (pv * wy[1]) / 32.0;
    wz[2] = wz[0] + 80;
    wz[3] = wz[1] + 80;

    if (wy[0] < 1 && wy[1] < 1){ return;}

    if (wy[0] < 1){
        clip(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);
        clip(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);
    }

    if (wy[1] < 1){
        clip(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);
        clip(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);
    }

    wx[0] = wx[0] * FOV / wy[0] + (WINDOW_WIDTH / 2);
    wy[0] = wz[0] * FOV / wy[0] + (WINDOW_HEIGHT / 2);
    wx[1] = wx[1] * FOV / wy[1] + (WINDOW_WIDTH / 2);
    wy[1] = wz[1] * FOV / wy[1] + (WINDOW_HEIGHT / 2);
    wx[2] = wx[2] * FOV / wy[2] + (WINDOW_WIDTH / 2);
    wy[2] = wz[2] * FOV / wy[2] + (WINDOW_HEIGHT / 2);
    wx[3] = wx[3] * FOV / wy[3] + (WINDOW_WIDTH / 2);
    wy[3] = wz[3] * FOV / wy[3] + (WINDOW_HEIGHT / 2);

    drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], allWalls[w] -> colour);

}

//-----------------------------------------------------------------------------------------------//

void calculateWallDistances(){
    /*
    Calculates the distance to each wall so they can be rendered in the right order and to
    reduce unnecessary calculations for collisions.
    */

    for (int i = 0; i < wallsSize; i++){
        if (allWalls[i] -> init == 0){
            allWalls[i] -> distance = 999999999;
        } else  {
            allWalls[i] -> distance = minDistance(  pPos.x, pPos.y, allWalls[i] -> x1,
                                                    allWalls[i] -> y1, allWalls[i] -> x2,
                                                    allWalls[i] -> y2);
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void sortWalls(){
    /*
    Sorts walls by their distance to the player so they can be rendered in the right order.
    */

    for (int i = 0; i < wallsSize; i++){
        for (int j = 0; j < wallsSize - i - 1; j++){
            if ((allWalls[j] -> distance < allWalls[j + 1] -> distance)){
                struct wall* w = allWalls[j];
                allWalls[j] = allWalls[j + 1];
                allWalls[j + 1] = w;
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void renderWorldObjects(SDL_Renderer* renderer){
    /*
    Main render loop for all world objects including walls, demons and bullets.
    */

    // After being sorted the last wall in the array is the one closest to the player and so is the
    // one that will be used for collisions.
    nearWall = allWalls[wallsSize - 1];
    int w = 0;
    int d = 0;

    // Loops over Demons and walls rendering them in order of farthest way to closest.
    for (int p = 0; p < wallsSize + MAX_DEMONS; p++){
        if ((w != wallsSize && allWalls[w] -> distance > demons[d].distance) || d == MAX_DEMONS){
            wallSetup(renderer, w);
            w++;
        } else if (d != MAX_DEMONS){
            drawEntity( renderer, demons[d].width, demons[d].height,
                        demons[d].x, demons[d].y, demons[d].colour, demons[d].init);
            d++;
        }
    }

    // Bullets are rendered over walls and demons so they dont get hidden behind things with the
    // player unable to see them or do anything about them.
    for (int b = 0; b < MAX_BULLETS; b++){
        drawEntity( renderer, bullets[b].width, bullets[b].height,
                    bullets[b].x, bullets[b].y, bullets[b].colour, bullets[b].init);
    }

}

//-----------------------------------------------------------------------------------------------//

void renderWorld(SDL_Renderer* renderer){
    /*
    Calls all the functions needed for world rendering.
    */

    floors(renderer);
    ceilings(renderer);
    calculateWallDistances();
    sortWalls();
    renderWorldObjects(renderer);

}

//-----------------------------------------------------------------------------------------------//
