#include <stdlib.h>
#include <string.h>

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