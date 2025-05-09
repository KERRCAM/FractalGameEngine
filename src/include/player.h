#pragma once
// LIBRARY IMPORTS
#include <stdbool.h>

// LOCAL IMPORTS
#include "rotations.h"
#include "vectors.h"
#include "../editor/include/walls.h"

//-----------------------------------------------------------------------------------------------//
// CONSTANTS



//-----------------------------------------------------------------------------------------------//
// STRUCTS AND VARIABLES

struct pPos {
    float x, y, z;
} pPos;

struct rotation2D pRot;

int dashTime;
int vertAcc;
bool inAir;
int lastBullet;
int lastHeal;

struct wall* nearWall;

float pHP;
int score;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

void playerSetup();

void playerInput(SDL_Event event);

int detectCollision(struct vector2D pc, struct vector2D pn,
                    struct vector2D w1, struct vector2D w2);

void checkDemonBulletProximity();

int playerUpdate(float deltaTime);

//-----------------------------------------------------------------------------------------------//
