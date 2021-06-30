#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "../Headers/utils.h"
#include "../Headers/consts.h"
#include "../Headers/huffman.h"
#include "../Headers/pth_compress.h"

void file_compress_pth(const char *fileSource, int thds)
{
    long t;
    FILE *file;
    void *status;
    pthread_t threads[thds];
    char source[] = fileSource;

    argsThread *args = (argsThread *)malloc(sizeof(argsThread));

    file = fopen(fileSource, "rb");
    args->size = fline(file);

    args->name = source;
    args->soma = 0;

    for (t=0; t<thds; t++)
    {
        args->args = t;
        pthread_create(&threads[t], NULL, file_compress, (void *) args);
    }

    for (t=0; t<thds; t++)
    {
        pthread_join(threads[t], &status);
    }
}

void file_compress(void *args)
{
    argsThread *inicio;
    inicio = (argsThread *) args;

    printf("Size %d Nome %s task %d\n",inicio->size, inicio->name, inicio->args);
}