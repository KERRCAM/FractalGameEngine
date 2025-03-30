// LIBRARY IMPORTS
#include <stdio.h>
#include <stdlib.h>

// LOCAL IMPORTS
#include "include/editor.h"

//-----------------------------------------------------------------------------------------------//

char *output;

//-----------------------------------------------------------------------------------------------//

int strLength(char *str){

    int size = 0;
    while(str[size] != '\0'){
        size++;
    }
    return size;
}

//-----------------------------------------------------------------------------------------------//

void buildOutput(char *addition){

    int oldSize = strLength(output);
    int newSize = strLength(output) + strLength(addition) + 1;
    output = realloc(output, newSize);
    sprintf(output + oldSize, "%s", addition);

}

//-----------------------------------------------------------------------------------------------//

void addWall(struct wall *w){

    char newLine[64];
    sprintf(newLine, "    {%d, %d, %d, %d, %d, %d},\n",
            w -> x1, w -> y1, w -> x2, w -> y2, w -> colour, w -> init);
    char *str = newLine;
    buildOutput(str);

}

//-----------------------------------------------------------------------------------------------//

void addSector(struct sector *s){

    char newLine[64];
    sprintf(newLine, "    {%d, %d, %d, %d, %d},\n",
            s -> minZ, 80, s -> floorColour, s -> ceilingColour, s -> init);
    char *str = newLine;
    buildOutput(str);

}

//-----------------------------------------------------------------------------------------------//

void writeLevel(struct level *l, int number){

    output = malloc(72);
    char init[72] = "#include \"../src/include/constants.h\"\n\nint sectors[MAX_SECTORS][5] = {\n";
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

    for(int i = 0; i < MAX_LEVELS; i++){
        struct level *current = &levels[i];
        writeLevel(current, i);
    }

}

//-----------------------------------------------------------------------------------------------//

/* TODO:
- Write saved levels into seperated .h each
- Also on editor start up we need to initialise our structs with the information in existing .h level files
- Move render code to seperate files maybe
- also maybe try reduce duplicate code in input processor
*/