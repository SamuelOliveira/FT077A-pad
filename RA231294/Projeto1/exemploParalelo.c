#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS	50
#define tamanho 1000
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

typedef struct Args {
   int  *matriz;
   int  inicio;
} param;

// D = A * B + C

void *carrega_matriz(void *args)
{
    param *p = (param *) args;
    int *matriz, inicio, numLin, numCol;

    matriz = p->matriz;
    inicio = p->inicio;

    numCol = tamanho;
    numLin = (int) (tamanho / THREADS);

    for (int i=(inicio*numLin); i<numLin*(inicio+1); i++) {
        for (int j=0; j<numCol; j++) {
            matriz[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }

    pthread_exit(NULL);
}

void imprime_matriz(int *args)
{
    for( int i = 0; i < tamanho; i++)
    {
        for( int j = 0; j < tamanho; j++)
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

int main() {
    srand(time(NULL));
    pthread_t threads[THREADS];
    param *p;

    long t;
    int rc;
    void *status;
    int *matrizA, *matrizB, *matrizC, *matrizP, *matrizD;

    matrizA = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizB = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizC = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizP = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizD = (int *) malloc(tamanho * tamanho * sizeof(int));
  
    for (t=0; t<THREADS; t++)
    {
        param *p = (param *) malloc(sizeof(param));
        p->inicio = t;
        p->matriz = matrizA;

        pthread_create(&threads[t], NULL, (void *) carrega_matriz, (void *) p);
    }

    for (t=0;t<THREADS;t++)
    {
        pthread_join(threads[t], &status);
        printf("Retorno do thread %ld com status %ld\n", t, (long) status);
    }


    for (t=0; t<THREADS; t++)
    {
        param *p = (param *) malloc(sizeof(param));
        p->inicio = t;
        p->matriz = matrizB;

        pthread_create(&threads[t], NULL, (void *) carrega_matriz, (void *) p);
    }

    for (t=0;t<THREADS;t++)
    {
        pthread_join(threads[t], &status);
        printf("Retorno do thread %ld com status %ld\n", t, (long) status);
    }


    for (t=0; t<THREADS; t++)
    {
        param *p = (param *) malloc(sizeof(param));
        p->inicio = t;
        p->matriz = matrizC;

        pthread_create(&threads[t], NULL, (void *) carrega_matriz, (void *) p);
    }

    for (t=0;t<THREADS;t++)
    {
        pthread_join(threads[t], &status);
        printf("Retorno do thread %ld com status %ld\n", t, (long) status);
    }

    // sleep(1);

    // printf("Matriz A\n");
    // imprime_matriz(matrizA);

    // printf("Matriz B\n");
    // imprime_matriz(matrizB);

    // printf("Matriz C\n");
    // imprime_matriz(matrizC);

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizP);
    free(matrizD);

    return 0;
}