#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include "../Headers/utils.h"
#include "../Headers/huffman.h"
#include "../Headers/pth_compress.h"
#include "../Headers/serial_compress.h"

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
    short thread = 0;  // Opcao t

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
            // case 't' : // Thread
            //     tmp = argv[1];
            //     ret = strstr(tmp, "tc");
            //     if(ret) {
            //         thread = atoi(argv[2]);
            //         option = 1;
            //     }
            //     break;
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

    // if(thread < 2) {
    //     options_list();
    //     printf("\x1b[41mAviso:\x1b[0m\x1b[33m Threads insuficientes!\x1b[0m\n");
    //     exit(0);
    // }

    strcpy(fileSource, argv[2]);
    strcpy(fileTarget, argv[2]);
    strip_ext(fileTarget);

    if(option==1) {
        file_compress_serial(fileSource);
        file_compress_pth(fileSource,split);
    }

    if(option==2) {
        strcat(fileTarget, ".faa");
        DecompressFile(fileSource, fileTarget);       
    }

    return 0;
}
