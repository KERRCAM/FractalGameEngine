// LIBRARY IMPORTS
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/draw.h"
#include "include/vectors.h"
#include "include/player.h"
#include "../levels/level1.h"
#include "../editor/include/levels.h"
#include "include/colours.h"
#include "include/demon.h"
#include "include/globals.h"

//-----------------------------------------------------------------------------------------------//

struct level l;

//-----------------------------------------------------------------------------------------------//

void sectorSetup(){

    for (int d = 0; d < MAX_DEMONS; d++){
        demons[d] = newDemon(-1, -1, -1, -1, 0);
    }

    for (int b = 0; b < MAX_BULLETS; b++){
        bullets[b] = newBullet(-1, -1, -1, -1, 0);
    }

    struct demon test = newDemon(400, 400, 80, 1, 1);
    demons[0] = test;

    struct level l1 = newLevel(0, 0, 0, 1);
    l = l1;

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

    for (int s = 0; s < MAX_SECTORS; s++){
        for (int w = 0; w < MAX_WALLS ; w++){
            allWalls[pos] = &l.levelSectors[s].sectorWalls[w];
            pos++;
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void drawEntity(SDL_Renderer* renderer, int width, int height, int x, int y, int colour, int init){

    if (init == 0){
        return;
    }

    int px = round(pPos.x);
    int py = round(pPos.y);
    int pz = round(pPos.z);
    int pv = round(pRot.v);
    int ph = round(pRot.h);

    int wx[4], wy[4], wz[4];
    float CS = M.cos[ph], SN = M.sin[ph];

    int angle = ph + 90; if (angle > 359){ angle -= 360;}

    float xComp = M.sin[(ph + 90) % 360];
    float yComp = M.cos[(ph + 90) % 360];

    int offX = (width * xComp) / 2;
    int offY = (height * yComp) / 2;

    int x1 = x - offX - px;
    int y1 = y - offY - py;
    int x2 = x + offX - px;
    int y2 = y + offY - py;

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

    drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], colour, 0);

}

//-----------------------------------------------------------------------------------------------//

float minDistance(int px, int py, int x1, int y1, int x2, int y2){

    float min = -1;
    float intx = abs(x1 - x2) / 10.0;
    float inty = abs(y1 - y2) / 10.0;
    float cx, cy;
    float ex, ey;

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

    float da =*y1;
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

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int colour, int distance){

//    int r1 = distance / 4; if (r1 > 255) r1 = 255;
//    int c1 = colours[colour][0] * r1;
//    int r2 = distance / 4; if (r2 > 255) r2 = 255;
//    int c2 = colours[colour][1] * r2;
//    int r3 = distance / 4; if (r3 > 255) r3 = 255;
//    int c3 = colours[colour][2] * r3;
//    SDL_SetRenderDrawColor(renderer, c1, c2, c3, 255);

    SDL_SetRenderDrawColor(renderer, colours[colour][0], colours[colour][1], colours[colour][2], 255);

    int x;

    int dyb = b2 - b1;
    int dyt = t2 - t1;

    int dx = x2 - x1;
    if (dx == 0){ dx = 1;}
    int xs = x1;

    if (x1 < 0){ x1 = 0;}
    if (x2 < 0){ x2 = 0;}
    if (x1 > WINDOW_WIDTH){ x1 = WINDOW_WIDTH;}
    if (x2 > WINDOW_WIDTH){ x2 = WINDOW_WIDTH;}

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

    int x;
    int y;
    int xo = WINDOW_WIDTH / 2;
    int yo = WINDOW_HEIGHT / 2;
    float upDown = pRot.v * 2; if (upDown > WINDOW_HEIGHT){upDown = WINDOW_HEIGHT;}
    int ph = round(pRot.h);
    float scale = 0.25;

    for (y = upDown; y < yo; y += 2){
        for (x = -xo; x < xo; x += 2){
            float z = y + upDown; if (z == 0){ z = 0.0001;}
            float fx = x / z * scale;
            float fy = (float)FOV / z * scale;
            float rx = fx * M.cos[ph] + fy * M.sin[ph] + (pPos.x / 160.0);
            float ry = fx * M.sin[ph] - fy * M.cos[ph] - (pPos.y / 160.0);

            if (rx < 0){ rx = -rx + 1;}
            if (ry < 0){ ry = -ry + 1;}
            if ((int)rx % 2 == (int)ry % 2){
                SDL_SetRenderDrawColor(renderer, 0, 130, 0, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            } else{
                //int c = 255 * (255 - (y / (float)yo));
                int c = 120;
                SDL_SetRenderDrawColor(renderer, c, 120, 60, 255);
                SDL_RenderDrawPoint(renderer, x + xo, y + yo);
            }
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void ceilings(SDL_Renderer* renderer){

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
                //int c = 255 * (255 - (y / (float)yo));
                int c = 255;
                SDL_SetRenderDrawColor(renderer, c, 0, 60, 255);
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

    drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], allWalls[w] -> colour, allWalls[w] -> distance);

}

//-----------------------------------------------------------------------------------------------//

int checkBulletProximity(struct demon* d){

    for (int b = 0; b < MAX_BULLETS; b++){

        if (bullets[b].init == 0){ continue;}

        if (euclidianDistance2D(newVector2D(bullets[b].x, bullets[b].x), newVector2D(d -> x, d -> y))  < d -> width / 2){
            bullets[b] = newBullet(-1, -1, -1, -1, 0);
            return 1;
        }

    }

    return 0;

}

//-----------------------------------------------------------------------------------------------//

void renderWorld(SDL_Renderer* renderer){

    int px = round(pPos.x);
    int py = round(pPos.y);
    int wallsSize = (sizeof(allWalls) / sizeof(allWalls[0]));

    // re compute wall distances here
    for (int i = 0; i < wallsSize; i++){
        if (allWalls[i] -> init == 0){
            allWalls[i] -> distance = 999999999;
        } else  {
            allWalls[i] -> distance = minDistance(pPos.x, pPos.y, allWalls[i] -> x1, allWalls[i] -> y1, allWalls[i] -> x2, allWalls[i] -> y2);
        }

    }

    for (int i = 0; i < wallsSize; i++){
        for (int j = 0; j < wallsSize - i - 1; j++){
            if ((allWalls[j] -> distance < allWalls[j + 1] -> distance)){
                struct wall* w = allWalls[j];
                allWalls[j] = allWalls[j + 1];
                allWalls[j + 1] = w;
            }
        }
    }
    nearWall = allWalls[wallsSize - 1];

    for (int i = 0; i < MAX_DEMONS; i++){
        if (demons[i].init == 0){
            demons[i].distance = 999999999;
        } else {
            if (checkBulletProximity(&demons[i])){
                demons[i].hp -= 10;
                if (demons[i].hp <= 0){
                    score += demons[i].bounty;
                    demons[i] = newDemon(-1, -1, -1, -1, 0);
                    demons[i].distance = 999999999;
                }
            }
            demons[i].distance = euclidianDistance2D(newVector2D(px, py), newVector2D(demons[i].x, demons[i].y));
        }
    }

    for (int i = 0; i < MAX_DEMONS; i++){
        for (int j = 0; j < MAX_DEMONS - i - 1; j++){
            if ((demons[j].distance < demons[j + 1].distance)){
                struct demon d = demons[j];
                demons[j] = demons[j + 1];
                demons[j + 1] = d;
            }
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++){
        if (bullets[i].init == 0){
            bullets[i].distance = 999999999;
        } else if (SDL_GetTicks() - bullets[i].spawnTime > 3000){
            bullets[i] = newBullet(-1, -1, -1, -1, 0);
            bullets[i].distance = 999999999;
        } else  {
            bullets[i].x += bullets[i].xSpeed;
            bullets[i].y += bullets[i].ySpeed;

            bullets[i].distance = euclidianDistance2D(newVector2D(px, py), newVector2D(bullets[i].x, bullets[i].y));
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++){
        for (int j = 0; j < MAX_BULLETS - i - 1; j++){
            if ((bullets[j].distance < bullets[j + 1].distance)){
                struct bullet b = bullets[j];
                bullets[j] = bullets[j + 1];
                bullets[j + 1] = b;
            }
        }
    }

    int w = 0;
    int d = 0;

    for (int p = 0; p < wallsSize + MAX_DEMONS; p++){
        if ((w != wallsSize && allWalls[w] -> distance > demons[d].distance) || d == MAX_DEMONS){ //  && allWalls[w] -> distance > bullets[b].distance
            wallSetup(renderer, w);
            w++;
        } else if (d != MAX_DEMONS){
            drawEntity(renderer, demons[d].width, demons[d].height, demons[d].x, demons[d].y, demons[d].colour, demons[d].init);
            d++;
        }
    }

    for (int b = 0; b < MAX_BULLETS; b++){
        drawEntity(renderer, bullets[b].width, bullets[b].height, bullets[b].x, bullets[b].y, bullets[b].colour, bullets[b].init);
    }

}

//-----------------------------------------------------------------------------------------------//
