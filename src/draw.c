// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/draw.h"
#include "include/vectors.h"
#include "include/player.h"
#include "newLevel.h"
#include "../editor/include/levels.h"

//-----------------------------------------------------------------------------------------------//

// distance function -> calc wall midpoints, calc midpoint of all walls in sector
// calc L2 distance from player to sector midpoint (2D) and return it

struct level l;

//-----------------------------------------------------------------------------------------------//

void sectorSetup(){

    struct level l1 = newLevel(0, 0, 0, 1);
    l = l1;

    for (int i = 0; i < 4; i++){ // will be max sectors
        l.levelSectors[i].minZ = sectors[i][0];
        l.levelSectors[i].maxZ = sectors[i][1];
        l.levelSectors[i].floorColour = sectors[i][2];
        l.levelSectors[i].ceilingColour = sectors[i][3];
        l.levelSectors[i].init = sectors[i][4];

        for (int j = 0; j < 4; j++){ // will be max walls
            l.levelSectors[i].sectorWalls[j].x1 = walls[i][j][0];
            l.levelSectors[i].sectorWalls[j].y1 = walls[i][j][1];
            l.levelSectors[i].sectorWalls[j].x2 = walls[i][j][2];
            l.levelSectors[i].sectorWalls[j].y2 = walls[i][j][3];
            l.levelSectors[i].sectorWalls[j].colour = walls[i][j][4];
            l.levelSectors[i].sectorWalls[j].init = walls[i][j][5];
        }
    }

}

//-----------------------------------------------------------------------------------------------//

void clip(int *x1, int *y1, int *z1, int x2, int y2, int z2){

    float da =*y1;
    float db = y2;
    float d = da - db;
    if (d == 0){ d = 1;}
    float s = da / (da - db);
    *x1 = *x1 + s*(x2 - (*x1));
    *y1 = *y1 + s*(y2 - (*y1));
    if (*y1 == 0){ *y1 = 1;}
    *z1 = *z1 + s*(z2 - (*z1));

}

//-----------------------------------------------------------------------------------------------//

void drawWall (SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int s){

    int x; // ,y; -> never used so far

    int dyb = b2 - b1;
    int dyt = t2 - t1;

    int dx = x2 - x1;
    if (dx == 0){ dx = 1;}
    int xs = x1;

    if (x1 < 1){ x1 = 1;}
    if (x2 < 1){ x2 = 1;}
    if (x1 > WINDOW_WIDTH - 1){ x1 = WINDOW_WIDTH - 1;}
    if (x2 > WINDOW_WIDTH - 1){ x2 = WINDOW_WIDTH - 1;}

    for (x = x1; x < x2; x++){
        int y1 = dyb * (x - xs + 0.5) / dx + b1;
        int y2 = dyt * (x - xs + 0.5) / dx + t1;

        if (y1 < 1){ y1 = 1;}
        if (y2 < 1){ y2 = 1;}
        if (y1 > WINDOW_HEIGHT - 1){ y1 = WINDOW_HEIGHT - 1;}
        if (y2 > WINDOW_HEIGHT - 1){ y2 = WINDOW_HEIGHT - 1;}

        if (l.levelSectors[s].surface == 1){ l.levelSectors[s].surf[x] = y1; continue;}
        if (l.levelSectors[s].surface == 2){ l.levelSectors[s].surf[x] = y2; continue;}
        if (l.levelSectors[s].surface == -1){ SDL_RenderDrawLine(renderer, x, l.levelSectors[s].surf[x], x, y1);}
        if (l.levelSectors[s].surface == -2){ SDL_RenderDrawLine(renderer, x, y2, x, l.levelSectors[s].surf[x]);}

        SDL_RenderDrawLine(renderer, x, y1, x, y2);
    }

}

//-----------------------------------------------------------------------------------------------//

void sectorRender(SDL_Renderer* renderer){

    int px = round(pPos.x);
    int py = round(pPos.y);
    int pz = round(pPos.z);
    int pv = round(pRot.v);
    int ph = round(pRot.h);

    int wx[4], wy[4], wz[4];
    float CS = M.cos[ph], SN = M.sin[ph];

    // crappy bubble sort, replace later with somehting better
    for(int s = 0; s < numSect; s++){
        for(int w = 0; w < numSect - s - 1; w++){
            if (l.levelSectors[w].distance < l.levelSectors[w + 1].distance){
                struct sector st = l.levelSectors[w];
                l.levelSectors[w] = l.levelSectors[w + 1];
                l.levelSectors[w + 1] = st;
            }
        }
    }

    for(int s = 0; s < numSect; s++){
        l.levelSectors[s].distance = 0;
        if (pz < l.levelSectors[s].minZ) { l.levelSectors[s].surface = 1;}
        else if (pz > l.levelSectors[s].maxZ) { l.levelSectors[s].surface = 2;}
        else { l.levelSectors[s].surface = 0;}

        for (int loop = 0; loop < 2; loop++){

            for(int w = 0; w < 4; w++){

                int x1 = l.levelSectors[s].sectorWalls[w].x1 - px; int y1 = l.levelSectors[s].sectorWalls[w].y1 - py;
                int x2 = l.levelSectors[s].sectorWalls[w].x2 - px; int y2 = l.levelSectors[s].sectorWalls[w].y2 - py;

                if (loop == 0){ int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp;}

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

                wx[0] = wx[0] * 200 / wy[0] + (WINDOW_WIDTH / 2);
                wy[0] = wz[0] * 200 / wy[0] + (WINDOW_HEIGHT / 2);
                wx[1] = wx[1] * 200 / wy[1] + (WINDOW_WIDTH / 2);
                wy[1] = wz[1] * 200 / wy[1] + (WINDOW_HEIGHT / 2);
                wx[2] = wx[2] * 200 / wy[2] + (WINDOW_WIDTH / 2);
                wy[2] = wz[2] * 200 / wy[2] + (WINDOW_HEIGHT / 2);
                wx[3] = wx[3] * 200 / wy[3] + (WINDOW_WIDTH / 2);
                wy[3] = wz[3] * 200 / wy[3] + (WINDOW_HEIGHT / 2);

                SDL_SetRenderDrawColor(renderer, (wx[0] * 5 % 255), (wy[1] * 15 % 255), (wy[0] * 20 % 255), (wx[1] * 8 % 255));

                drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], s);
            }

        // can probably be optimised later, definetely put in seperate function at the very least
        int minDistance = 10000000;
        int newDistance;
        for (int i = 0; i < 4; i++){ // will be wall max
            newDistance = euclidianDistance2D(newVector2D(px, py),
                newVector2D(l.levelSectors[s].sectorWalls[i].x1, l.levelSectors[s].sectorWalls[i].y1)
            );
            if (newDistance < minDistance){ minDistance = newDistance;}

            newDistance = euclidianDistance2D(newVector2D(px, py),
                newVector2D(l.levelSectors[s].sectorWalls[i].x2, l.levelSectors[s].sectorWalls[i].y2)
            );
            if (newDistance < minDistance){ minDistance = newDistance;}
        }

        l.levelSectors[s].surface *= -1;
        }
    }

}

//-----------------------------------------------------------------------------------------------//