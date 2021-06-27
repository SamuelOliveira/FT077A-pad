#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#define MAX_FILE_NAME 100

#define BUFFER_SIZE 50

void concatenar ( FILE *base, FILE *copiado);

int main() {
    wchar_t str[BUFFER_SIZE];
    size_t  strSize;

    char buffer[200]; // Buffer to store data
    FILE *base;
    FILE *arquivo2;
    FILE *arquivo3;
    size_t len= 100;

    int line = 0;

    char *linha= malloc(len);

    base = fopen("base.txt", "r");
    arquivo2 = fopen("arquivo2.txt", "a");
    arquivo3 = fopen("arquivo3.txt", "w");

    while ((getline(&linha, &len, base) > 0) && (line < 2))
    {
        ++line;
        if (fputs(linha, arquivo2) == EOF)
            printf("Erro ao tentar gravar os dados! \n");
    }

    rewind(base);

    fclose(arquivo2);
    arquivo2 = fopen("arquivo2.txt", "r");

    concatenar(arquivo3,base);
    fputs("\n-----------------------\n", arquivo3);
    concatenar(arquivo3,arquivo2);

    fclose(base);
    fclose(arquivo3);
    fclose(arquivo2);
    remove("arquivo2.txt");

    free(linha);

    printf("\n");

    return 0;
}

void concatenar ( FILE *base, FILE *copiado)
{
    char leitor [1000];

    while (fgets (leitor, sizeof leitor, copiado) != NULL)
    {
        fputs (leitor, base);
    }
}