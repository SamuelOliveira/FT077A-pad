#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define NUM_THREADS 32
#define tamanho 1000
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizD;

// D = A * B + C
// aqui realizamos as operações entre as matrizes
void produto_matriz()
{
    int i, j, k;
    int prod = 0;

    // Não houve necessidade de sincronização com a aplicação
    // de uma diretiva de berreira pois as operações com as matrizes ocorrem
    // em uma única etapa, nas threads em execução.
    #pragma omp parallel for private(prod, i, j, k)
    for (i=0; i<tamanho; i++) {
        for (j=0; j<tamanho; j++) {
            prod = 0;
            for(k=0; k<tamanho; k++) {
                prod += matrizA[posicao(i, k, tamanho)] * matrizB[posicao(k, j, tamanho)];
            }
            matrizD[posicao(i, j, tamanho)] = prod + matrizC[posicao(i, j, tamanho)];
        }
    }
}

// aqui realizamos a leitura das matrizes
void carrega_matriz(int *args)
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            args[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }
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
    int thread_id;
    srand(time(NULL));

    // Neste momento estamos alocando espaço em memória em uma única etapa
    // as matrizes são quadradas isto pode ser observado no trecho de código abaixo
    // "tamanho * tamanho"
    matrizA = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizB = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizC = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizD = (int *) malloc(tamanho * tamanho * sizeof(int));

    // Como não estamos interessados em computar o tempo de processamento do carregamento
    // deixamos esta parte fora da contagem do tempo

    // Aqui criamos threads individuais para carregamento de cada Matriz
    // 3 threads, matrizes A, B e C
    omp_set_num_threads(3);
    #pragma omp parallel private (thread_id)
    {
        for(thread_id=0; thread_id<omp_get_max_threads(); thread_id++){
            if(thread_id == omp_get_thread_num()){
                switch (thread_id)
                {
                    case 0:
                        printf("Thread de carregamento: %d\n", thread_id);
                        carrega_matriz(matrizA);
                        break;
                    case 1:
                        printf("Thread de carregamento: %d\n", thread_id);
                        carrega_matriz(matrizB);
                        break;
                    case 2:
                        printf("Thread de carregamento: %d\n", thread_id);
                        carrega_matriz(matrizC);
                        break;
                    default:
                        break;
                }
            }
        }
        // Para garantir que um processo não ultrapasse o outro, 
        // adicionei uma diretiva de barreira no código para Sincronização
        #pragma omp barrier
    }

    // Esse metodo carrega de forma serial
    // carrega_matriz_serial();

    /**
     * Aqui redefinimos o número de threads de acordo com
     * as especificações globais em #define NUM_THREADS
     * não incluimos o tempo de criação das threads, que exige recursos do S.O.
     * Queremos computar somente o tempo de processamento das operações
     **/
    omp_set_num_threads(NUM_THREADS);

    // Inicia Tempo
    clock_t inicio = clock();

    produto_matriz();

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
