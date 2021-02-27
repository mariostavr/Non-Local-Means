#include <stdio.h>
#include <stdlib.h>

#define pictureSize XXX

int main()
{
    int i,j;
    float picture[pictureSize][pictureSize];
    FILE *fptr;

    if ((fptr = fopen("Name_of_file.txt","r")) == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fptr = fopen("Name_of_file.txt","r");

    for(i=0; i<pictureSize; i++)
        for(j=0; j<pictureSize; j++)
            fscanf(fptr, "%f", &picture[i][j]);
    fclose(fptr);

    for(i=0; i<pictureSize; i++)
        for(j=0; j<pictureSize; j++)
            picture[i][j] = picture[i][j]/1000;

    FILE *inFile;
    inFile = fopen("Name_of_new_file", "w");
     for(i=0; i<pictureSize; i++)
        for(j=0; j<pictureSize; j++)
            fprintf(inFile, "%f ", picture[i][j]);
    fclose(inFile);
    return 0;
}
