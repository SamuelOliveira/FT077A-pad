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
    void *status;
    int numLin, modLin;
    pthread_t threads[thds];

    argsThread *args = (argsThread *)malloc(sizeof(argsThread));

    file = fopen(fileSource, "rb");
    args->line = fline(file);
    args->sumLin = 0;

    for (t=0; t<thds; t++)
    {
        args->args = t;

        numLin = (int) (args->line / thds);

        if(args->args == thds)
        {
            modLin = (int) (args->line % thds);
            numLin += modLin;
        }

        pthread_create(&threads[t], NULL, file_compress, (void *) args);

        args->numLin = numLin;
        args->sumLin += numLin;
    }

    for (t=0; t<thds; t++)
    {
        pthread_join(threads[t], &status);
    }
}

void *file_compress(void *args)
{
    argsThread *thread;
    thread = (argsThread *) args;

    printf("Linhas %d task %d\n",thread->line, thread->args);

    FILE* fileSplit;
    char nameSplit[50];
    char dataSplit[50];

    char line[256];
    int numLin, modLin;

    int l = 0;
    size_t len = 100;
    long posit = 1;

    snprintf(nameSplit, 50, "fileSplit_%d", thread->args);
    snprintf(dataSplit, 50, "dataSplit_%d.hx", thread->args);
    fileSplit = fopen(nameSplit, "w+");
    // numLin = (int) (thread->line / thread->thds);

    // if(thread->args == thread->thds)
    // {
    //     modLin = (int) (thread->line % thread->thds);
    //     numLin += modLin;
    // }

    fseek(file, 0, SEEK_SET);
    char *linha= malloc(len);

    while (getline(&linha, &len, file) > 0)
    {
        if (l >= thread->sumLin && l <= (thread->numLin+thread->sumLin)) {
            if (fputs(linha, fileSplit) == EOF)
                erroGravacao();
        }
        l++;
    }

    // sum += numLin;
    fclose(fileSplit);

    CompressFile(nameSplit, dataSplit);
    printf("\n");

    remove(nameSplit);

    pthread_exit(NULL);

}