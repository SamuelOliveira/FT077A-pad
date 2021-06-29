#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include "../Headers/utils.h"
#include "../Headers/huffman.h"
#include "../Headers/omp_compress.h"

int main(int argc, char *argv[])
{
    // Variaveis de controle para posição do parametro
    char *ret;
    char *tmp;
    char optc = 0;
    int split = 2;

    // Variaveis para os parametros e argumentos
    short option = 0;  // Opcao c ou d
    short resume = 0;  // Opcao r

    char fileSource[50];
    char fileTarget[50];
    char *fileName = "fileBinary.hx";

    FILE *file;
    FILE *data;
    FILE *fileOf;
    fileHeader *filesOpen;

    filesOpen = (fileHeader *)malloc(sizeof(fileHeader) + (sizeof(int) * split));

    filesOpen->file = split;

    // Sem argumentos
    if(argc == 1) {
        options_list();
        exit(0);
    }

    // Argumentos insuficientes
    if(argc != 3) {
        options_list();
        printf("\x1b[41mAviso:\x1b[0m\x1b[33m Argumentos insuficientes!\x1b[0m\n");
        exit(0);
    }

    while((optc = getopt(argc, argv, "cdr")) != -1) {
        switch(optc) {
            case 'r' : // Resume
                resume = 1;
                break;
            case 'c' : // Compress
                tmp = argv[1];
                ret = strstr(tmp, "c");
                if(ret) option = 1;
                break;
            case 'd' : // Decompress
                tmp = argv[1];
                ret = strstr(tmp, "d");
                if(ret) option = 2;
                break;
            default : // Qualquer parametro nao tratado
                printf("\x1b[41mAviso:\x1b[0m\x1b[33m Parametros incorretos!\x1b[0m\n");
                exit(0);
        }
    }

    strcpy(fileSource, argv[2]);
    strcpy(fileTarget, argv[2]);
    strip_ext(fileTarget);

    if(option==1) {

        strcat(fileTarget, ".hx");
        file  = fopen(fileSource, "r");

        file_compress_opm(file,split);

        // long sum = 0;
        // long tamanho;
        // char line[256];
        // int numLin, modLin;
        // char* strings[split];

        // strcat(fileTarget, ".hx");
        // file  = fopen(fileSource, "r");
        
        // tamanho = fline(file);

        // for(int i=0; i<split; i++)
        // {
        //     int l = 0;
        //     size_t len = 100;
        //     long posit = 1;

        //     FILE* fileSplit;
        //     char nameSplit[50];
        //     char dataSplit[50];

        //     snprintf(nameSplit, 50, "fileSplit_%d", i+1);
        //     snprintf(dataSplit, 50, "dataSplit_%d.hx", i+1);

        //     fileSplit = fopen(nameSplit, "w+");

        //     // numero de linhas para split do arquivo
        //     numLin = (int) (tamanho / split);

        //     if(split == i+1)
        //     {
        //         modLin = (int) (tamanho % split);
        //         numLin += modLin;
        //     }

        //     fseek(file, 0, SEEK_SET);
        //     char *linha= malloc(len);

        //     while (getline(&linha, &len, file) > 0)
        //     {
        //         if (l >= sum && l <= (numLin+sum)) {
        //             if (fputs(linha, fileSplit) == EOF)
        //                 erroGravacao();
        //         }
        //         l++;
        //     }

        //     sum += numLin;
        //     fclose(fileSplit);

        //     filesOpen->size[i] = CompressName(nameSplit, dataSplit);
        //     strings[i] = dataSplit;

        //     remove(nameSplit);
        // }

        // fclose(fileOf);
    }

    if(option==2) {
        strcat(fileTarget, ".faa");
        DecompressFile(fileSource, fileTarget);       
    }

    return 0;
}
