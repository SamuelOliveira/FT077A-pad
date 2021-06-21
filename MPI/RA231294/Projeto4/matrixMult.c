#define N 10
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"

#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizP, *matrizD;

double speed_up(double ts, double tp)
{
    return ts/tp;
}

void imprime_matriz(int *args, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        for(int j = 0; j < tamanho; j++)
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

int *aloca_matriz(int tamanho) {
    return (int *) malloc(tamanho * tamanho * sizeof(int));
}

void carrega_matriz(int *args, int tamanho)
{
    for (int i=0; i < tamanho; i++) {
        for (int j=0; j < tamanho; j++) {
            args[posicao(i, j, tamanho)] = 2;
        }
    }
}

void print_results(char *prompt, int a[N][N]);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int i, j, k, rank, size, tag = 99, blksz, sum = 0, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    matrizA = aloca_matriz(N);
    matrizB = aloca_matriz(N);
    matrizC = aloca_matriz(N);
    matrizP = aloca_matriz(N);
    matrizD = aloca_matriz(N);

    // como não estamos interessados em computar o tempo do carregamento
    // deixamos esta parte fora da contagem do tempo
    carrega_matriz(matrizA,N);
    carrega_matriz(matrizB,N);
    carrega_matriz(matrizC,N);
    carrega_matriz(matrizD,N);
    carrega_matriz(matrizP,N);


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //scatter rows of first matrix to different processes
    MPI_Scatter(matrizA, N*N/size, MPI_INT, matrizP, N*N/size, MPI_INT,0,MPI_COMM_WORLD);

    //broadcast second matrix to all processes
    MPI_Bcast(matrizB, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    //perform vector multiplication by all processes
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            for (int k=0; k<N; k++)
                matrizP[posicao(i, j, N)] += matrizA[posicao(i, k, N)] * matrizB[posicao(k, j, N)];

    MPI_Gather(matrizD, N*N/size, MPI_INT, matrizC, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);

    // Obtem o nome do processador (nome da maquina onde o processo sera executado)
    MPI_Get_processor_name(hostname, &len);
    printf ("Numero de tarefas = %d Meu rank= %d Rodando em %s\n", size,rank,hostname);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    if(rank==0) imprime_matriz(matrizP,N);

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizP);
    free(matrizD);

}
