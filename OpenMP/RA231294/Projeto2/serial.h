/**
 * @brief Definições de funções seriais com matrizes
 */

#ifndef __SERIAL_H_
#define __SERIAL_H_
 
#include <stdio.h>
#include "consts.h"

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_serial(int *a, int *b, int *r, int tamanho);

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_serial(int *a, int *b, int *r, int tamanho);

#endif /* SERIAL_H_ */