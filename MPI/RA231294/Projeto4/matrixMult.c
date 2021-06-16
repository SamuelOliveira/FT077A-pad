#define N 10
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
            args[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }
}

void print_results(char *prompt, int a[N][N]);

int main(int argc, char *argv[])
{
    int i, j, k, rank, size, tag = 99, blksz, sum = 0;
/*
    int a[N][N]={{1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7,}};
    int b[N][N]={{1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7,}};
    int c[N][N];
    int aa[N],cc[N];
*/
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


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //scatter rows of first matrix to different processes     
    MPI_Scatter(matrizA, N*N/size, MPI_INT, matrizP, N*N/size, MPI_INT,0,MPI_COMM_WORLD);

    //broadcast second matrix to all processes
    MPI_Bcast(matrizB, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            for (int k=0; k<N; k++)
                matrizP[posicao(i, j, N)] += matrizA[posicao(i, k, N)] * matrizB[posicao(k, j, N)];

          //perform vector multiplication by all processes
/*
          for (i = 0; i < N; i++)
            {
                    for (j = 0; j < N; j++)
                    {
                            sum = sum + matrizP[j] * matrizB[i][j];                
                    }
                    matrizD[i] = sum;
                    sum = 0;
            }
*/
    MPI_Gather(matrizD, N*N/size, MPI_INT, matrizC, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);        
    MPI_Finalize();
    //print_results("C = ", c);
    imprime_matriz(matrizD,N);

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizP);
    free(matrizD);

}

void print_results(char *prompt, int a[N][N])
{
    int i, j;

    printf ("\n\n%s\n", prompt);
    for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                    printf(" %d", a[i][j]);
            }
            printf ("\n");
    }
    printf ("\n\n");
}

