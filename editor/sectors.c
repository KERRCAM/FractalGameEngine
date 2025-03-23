// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/sectors.h"

//-----------------------------------------------------------------------------------------------//

struct sector newSector(int minZ, int maxZ, int floorColour, int ceilingColour,
                        struct wall sectorWalls[MAX_WALLS]){

    struct sector s;

    s.minZ = minZ;
    s.maxZ = maxZ;
    s.floorColour = floorColour;
    s.ceilingColour = ceilingColour;

    for (int i = 0; i < MAX_WALLS; i++){
        s.sectorWalls[i] = sectorWalls[i];
    }

    return s;

}

//-----------------------------------------------------------------------------------------------//

void addWall(struct sector s, struct wall w){



}