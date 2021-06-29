#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include <omp.h>

#include "../Headers/utils.h"
#include "../Headers/consts.h"
#include "../Headers/huffman.h"
#include "../Headers/omp_compress.h"

void file_compress_opm(FILE *file, int thds)
{
    int i;
    long sum = 0;
    long tamanho;
    tamanho = fline(file);

    FILE* fileSplit;
    char nameSplit[50];
    char dataSplit[50];

    #pragma omp parallel shared(file, tamanho, sum) \
        private(fileSplit, nameSplit, dataSplit, i) \
        num_threads(thds)
    {
        #pragma omp for
        for (i=0; i<thds; i++) {
            char line[256];
            int numLin, modLin;
            int tid = omp_get_thread_num();

            int l = 0;
            size_t len = 100;
            long posit = 1;

            snprintf(nameSplit, 50, "fileSplit_%d", i+1);
            snprintf(dataSplit, 50, "dataSplit_%d.hx", i+1);
            fileSplit = fopen(nameSplit, "w+");
            numLin = (int) (tamanho / thds);

            if(tid == thds)
            {
                modLin = (int) (tamanho % thds);
                numLin += modLin;
            }

            fseek(file, 0, SEEK_SET);
            char *linha= malloc(len);

            while (getline(&linha, &len, file) > 0)
            {
                if (l >= sum && l <= (numLin+sum)) {
                    if (fputs(linha, fileSplit) == EOF)
                        erroGravacao();
                }
                l++;
            }

            sum += numLin;
            fclose(fileSplit);

            CompressName(nameSplit, dataSplit);
            printf("\n");

            remove(nameSplit);
        }
    }

}