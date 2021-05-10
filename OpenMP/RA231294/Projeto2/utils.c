#include <stdlib.h>
#include "consts.h"

/**
 * @brief Alocando uma matriz quadrada
 */
int *aloca_matriz(int tamanho) {
    return (int *) malloc(tamanho * tamanho * sizeof(int));
}

/**
 * @brief Carrega uma matriz quadrada de forma serial
 */
void carrega_matriz(int *args, int tamanho)
{
    for (int i=0; i < tamanho; i++) {
        for (int j=0; j < tamanho; j++) {
            args[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }
}

/**
 * @brief Imprimindo uma matriz quadrada
 */
void imprime_matriz(int *args, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        for(int j = 0; j < tamanho; j++)
        {
            if(j != (tamanho-1))
            {
                printf("%d \t",args[posicao(i, j, tamanho)]);
            }
            else
            {
                printf("%d \n",args[posicao(i, j, tamanho)]);
            }
        }
    }
    printf("\n");
}

double speed_up(double ts, double tp) {
    return ts/tp;
}

// https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/?ref=rp
// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
void options_list()
{
    printf("\n");
    printf("\x1b[41mOpções\x1b[0m\n");
    printf("  *\x1b[33m -t\x1b[0m - Tamanho da Matriz Quadrada\n");
    printf("  *\x1b[33m -r\x1b[0m - Número de Threads no Processamento, r>=2\n");
    printf("  *\x1b[33m -s\x1b[0m - (opcional) Imprime Resumo do Processamento\n");
    printf("  *\x1b[33m -v\x1b[0m - (opcional) Imprime Matrizes para Verificação, t<=10\n");
    printf("\n\x1b[36mNo mínimo dois parâmetros com argumentos devem ser fornecidos!\x1b[0m\n");
    printf("\n");	
}