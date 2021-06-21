/**
 * @brief Definições de funções genéricas
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include "consts.h"

/**
 * @brief Alocando uma matriz quadrada
 */
int *aloca_matriz(int tamanho);

/**
 * @brief Carrega uma matriz quadrada de forma serial
 */
void carrega_matriz(int *args, int tamanho);

/**
 * @brief Imprimindo uma matriz quadrada
 */
void imprime_matriz(int *args, int tamanho);

double speed_up(double ts, double tp);

void options_list();

#endif /* UTILS_H_ */
