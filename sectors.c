// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/constants.h"
#include "include/sectors.h"
#include "include/vectors.h"
#include "include/player.h"

//-----------------------------------------------------------------------------------------------//

int loadSectors[] = {
    0,   4, 0, 40, 2, 3,
    4,   8, 0, 40, 4, 5,
    8,  12, 0, 40, 6, 7,
    12, 16, 0, 40, 0, 1,
};

int loadWalls[]=
{//x1,y1, x2,y2, color
    0,   0, 32,  0, 0,
    32,  0, 32, 32, 1,
    32, 32,  0, 32, 0,
    0,  32,  0,  0, 1,

    64,  0, 96,  0, 2,
    96,  0, 96, 32, 3,
    96, 32, 64, 32, 2,
    64, 32, 64,  0, 3,

    64, 64, 96, 64, 4,
    96, 64, 96, 96, 5,
    96, 96, 64, 96, 4,
    64, 96, 64, 64, 5,

    0,  64, 32, 64, 6,
    32, 64, 32, 96, 7,
    32, 96,  0, 96, 6,
    0,  96,  0, 64, 7,
};

//-----------------------------------------------------------------------------------------------//

void sectorSetup(){

    int s, w, v1 = 0, v2 = 0;
    for (s = 0; s < numSect; s++){
        S[s].ws = loadSectors[v1 + 0];
        S[s].we = loadSectors[v1 + 1];
        S[s].z1 = loadSectors[v1 + 2];
        S[s].z2 = loadSectors[v1 + 3] - loadSectors[v1 + 2];
        S[s].c1 = loadSectors[v1 + 4];
        S[s].c2 = loadSectors[v1 + 5];
        v1 += 6;

        for (w = S[s].ws; w < S[s].we; w++){
            W[w].x1 = loadWalls[v2 + 0];
            W[w].y1 = loadWalls[v2 + 1];
            W[w].x2 = loadWalls[v2 + 2];
            W[w].y2 = loadWalls[v2 + 3];
            W[w].c = loadWalls[v2 + 4];
            v2 += 5;
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

    int x, y;

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

    int wx[4], wy[4], wz[4];
    float CS = M.cos[pRot.h], SN = M.sin[pRot.h];

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
        if (pPos.z < S[s].z1) { S[s].surface = 1;}
        else if (pPos.z > S[s].z2) { S[s].surface = 2;}
        else { S[s].surface = 0;}

        for (int loop = 0; loop < 2; loop++){

            for(int w = S[s].ws; w < S[s].we; w++){

                int x1 = W[w].x1 - pPos.x; int y1 = W[w].y1 - pPos.y;
                int x2 = W[w].x2 - pPos.x; int y2 = W[w].y2 - pPos.y;

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

                wz[0] = S[s].z1 - pPos.z + (pRot.v * wy[0]) / 32.0;
                wz[1] = S[s].z1 - pPos.z + (pRot.v * wy[1]) / 32.0;
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
        S[s].d /= (S[s].we - S[s].ws);
        S[s].surface *= -1;
        }
    }

}

//-----------------------------------------------------------------------------------------------//
