/**
 * @brief Definições de funções seriais com matrizes
 */

#ifndef __OMP_PARALELO_H_
#define __OMP_PARALELO_H_
 
#include <stdio.h>
#include "consts.h"

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_omp(int *a, int *b, int *r, int tamanho, int thd);

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_omp(int *a, int *b, int *r, int tamanho, int thd);

#endif /* OMP_PARALELO_H_ */