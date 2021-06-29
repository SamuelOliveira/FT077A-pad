#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include "../Headers/huffman.h"
#include "../Headers/serial_compress.h"

void file_compress(FILE *file)
{
    // char fileSource[50];
    // char fileTarget[50];

    // strcpy(fileSource, "fileSplit");
    // strcpy(fileTarget, argv[2]);
    // strip_ext(fileTarget);

    // strip_ext(fileTarget);
    // strcat(fileTarget, ".hx");
    // file  = fopen(fileSource, "r");

    // fseek(file, 0, SEEK_SET);

    // CompressFile(fileSource, fileTarget);

}