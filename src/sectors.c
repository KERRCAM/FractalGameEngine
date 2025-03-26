// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/constants.h"
#include "include/sectors.h"
#include "include/vectors.h"
#include "include/player.h"
#include "newLevel.h"

//-----------------------------------------------------------------------------------------------//

void sectorSetup(){

    int s, w;
    for (s = 0; s < numSect; s++){
        S[s].z1 = loadSectors[s][0];
        S[s].z2 = loadSectors[s][1] - loadSectors[s][0];
        S[s].c1 = loadSectors[s][2];
        S[s].c2 = loadSectors[s][3];

        for (w = 0; w < 5; w++){
            W[w].x1 = loadWalls[w][0];
            W[w].y1 = loadWalls[w][1];
            W[w].x2 = loadWalls[w][2];
            W[w].y2 = loadWalls[w][3];
            W[w].c = loadWalls[w][4];
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

        if (S[s].surface == 1){ S[s].surf[x] = y1; continue;}
        if (S[s].surface == 2){ S[s].surf[x] = y2; continue;}
        if (S[s].surface == -1){ SDL_RenderDrawLine(renderer, x, S[s].surf[x], x, y1);}
        if (S[s].surface == -2){ SDL_RenderDrawLine(renderer, x, y2, x, S[s].surf[x]);}

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
            if (S[w].d < S[w + 1].d){
                sectors st = S[w]; S[w] = S[w + 1]; S[w + 1] = st;
            }
        }
    }

    for(int s = 0; s < numSect; s++){
        S[s].d = 0;
        if (pz < S[s].z1) { S[s].surface = 1;}
        else if (pz > S[s].z2) { S[s].surface = 2;}
        else { S[s].surface = 0;}

        for (int loop = 0; loop < 2; loop++){

            for(int w = 0; w < 5; w++){ // number of elements in each wall array

                int x1 = W[w].x1 - px; int y1 = W[w].y1 - py;
                int x2 = W[w].x2 - px; int y2 = W[w].y2 - py;

                if (loop == 0){ int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp;}

                wx[0] = x1 * CS - y1 * SN;
                wx[1] = x2 * CS - y2 * SN;
                wx[2] = wx[0];
                wx[3] = wx[1];

                wy[0] = y1 * CS + x1 * SN;
                wy[1] = y2 * CS + x2 * SN;
                wy[2] = wy[0];
                wy[3] = wy[1];

                S[s].d += euclidianDistance2D(newVector2D(0, 0),
                    newVector2D((wx[0] + wx[1]) / 2, (wy[0] + wy[1]) / 2));

                wz[0] = S[s].z1 - pz + (pv * wy[0]) / 32.0;
                wz[1] = S[s].z1 - pz + (pv * wy[1]) / 32.0;
                wz[2] = wz[0] + S[s].z2;
                wz[3] = wz[1] + S[s].z2;

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
        // S[s].d /= (S[s].we - S[s].ws);
        S[s].surface *= -1;
        }
    }

}

//-----------------------------------------------------------------------------------------------//
