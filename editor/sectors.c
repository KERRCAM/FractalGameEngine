// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "include/sectors.h"

//-----------------------------------------------------------------------------------------------//

struct sector newSector(int minZ, int maxZ, int floorColour, int ceilingColour, int init){

    struct sector s;

    s.minZ = minZ;
    s.maxZ = maxZ;
    s.floorColour = floorColour;
    s.ceilingColour = ceilingColour;
    s.init = init;

    for (int i = 0; i < MAX_WALLS; i++){
        s.sectorWalls[i] = newWall(-1, -1, -1, -1, 0, 0);
    }

    return s;

}

//-----------------------------------------------------------------------------------------------//

