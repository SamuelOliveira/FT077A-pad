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
    int t;
    void *status;
    int numLin, modLin;
    pthread_t threads[thds];

    argsThread *args = (argsThread *)malloc(sizeof(argsThread) + (sizeof(int) * 5));

    file = fopen(fileSource, "rb");
    args->line = fline(file);
    args->sumLin = 0;
    args->thds = thds;

    for (t=0; t<thds; t++)
    {
        args->args = t+1;
        printf("Thread %d\n",t);
        pthread_create(&threads[t], NULL, file_compress, (void *)args);
    }

    for (t=0; t<thds; t++)
    {
        pthread_join(threads[t], &status);
    }

    fclose(file);
}

void *file_compress(void *args)
{
    argsThread *thread = (argsThread *)malloc(sizeof(argsThread) + (sizeof(int) * 5));
    thread = (argsThread *) args;

    FILE* fileSplit;
    char nameSplit[50];
    char dataSplit[50];

    char line[256];
    int numLin, modLin;

    int l = 0;
    size_t len = 100;
    long posit = 1;

    snprintf(nameSplit, 50, "split_%d", thread->args);
    snprintf(dataSplit, 50, "chunk_%d.hx", thread->args);
    fileSplit = fopen(nameSplit, "w+");

    numLin = (int) (thread->line / thread->thds);

    if(thread->args == thread->thds)
    {
        modLin = (int) (thread->line % thread->thds);
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