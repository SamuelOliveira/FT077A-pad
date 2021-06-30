#include <stdio.h>

#include "../Headers/utils.h"
#include "../Headers/huffman.h"
#include "../Headers/serial_compress.h"

void file_compress_serial(const char *fileSource)
{
    char fileTarget[50];

    strcpy(fileTarget, fileSource);

    strip_ext(fileTarget);
    strcat(fileTarget, ".hx");

    CompressFile(fileSource, fileTarget);
}