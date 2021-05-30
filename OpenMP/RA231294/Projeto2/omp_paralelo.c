#include <stdlib.h>
#include <omp.h>

#include "consts.h"
#include "omp_paralelo.h"

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_omp(int *a, int *b, int *r, int tamanho, int thds)
{
    int i, j, k, tot;

    /**
     * Aqui definimos o número de threads para esta operação r = thds
     **/
    #pragma omp parallel shared(r) private(i, j, k, tot) num_threads(thds)
    {
        #pragma omp for collapse(2)
        for (i=0; i<tamanho; i++) {
            for (j=0; j<tamanho; j++) {
                tot = 0;
                for(k=0; k<tamanho; k++) {
                    tot += a[posicao(i, k, tamanho)] * b[posicao(k, j, tamanho)];
                }
                r[posicao(i, j, tamanho)] = tot;
            }
        }
        //Aqui temos um join implicito, um mecanismo de sincronização
    }
}

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_omp(int *a, int *b, int *r, int tamanho, int thds)
{
    int i, j;

    /**
     * Aqui definimos o número de threads para esta operação r = thds
     **/
    #pragma omp parallel shared(r) private(i, j) num_threads(thds)
    {
        #pragma omp for
        for (i=0; i<tamanho; i++) {
            for (j=0; j<tamanho; j++) {
                r[posicao(i, j, tamanho)] = a[posicao(i, j, tamanho)] + b[posicao(i, j, tamanho)];
            }
        }
        //Aqui temos um join implicito, um mecanismo de sincronização
    }
}