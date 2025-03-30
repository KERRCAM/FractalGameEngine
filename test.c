#include <stdio.h>
#include <math.h>





int main(){

    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("levels/filename.txt", "w");

    // Write some text to the file
    fprintf(fptr, "Some text");

    // Close the file
    fclose(fptr);

    return 0;
}