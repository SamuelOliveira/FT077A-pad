#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/huffman.h"

int main(int argc, char *argv[])
{
    char fileSource[50];
    char fileTarget[50];

    // Caso os parâmetros informados sejam insuficientes
    if (argc < 3)
    {
        printf("Uso: huffman [OPCAO] [ARQUIVO] [ARQUIVO]\n\n");
        printf("Opcoes:\n");
        printf("\t-c\tComprime\n");
        printf("\t-x\tDescomprime\n");
        printf("\nExemplo: ./huffman -c comprima.isso nisso.hx\n");

        return 0;
    }

    if (strcmp("-c", argv[1]) == 0)
    {
        strcpy(fileSource, argv[2]);
        strcpy(fileTarget, argv[2]);

        strip_ext(fileTarget);
        strcat(fileTarget, ".hx");

        CompressFile(fileSource, fileTarget);
    }
    else if (strcmp("-x", argv[1]) == 0)
    {
        strcpy(fileSource, argv[2]);
        strcpy(fileTarget, argv[2]);

        strip_ext(fileTarget);
        strcat(fileTarget, ".faa");

        DecompressFile(fileSource, fileTarget);
    }
    else
    {
        printf("Uso: huffman [OPCAO] [ARQUIVO] [ARQUIVO]\n\n");
        printf("Opcoes:\n");
        printf("\t-c\tComprime\n");
        printf("\t-x\tDescomprime\n");
        printf("\nExemplo: ./huffman -c comprima.isso nisso.hx\n");

        return 0;
    }

    return 0;
}
