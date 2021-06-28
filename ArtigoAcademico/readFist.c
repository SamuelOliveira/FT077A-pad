#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <sys/stat.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#define MAX_FILE_NAME 100

#define BUFFER_SIZE 50

typedef struct fileHeader
{
    int files;
    int sizes[];
} fileHeader;

void concatenar (FILE *base, FILE *copiado);

int main() {
    wchar_t str[BUFFER_SIZE];
    size_t  strSize;
    struct stat sb;
    // https://www.delftstack.com/pt/howto/c/file-size-in-c/

    char buffer[200]; // Buffer to store data
    FILE *base;
    FILE *arquivo2;
    FILE *arquivo3;
    size_t len = 100;

    fileHeader header;
    
    int line = 0;

    char *linha= malloc(len);

    base = fopen("base.txt", "r");
    arquivo2 = fopen("arquivo2.txt", "w");
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
       

    header.files = 3;
    stat("base.txt", &sb);
    header.sizes[0] = sb.st_size;
    sb.st_size = 0;
    stat("arquivo2.txt", &sb);
    header.sizes[1] = sb.st_size;
    sb.st_size = 0;
    stat("arquivo3.txt", &sb);
    header.sizes[2] = sb.st_size;
    sb.st_size = 0;
    printf("tamanho do Base %d\n", header.sizes[0]);
    printf("tamanho do arquivo2 %d\n", header.sizes[1]);
    printf("tamanho do arquivo3 %d\n", header.sizes[2]);

    // fclose(base);
    // fclose(arquivo3);
    // fclose(arquivo2);
    // remove("arquivo2.txt");

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
