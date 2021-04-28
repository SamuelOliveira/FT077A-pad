#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define tamanho 10000
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizD;

// D = A * B + C
void produto_matriz()
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            int temp = 0;
            for(int k=0; k<tamanho; k++) {
                temp = temp + matrizA[posicao(i, k, tamanho)] * matrizB[posicao(k, j, tamanho)];
            }
            matrizD[posicao(i, j, tamanho)] = temp + matrizC[posicao(i, j, tamanho)];
        }
    }
}

void carrega_matriz(int *args)
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            args[posicao(i, j, tamanho)] = rand() % 10 + 1;
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

    matrizA = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizB = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizC = (int *) malloc(tamanho * tamanho * sizeof(int));
    matrizD = (int *) malloc(tamanho * tamanho * sizeof(int));

    // Inicia Tempo
    clock_t inicio = clock();

    carrega_matriz(matrizA);
    carrega_matriz(matrizB);
    carrega_matriz(matrizC);

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