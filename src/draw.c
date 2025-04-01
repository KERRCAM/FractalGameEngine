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

//-----------------------------------------------------------------------------------------------//

struct level l;

//-----------------------------------------------------------------------------------------------//

void sectorSetup(){

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

}

//-----------------------------------------------------------------------------------------------//

float minDistance(int px, int py, int x1, int y1, int x2, int y2){

    float min = 1000000;

    float intx = abs(x1 - x2) / 10;
    float inty = abs(y1 - y2) / 10;

    float cx, cy;
    float sx, sy;
    float ex, ey;

    if (x1 < x2){
        sx = x1;
        cx = sx;
        ex = x2;
    } else {
        sx = x2;
        cx = sx;
        ex = x1;
    }

    if (y1 < y2){
        sy = y1;
        cy = sy;
        ey = y2;
    } else{
        sy = y2;
        cy = sy;
        ey = y1;
    }

    while (cx < ex || cy < ey){
        float newDistance = euclidianDistance2D(newVector2D(px, py), newVector2D(cx, cy));
        if (newDistance < min){
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

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int s, int w, int frontBack, int colour){

    SDL_SetRenderDrawColor(renderer, colours[colour][0], colours[colour][1], colours[colour][2], 255);

    int x; // ,y; -> never used so far

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

        if (frontBack == 0){
            if (l.levelSectors[s].surface == 1){ l.levelSectors[s].surf[x] = y1;}
            if (l.levelSectors[s].surface == 2){ l.levelSectors[s].surf[x] = y2;}
            SDL_RenderDrawLine(renderer, x, y1, x, y2);
        }

        if (frontBack == 1){
            if (l.levelSectors[s].surface == 1){ y2 = l.levelSectors[s].surf[x];}
            if (l.levelSectors[s].surface == 2){ y1 = l.levelSectors[s].surf[x];}
            SDL_RenderDrawLine(renderer, x, y1, x, y2);
        }


    }

}

//-----------------------------------------------------------------------------------------------//

void sectorRender(SDL_Renderer* renderer){

    int cycles;

    int px = round(pPos.x);
    int py = round(pPos.y);
    int pz = round(pPos.z);
    int pv = round(pRot.v);
    int ph = round(pRot.h);

    int wx[4], wy[4], wz[4];
    float CS = M.cos[ph], SN = M.sin[ph];

    for(int s = 0; s < MAX_SECTORS; s++){
        for(int w = 0; w < MAX_SECTORS - s - 1; w++){

            if (l.levelSectors[w].distance < l.levelSectors[w + 1].distance){
                struct sector st = l.levelSectors[w];
                l.levelSectors[w] = l.levelSectors[w + 1];
                l.levelSectors[w + 1] = st;
            } else if (l.levelSectors[w].distance == l.levelSectors[w + 1].distance){
                if (l.levelSectors[w].init == 0){ continue;}
                struct wall w1 = l.levelSectors[w].closestWall;
                struct wall w2 = l.levelSectors[w + 1].closestWall;
                if (w1.init == 0 || w2.init == 0){ continue;}
                float d1 = minDistance(px, py, w1.x1, w1.y1, w1.x2, w1.y2);
                printf("D1\n");
                printf("px %d, py %d\n", px, py);
                printf("x1 %d, y1 %d\n", w1.x1, w1.y1);
                printf("x2 %d, y2 %d\n", w1.x2, w1.y2);

                float d2 = minDistance(px, py, w2.x1, w2.y1, w2.x2, w2.y2);
                printf("D2\n");
                printf("px %d, py %d\n", px, py);
                printf("x1 %d, y1 %d\n", w2.x1, w2.y1);
                printf("x2 %d, y2 %d\n", w2.x2, w2.y2);


                printf("d1: %f, d2: %f \n", d1, d2);
                if (d1 < d2){
                    struct sector st = l.levelSectors[w];
                    l.levelSectors[w] = l.levelSectors[w + 1];
                    l.levelSectors[w + 1] = st;
                }
            }
        }
    }

    for(int i = 0; i < MAX_SECTORS; i++){
        for (int j = 0; j < MAX_WALLS ; j++){
            for (int k = 0; k < MAX_WALLS - i - 1; k++){
                if (l.levelSectors[i].sectorWalls[k].distance < l.levelSectors[i].sectorWalls[k + 1].distance){
                    struct wall w = l.levelSectors[i].sectorWalls[k];
                    l.levelSectors[i].sectorWalls[k] = l.levelSectors[i].sectorWalls[k + 1];
                    l.levelSectors[i].sectorWalls[k + 1] = w;
                }
            }
        }
    }

    for(int s = 0; s < MAX_SECTORS; s++){
        if (l.levelSectors[s].init == 0){
            continue;
        }

        l.levelSectors[s].distance = 0;
        if (pz < l.levelSectors[s].minZ) { l.levelSectors[s].surface = 1; cycles = 2; for (int x = 0; x < WINDOW_WIDTH; x++){l.levelSectors[s].surf[x] = WINDOW_HEIGHT;}}
        else if (pz > l.levelSectors[s].maxZ) { l.levelSectors[s].surface = 2; cycles = 2; for (int x = 0; x < WINDOW_WIDTH; x++){l.levelSectors[s].surf[x] = 0;}}
        else { l.levelSectors[s].surface = 0; cycles = 1;}


        for (int frontBack = 0; frontBack < cycles; frontBack++){

            for(int w = 0; w < MAX_WALLS; w++){
                if (l.levelSectors[s].sectorWalls[w].init == 0){
                    continue;
                }

                int x1 = l.levelSectors[s].sectorWalls[w].x1 - px;
                int y1 = l.levelSectors[s].sectorWalls[w].y1 - py;
                int x2 = l.levelSectors[s].sectorWalls[w].x2 - px;
                int y2 = l.levelSectors[s].sectorWalls[w].y2 - py;

                if (frontBack == 1){ int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp;}

                wx[0] = x1 * CS - y1 * SN;
                wx[1] = x2 * CS - y2 * SN;
                wx[2] = wx[0];
                wx[3] = wx[1];

                wy[0] = y1 * CS + x1 * SN;
                wy[1] = y2 * CS + x2 * SN;
                wy[2] = wy[0];
                wy[3] = wy[1];

                l.levelSectors[s].distance += euclidianDistance2D(newVector2D(0, 0),
                    newVector2D((wx[0] + wx[1]) / 2, (wy[0] + wy[1]) / 2));

                wz[0] = l.levelSectors[s].minZ - pz + (pv * wy[0]) / 32.0;
                wz[1] = l.levelSectors[s].minZ - pz + (pv * wy[1]) / 32.0;
                wz[2] = wz[0] + l.levelSectors[s].maxZ;
                wz[3] = wz[1] + l.levelSectors[s].maxZ;

                if (wy[0] < 1 && wy[1] < 1){ continue;}

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

                drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], s, w, frontBack, l.levelSectors[s].sectorWalls[w].colour);
            }

        // can probably be optimised later, definetely put in seperate function at the very least
        int minDistance = 10000000;
        int newDistance1;
        int newDistance2;
        int cw;
        for (int i = 0; i < MAX_WALLS; i++){ // will be wall max
            newDistance1 = euclidianDistance2D(newVector2D(px, py),
                newVector2D(l.levelSectors[s].sectorWalls[i].x1,
                            l.levelSectors[s].sectorWalls[i].y1));
            if (newDistance1 < minDistance){ minDistance = newDistance1; cw = i;}

            newDistance2 = euclidianDistance2D(newVector2D(px, py),
                newVector2D(l.levelSectors[s].sectorWalls[i].x2,
                            l.levelSectors[s].sectorWalls[i].y2));
            if (newDistance2 < minDistance){ minDistance = newDistance2; cw = i;}

            if (newDistance1 < newDistance2){
                l.levelSectors[s].sectorWalls[i].distance = newDistance1;
            } else {
                l.levelSectors[s].sectorWalls[i].distance = newDistance2;
            }
        }

        l.levelSectors[s].distance = minDistance;
        l.levelSectors[s].closestWall = l.levelSectors[s].sectorWalls[cw];

        //l.levelSectors[s].surface *= -1;
        }
    }

}

//-----------------------------------------------------------------------------------------------//