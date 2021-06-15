/**
 * @brief Definições de constantes para o projeto
 */

#ifndef __CONSTS_H_
#define __CONSTS_H_
 
#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

#endif /* CONSTS_H_ */