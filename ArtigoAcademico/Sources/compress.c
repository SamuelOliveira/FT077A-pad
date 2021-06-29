#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/utils.h"
#include "../Headers/huffman.h"

int main(int argc, char *argv[])
{
    // Variaveis de controle para posição do parametro
    char *ret;
    char *tmp;
    char optc = 0;
    int split = 3;

    // Variaveis para os parametros e argumentos
    short option = 0;  // Opcao c ou d
    short resume = 0;  // Opcao r

    char fileSource[50];
    char fileTarget[50];

    FILE* file;

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
        long sum = 0;
        long tamanho;
        int numLin, modLin;

        strcat(fileTarget, ".hx");
        file  = fopen(fileSource, "r");
        
        fseek(file, 0, SEEK_SET);

        tamanho = ftell(file);

        for(int i=0; i<split; i++)
        {
            char line[256];
            FILE* fileSplit;
            char nameSplit[50];

            snprintf(nameSplit, 50, "fileSplit_%d", i+1);

            fileSplit = fopen(nameSplit, "w+");

            // numero de linhas para split do arquivo
            numLin = (int) (tamanho / split);

            if(split == i+1)
            {
                modLin = (int) (tamanho % split);
                numLin += modLin;
            }

            fseek(file, sum, SEEK_CUR);

            while (fgets(line, sizeof(line), file)) {
                if (fputs(line, fileSplit) == EOF)
                    erroGravacao();
            }

            sum += numLin;
            fclose(fileSplit);

            // while (fgets(line, sizeof(line), file)) {
            //     l++;
            //     if (l <= 2) {
            //         if (fputs(line, file1) == EOF)
            //             erroGravacao();
            //     };
            //     if (l >= 3 && l <= 5) {
            //         if (fputs(line, file2) == EOF)
            //             erroGravacao();
            //     };
            // }

            // printf("%d\n",numLin);

            // int l = 0;
            // char line[256];
            // FILE* fileSplit = fopen(fileName1, "w+");
        }


        // SplitFile
        // CompressFile(fileSource, fileTarget);        
    }

    if(option==2) {
        strcat(fileTarget, ".faa");
        DecompressFile(fileSource, fileTarget);       
    }

    return 0;
}
