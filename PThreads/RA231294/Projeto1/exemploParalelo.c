#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS	32
#define tamanho 1000
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizD;

// D = A * B + C
// aqui realizamos as operações entre as matrizes
void *produto_matriz(void *args)
{
    long inicio;
    int numLin, numCol, modLin;

    modLin = 0;                         // guardar o resto da divisão linhas / trd 

    inicio = (long) args;               // separando a "fatia" da matriz para processamento

    numCol = tamanho;                   // tamanho da matriz

    numLin = (int) (tamanho / NUM_THREADS); // numero de linhas para thread

    // balanceamento da quantidade de linhas
    // aqui tratamos resto das linhas que sobraram na divisão pelas threads
    // ( se houver necessidade )
    if(NUM_THREADS == inicio+1)
    {
        modLin = (int) (tamanho % NUM_THREADS);
    }

    for (int i=(inicio*numLin); i<(numLin*(inicio+1))+modLin; i++) {
        for (int j=0; j<numCol; j++) {
            int temp = 0;
            // produto das matrizes A * B
            for(int k=0; k<tamanho; k++) {
                temp = temp + matrizA[posicao(i, k, tamanho)] * matrizB[posicao(k, j, tamanho)];
            }
            // o resultado do produto soma com C, D = P + C
            matrizD[posicao(i, j, tamanho)] = temp + matrizC[posicao(i, j, tamanho)];
        }
    }

    pthread_exit(NULL);
}

// aqui realizamos a leitura das matrizes
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

// aqui realizamos a leitura das matrizes de forma Serial
void carrega_matriz_serial()
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            matrizA[posicao(i, j, tamanho)] = rand() % 10 + 1;
            matrizB[posicao(i, j, tamanho)] = rand() % 10 + 1;
            matrizC[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }
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
    pthread_t thd0, thd1, thd2, threads[NUM_THREADS];

    long t;         // indice identificador das threads
    void *status;   // status retorno do join das threads

    // neste momento estamos alocando espaço em memória em uma única etapa
    // as matrizes são quadradas isto pode ser observado no trecho de código abaixo
    // "tamanho * tamanho"
    matrizA = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizB = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizC = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizD = (int *) malloc(tamanho * tamanho * sizeof(int));

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

    // esse metodo carrega de forma serial
    // carrega_matriz_serial();

    // Inicia Tempo
    clock_t inicio = clock();

    // aqui criamos as threads para as operações D = A * B + C
    for (t=0; t<NUM_THREADS; t++)
    {
        pthread_create(&threads[t], NULL, produto_matriz, (void *) t);
    }

    // aqui fazemos o Join das threads de operações
    // neste momento sincronizamos as threads de operações
    for (t=0; t<NUM_THREADS; t++)
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