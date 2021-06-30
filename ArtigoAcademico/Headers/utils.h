#ifndef __UTILS_H_
#define __UTILS_H_

/**
 * @brief Definições de funções genéricas
 */
#include <stdio.h>
#include <stdlib.h>

FILE *file;

typedef struct fileHeader
{
    int file;
    int size[];
} fileHeader;

typedef struct argsThread
{
    int thds;
    int args;
    int line;
    int numLin;
    int sumLin;
} argsThread;

double speed_up(double ts, double tp);

void options_list();
void erroGravacao();

long fsize(FILE *file);
long fline(FILE *file);

/** Função para remover a extenção do nome arquivo.
* @author: https://stackoverflow.com/questions/43163677/how-do-i-strip-a-file-extension-from-a-string-in-c
* @param: um nome de arquivo.
*/
void strip_ext(char *fname);


#endif /* UTILS_H_ */