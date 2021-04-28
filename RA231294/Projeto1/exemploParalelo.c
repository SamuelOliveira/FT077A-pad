#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS	10
#define tamanho 10000
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizD;

// D = A * B + C
void *produto_matriz(void *args)
{
    long inicio;
    int numLin, numCol;

    inicio = (long) args;

    numCol = tamanho;
    numLin = (int) (tamanho / THREADS);

    for (int i=(inicio*numLin); i<numLin*(inicio+1); i++) {
        for (int j=0; j<numCol; j++) {
            int temp = 0;
            for(int k=0; k<tamanho; k++) {
                temp = temp + matrizA[posicao(i, k, tamanho)] * matrizB[posicao(k, j, tamanho)];
            }
            matrizD[posicao(i, j, tamanho)] = temp + matrizC[posicao(i, j, tamanho)];
        }
    }

    pthread_exit(NULL);
}

void *carrega_matriz(void *args)
{
    int *matriz = (int *) args;

    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
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

    // variaveis de controle para as threads
    pthread_t thd0, thd1, thd2, threads[THREADS];

    long t;         // indice identificador das threads
    void *status;   // status retorno do join das threads

    // neste momento estamos alocando espaço em memória em uma única etapa
    // as matrizes são quadradas isto pode ser observado no trecho de código abaixo
    // "tamanho * tamanho"
    matrizA = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizB = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizC = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizD = (int *) malloc(tamanho * tamanho * sizeof(int));

    // Inicia Tempo
    clock_t inicio = clock();

    // aqui criamos threads individuais para carregamento de cada Matriz
    // 3 threads, matrizes A, B e C
    pthread_create(&thd0, NULL, (void *) carrega_matriz, (void *) matrizA);
    pthread_create(&thd1, NULL, (void *) carrega_matriz, (void *) matrizB);
    pthread_create(&thd2, NULL, (void *) carrega_matriz, (void *) matrizC);

    // aqui fazemos o Join das threads de carregamento
    // neste momento sincronizamos as 3 threads
    pthread_join(thd0, &status);
    pthread_join(thd1, &status);
    pthread_join(thd2, &status);

    // aqui criamos as threads para as operações D = A * B + C
    for (t=0; t<THREADS; t++)
    {
        pthread_create(&threads[t], NULL, (void *) produto_matriz, (void *) t);
    }

    // aqui fazemos o Join das threads de operações
    // neste momento sincronizamos as threads das operações
    for (t=0; t<THREADS; t++)
    {
        pthread_join(threads[t], &status);
    }

    // Termina Tempo
    clock_t fim = clock();

    // Calcula Tempo
    double tempoProc = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo decorrido %.6fs",tempoProc);
    printf("\n");

    // printf("Matriz A\n");
    // imprime_matriz(matrizA);

    // printf("Matriz B\n");
    // imprime_matriz(matrizB);

    // printf("Matriz C\n");
    // imprime_matriz(matrizC);

    // printf("Matriz D\n");
    // imprime_matriz(matrizD);

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizD);

    return 0;
}