#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define MAT_SIZE 8

void initialiseMatricies(int a[][MAT_SIZE], int b[][MAT_SIZE], int c[][MAT_SIZE])
{
    int num = 11;
    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            a[i][j] = num;
            b[i][j] = num+1;
            c[i][j] = 0;
        }
        num++;
    }
}

void print_results(int a[MAT_SIZE][MAT_SIZE])
{
    int i, j;

    for (i = 0; i < MAT_SIZE; i++) {
            for (j = 0; j < MAT_SIZE; j++) {
                    printf(" %d", a[i][j]);
            }
            printf ("\n");
    }
    printf ("\n\n");
}

int main(int argc, char **argv)
{   
    // MPI Variables
    int rank, size;

    // Create the main matrices with the predefined size
    int matrixA[MAT_SIZE][MAT_SIZE];
    int matrixB[MAT_SIZE][MAT_SIZE];
    int matrixC[MAT_SIZE][MAT_SIZE];

    // Create the separate arrays for storing the scattered rows from the main matrices
    int matrixARows[MAT_SIZE / size][MAT_SIZE];
    int matrixCRows[MAT_SIZE / size][MAT_SIZE];


    // Initialise the matrices
    initialiseMatricies(matrixA, matrixB, matrixC);

    // Start the MPI parallel sequence
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //int count = MAT_SIZE * MAT_SIZE / (size * (MAT_SIZE / size));
    int count = MAT_SIZE * MAT_SIZE / size;

    // Scatter rows of first matrix to different processes
    MPI_Scatter(matrixA, count, MPI_INT, matrixARows, count, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast second matrix to all processes
    MPI_Bcast(matrixB, MAT_SIZE * MAT_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    // Matrix Multiplication
    int sum = 0;
    for (int k = 0; k < MAT_SIZE/size; k++)
    {
      for (int i = 0; i < MAT_SIZE; i++)
      {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            sum += matrixARows[k][j] * matrixB[j][i];
        }
        matrixCRows[k][i] = sum;
        sum = 0;
      }
    }

    // Gather the row sums from the buffer and put it in matrix C
    MPI_Gather(matrixCRows, count, MPI_INT, matrixC, count, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

    // if it's on the master node
    if (rank == 0) print_results(matrixC);

    return 0;
}
