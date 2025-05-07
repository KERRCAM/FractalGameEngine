// LIBRARY IMPORTS
#include <stdio.h>
#include <stdlib.h>

// LOCAL IMPORTS
#include "include/editor.h"

//-----------------------------------------------------------------------------------------------//

// Output that is built up as one char pointer so it can be written to a file in one go.
char *output;

//-----------------------------------------------------------------------------------------------//

int strLength(char *str){
    /*
    Gets the length of the inputed char pointer.
    */

    int size = 0;
    while(str[size] != '\0'){ // Stops at string end character.
        size++;
    }
    return size;
}

//-----------------------------------------------------------------------------------------------//

void buildOutput(char *addition){
    /*
    Adds new section to the output adjusting the assigned memory accordingly.
    */

    int oldSize = strLength(output);
    int newSize = strLength(output) + strLength(addition) + 1;
    output = realloc(output, newSize);
    sprintf(output + oldSize, "%s", addition);

}

//-----------------------------------------------------------------------------------------------//

void addWall(struct wall *w){
    /*
    Adds the information for a new wall to the output.
    */

    char newLine[64];
    sprintf(newLine, "    {%d, %d, %d, %d, %d, %d},\n",
            w -> x1, w -> y1, w -> x2, w -> y2, w -> colour, w -> init);
    char *str = newLine;
    buildOutput(str);

}

//-----------------------------------------------------------------------------------------------//

void addSector(struct sector *s){
    /*
    Adds the information for a new sector to the output.
    */

    int tx = 0;
    int ty = 0;
    int c = 0;
    for (int i = 0; i < MAX_WALLS; i++){
        if (s -> sectorWalls[i].init == 1){
            c++;
            tx += (s -> sectorWalls[i].x1) + (s -> sectorWalls[i].x2);
            ty += (s -> sectorWalls[i].y1) + (s -> sectorWalls[i].y2);
        }
    }

    float nmpx = tx / c;
    float nmpy = ty / c;

    s -> mpx = nmpx;
    s -> mpy = nmpy;

    char newLine[64];
    sprintf(newLine, "    {%d, %d, %d, %d, %d, %f, %f},\n",
            s -> minZ, 80, s -> floorColour, s -> ceilingColour, s -> init, s -> mpx, s -> mpy);
    char *str = newLine;
    buildOutput(str);

}

//-----------------------------------------------------------------------------------------------//

void writeLevel(struct level *l, int number){
    /*
    Adds the information for a new level to the output.
    Also handles the memory initialisation and final file creation and write.
    */

    output = malloc(72);
    char init[72] = "#include \"../src/include/constants.h\"\n\nint sectors[MAX_SECTORS][7] = {\n";
    sprintf(output, "%s", init);

    for (int i = 0; i < MAX_SECTORS; i++) {
        struct sector *current = &l -> levelSectors[i];
        addSector(current);
    }

    char *endS_startW = "};\n\nint walls[MAX_SECTORS][MAX_WALLS][6] = {\n";
    buildOutput(endS_startW);

    for (int i = 0; i < MAX_SECTORS; i++) {
        char *startS = "    {\n";
        buildOutput(startS);

        for (int j = 0; j < MAX_WALLS; j++) {
            struct wall *current = &l -> levelSectors[i].sectorWalls[j];
            addWall(current);
        }

        char *endS = "    },\n\n";
        buildOutput(endS);
    }

    char *endW = "};\n";
    buildOutput(endW);

    FILE *fptr;

    char fileName[18];
    sprintf(fileName, "levels/level%d.h", number + 1);

    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s", output);

    fclose(fptr);

}

//-----------------------------------------------------------------------------------------------//

void saveLevels(){
    /*
    Loops over all levels calling write function on each.
    */

    for(int i = 0; i < MAX_LEVELS; i++){
        struct level *current = &levels[i];
        writeLevel(current, i);
    }

}

//-----------------------------------------------------------------------------------------------//
