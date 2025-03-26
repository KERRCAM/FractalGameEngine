// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/levels.h"

//-----------------------------------------------------------------------------------------------//

struct level newLevel(int pX, int pY, int pZ){



    struct level l;

    l.pX = pX;
    l.pY = pY;
    l.pZ = pZ;

    for (int i = 0; i < MAX_SECTORS; i++){
        l.levelSectors[i] = newSector(-1, -1, 0, 0);
    }

    return l;
}

//-----------------------------------------------------------------------------------------------//

void addSector(struct level l, struct sector s){



}