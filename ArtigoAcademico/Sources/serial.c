#include <stdlib.h>

#include "consts.h"
#include "serial.h"

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_serial(int *a, int *b, int *r, int tamanho)
{
    int tot;

    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            tot = 0;
            for(int k=0; k<tamanho; k++) {
                tot += a[posicao(i, k, tamanho)] * b[posicao(k, j, tamanho)];
            }
            r[posicao(i, j, tamanho)] = tot;
        }
    }
}

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_serial(int *a, int *b, int *r, int tamanho)
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            r[posicao(i, j, tamanho)] = a[posicao(i, j, tamanho)] + b[posicao(i, j, tamanho)];
        }
    }
}