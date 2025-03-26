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



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//

void addWall(struct wall *w){



}

//-----------------------------------------------------------------------------------------------//

void addSector(struct sector *s){



}

//-----------------------------------------------------------------------------------------------//

void writeLevel(struct level *l, int number){

    output = malloc(23);
    char init[23] = "int loadSectors[] = {\n";
    sprintf(output, "%s", init);

    for (int i = 0; i < MAX_SECTORS; i++) {
        if (l -> levelSectors[i].minZ > -1){
            struct sector *current = &l -> levelSectors[i];
            addSector(current);
        }
    }

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