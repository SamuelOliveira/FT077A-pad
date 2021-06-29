#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE // necessário porque getline() é extensão GNU

#include "../Headers/utils.h"
#include "../Headers/consts.h"

double speed_up(double ts, double tp)
{
    return ts/tp;
}

void options_list()
{
    printf("\n");
    printf("\x1b[41mOpções\x1b[0m\n");
    printf("  *\x1b[33m -c\x1b[0m - Comprimir arquivo\n");
    printf("  *\x1b[33m -d\x1b[0m - Descomprimir arquivo\n");
    printf("  *\x1b[33m -r\x1b[0m - (opcional) Imprime Resumo do Processamento\n");
    printf("\n\x1b[36mUm parâmetro com argumento deve ser fornecido!\x1b[0m\n");
    printf("\n");
}

void erroGravacao()
{
    printf("Erro ao tentar gravar os dados!\n");
}

long fsize(FILE *file)
{
    long tamanho;

    fseek(file, 0, SEEK_END);
    tamanho = ftell(file);
    fseek(file, 0, SEEK_SET);

    return tamanho;
}

long fline(FILE *file)
{
    long l = 1;
    size_t len = 100;

    fseek(file, 0, SEEK_SET);

    char *linha= malloc(len);
    while (getline(&linha, &len, file) > 0) l++;

    // int c = 0;
    // while(!feof(file))
    // {
    //     c = fgetc(file);
    //     if(c == '\n') l++;
    // }

    fseek(file, 0, SEEK_SET);

    return l;
}

/** Função para remover a extenção do nome arquivo.
* @author: https://stackoverflow.com/questions/43163677/how-do-i-strip-a-file-extension-from-a-string-in-c
* @param: um nome de arquivo.
*/
void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}