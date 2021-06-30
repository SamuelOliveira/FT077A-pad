#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include <pthread.h>

#include "../Headers/utils.h"
#include "../Headers/consts.h"
#include "../Headers/huffman.h"
#include "../Headers/pth_compress.h"


void file_compress_pth(const char *fileSource, int thds)
{
    long thdi;
    long line;
    void *status;
    pthread_t threads[thds];
    struct argsThread *args;

    file = fopen(fileSource, "rb");
    line = fline(file);

    for (thdi=0; thdi<thds; thdi++)
    {
        args = (argsThread *)malloc(sizeof(argsThread) + (sizeof(long) * 5));
        (*args).sumLin = 0;
        (*args).thds = thds;
        (*args).line = line;
        (*args).thdi = thdi+1;
        pthread_create(&threads[thdi], NULL, file_compress, (void *)args);
    }

    for (thdi=0; thdi<thds; thdi++)
    {
        pthread_join(threads[thdi], &status);
    }

    fclose(file);
}

void *file_compress(void *args)
{
    argsThread *thread;
    thread = (argsThread *)args;

    FILE* fileSplit;
    char nameSplit[50];
    char dataSplit[50];

    char line[256];
    long numLin, modLin;

    int l = 0;
    long posit = 1;
    size_t len = 100;

    snprintf(nameSplit, 50, "split_%ld", thread->thdi);
    snprintf(dataSplit, 50, "chunk_%ld.hx", thread->thdi);
    fileSplit = fopen(nameSplit, "w+");

    numLin = (long) (thread->line / thread->thds);

    if(thread->thdi == thread->thds)
    {
        modLin = (long) (thread->line % thread->thds);
        numLin += modLin;
    }

    fseek(file, 0, SEEK_SET);
    char *linha= malloc(len);

    while (getline(&linha, &len, file) > 0)
    {
        if (l >= thread->sumLin && l <= (numLin+thread->sumLin)) {
            if (fputs(linha, fileSplit) == EOF)
                erroGravacao();
        }
        l++;
    }

    thread->numLin = numLin;
    thread->sumLin += numLin;

    fclose(fileSplit);

    CompressFile(nameSplit, dataSplit);
    printf("\n");

    remove(nameSplit);

    pthread_exit(NULL);

}
