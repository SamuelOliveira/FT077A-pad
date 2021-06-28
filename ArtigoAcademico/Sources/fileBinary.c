#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fileHeader
{
    int file;
    int size[];
} fileHeader;

int main () {
    int file;
    int size = 9;
    FILE *fileOf;
    FILE *fileTo;

    fileHeader *filesOpen;
    fileHeader *filesInfo;

    char *fileName = "fileBinary.hex";

    filesOpen = (fileHeader *)malloc(sizeof(fileHeader) + (sizeof(int) * size));

    filesOpen->file = size;

    printf("%d\n",filesOpen->file);

    for(int i=0; i<size; i++) {
        filesOpen->size[i] = (i+1)*70;
        printf("%d\n",filesOpen->size[i]);
    }

    fileOf = fopen(fileName, "w");

    fwrite(filesOpen, sizeof(fileHeader) + (sizeof(int) * size), 1, fileOf);
    fclose(fileOf);

    printf("\n");

    fileTo = fopen(fileName, "r");
    fread(&file, sizeof(int), 1, fileTo);
    fseek(fileTo, 0, SEEK_SET);

    filesInfo = (fileHeader *)malloc(sizeof(fileHeader) + (sizeof(int) * file));
    fread(filesInfo, sizeof(fileHeader) + (sizeof(int) * file), 1, fileTo);

    printf("%d\n",filesInfo->file);

    for(int j=0; j<filesInfo->file; j++)
        printf("%d\n",filesInfo->size[j]);

    fclose(fileTo);
}
