// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/levels.h"

//-----------------------------------------------------------------------------------------------//

struct level newLevel(int pX, int pY, int pZ, struct sector levelSectors[MAX_SECTORS]){



    struct level l;

    l.pX = pX;
    l.pY = pY;
    l.pZ = pZ;

    for (int i = 0; i < MAX_SECTORS; i++){
        l.levelSectors[i] = levelSectors[i];
    }

    return l;
}

//-----------------------------------------------------------------------------------------------//

void addSector(struct level l, struct sector s){



}