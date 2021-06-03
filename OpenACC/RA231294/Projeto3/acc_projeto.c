#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <openacc.h>

#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))

int *matrizA, *matrizB, *matrizC, *matrizP, *matrizD;

/**
 * @brief Alocando uma matriz quadrada
 */
int *aloca_matriz(int tamanho);

/**
 * @brief Carrega uma matriz quadrada de forma serial
 */

void carrega_matriz(int *args, int tamanho);

/**
 * @brief Imprimindo uma matriz quadrada
 */
void imprime_matriz(int *args, int tamanho);

double speed_up(double ts, double tp);

void options_list();

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_serial(int *a, int *b, int *r, int tamanho);

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_serial(int *a, int *b, int *r, int tamanho);

/**
 * @brief Operações com matrizes, Paralelização, D = A * B + C
 */
void produto_soma_matrizes(int *a, int *b, int *c, int *p, int *d, int n);

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // Variaveis de controle para posição do parametro
    char *ret;
    char *tmp;
    char optc = 0;

    // Variaveis para os parametros e argumentos
    int tamanho = 0;    // Opcao 't'
    short verbose = 0;  // Opcao 'v'
    short summary = 0;  // Opcao 's'

    // Sem argumentos
    if(argc == 1) {
        options_list();
        exit(0);
    }

    // Argumentos insuficientes
    if(argc != 3) {
        options_list();
        printf("\x1b[41mAviso:\x1b[0m\x1b[33m Argumentos insuficientes!\x1b[0m\n");
        exit(0);
    }

    // Recuperando parametros e argumentos
    while((optc = getopt(argc, argv, "t:vs")) != -1) {
        switch(optc) {
            case 'v' : // Verbose
                verbose = 1;
                break;
            case 's' : // Summary
                summary = 1;
                break;
            case 't' : // Tamanho
                tmp = argv[1];
                ret = strstr(tmp, "t");
                if(ret) {
                    tamanho = atoi(argv[2]);
                }
                break;
            default : // Qualquer parametro nao tratado
                printf("Parametros incorretos.\n");
                exit(0);
        }
    }

    // neste momento estamos alocando espaço em memória
    // as matrizes são quadradas
    matrizA = aloca_matriz(tamanho);
    matrizB = aloca_matriz(tamanho);
    matrizC = aloca_matriz(tamanho);
    matrizP = aloca_matriz(tamanho);
    matrizD = aloca_matriz(tamanho);

    // como não estamos interessados em computar o tempo do carregamento
    // deixamos esta parte fora da contagem do tempo
    carrega_matriz(matrizA,tamanho);
    carrega_matriz(matrizB,tamanho);
    carrega_matriz(matrizC,tamanho);

    // Inicia Tempo. Processo Serial
    clock_t inicioSerial = clock();

    // operações com as matrizes, produto
    produto_matriz_serial(matrizA,matrizB,matrizP,tamanho);

    // operações com as matrizes, soma
    soma_matriz_serial(matrizP,matrizC,matrizD,tamanho);

    // Termina Tempo
    clock_t fimSerial = clock();

    // Calcula tempo
    double tempoSerial = (double)(fimSerial - inicioSerial) / CLOCKS_PER_SEC;

    // Inicia Tempo. Processo Paralelo
    clock_t inicioParalelo = clock();

    // Aqui ralizamos as operaçãoes com as matrizes
    // dentro da função criamos a área para paralelização
    // operações com as matrizes, produto e soma
    produto_soma_matrizes(matrizA,matrizB,matrizC,matrizP,matrizD,tamanho);

    // Termina tempo
    clock_t fimParalelo = clock();

    // Calcula Tempo
    double tempoParalelo = (double)(fimParalelo - inicioParalelo) / CLOCKS_PER_SEC;

    double speedup = speed_up(tempoSerial, tempoParalelo);

    // Imprime matrizes
    if(verbose == 1 && tamanho <= 10) {
        imprime_matriz(matrizA,tamanho);
        imprime_matriz(matrizB,tamanho);
        imprime_matriz(matrizC,tamanho);
        imprime_matriz(matrizD,tamanho);
    }

    // Imprime resumos do processamento
    if(summary == 1) {
        printf("\n");
        printf("\x1b[41mResumo\x1b[0m\n");
        printf("  SpeedUp:  \x1b[33m%.6fs\x1b[0m\n",speedup);
        printf("  Matriz:   \x1b[33m%dx%d\x1b[0m\n",tamanho, tamanho);
        printf("  Serial:   \x1b[33m%.6fs\x1b[0m\n",tempoSerial);
        printf("  Paralelo: \x1b[33m%.6fs\x1b[0m\n",tempoParalelo);
    }

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizP);
    free(matrizD);
}

/**
 * @brief Alocando uma matriz quadrada
 */
int *aloca_matriz(int tamanho) {
    return (int *) malloc(tamanho * tamanho * sizeof(int));
}

/**
 * @brief Carrega uma matriz quadrada de forma serial
 */
void carrega_matriz(int *args, int tamanho)
{
    for (int i=0; i < tamanho; i++) {
        for (int j=0; j < tamanho; j++) {
            args[posicao(i, j, tamanho)] = rand() % 10 + 1;
        }
    }
}

/**
 * @brief Imprimindo uma matriz quadrada
 */
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

double speed_up(double ts, double tp)
{
    return ts/tp;
}

void options_list()
{
    printf("\n");
    printf("\x1b[41mOpções\x1b[0m\n");
    printf("  *\x1b[33m -t\x1b[0m - Tamanho da Matriz Quadrada\n");
    printf("  *\x1b[33m -s\x1b[0m - (opcional) Imprime Resumo do Processamento\n");
    printf("  *\x1b[33m -v\x1b[0m - (opcional) Imprime Matrizes para Verificação, t<=10\n");
    printf("\n\x1b[36mNo mínimo um parâmetro com argumento deve ser fornecido!\x1b[0m\n");
    printf("\n");
}

/**
 * @brief Produtos de matrizes, r = a * b
 */
void produto_matriz_serial(int *a, int *b, int *r, int tamanho)
{
    int tot;

    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            tot = 0;
            for(int k=0; k<tamanho; k++) {
                tot += a[posicao(i, k, tamanho)] * b[posicao(k, j, tamanho)];
            }
            r[posicao(i, j, tamanho)] = tot;
        }
    }
}

/**
 * @brief Soma de matrizes, r = a + b
 */
void soma_matriz_serial(int *a, int *b, int *r, int tamanho)
{
    for (int i=0; i<tamanho; i++) {
        for (int j=0; j<tamanho; j++) {
            r[posicao(i, j, tamanho)] = a[posicao(i, j, tamanho)] + b[posicao(i, j, tamanho)];
        }
    }
}

/**
 * @brief Operações com matrizes, Paralelização, D = A * B + C
 */
void produto_soma_matrizes(int *a, int *b, int *c, int *p, int *d, int n)
{

    #pragma acc parallel loop collapse(3)   \
            copyin(a[:n*n], b[:n*n])        \
            copy(p[:n*n])
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++)
                p[posicao(i, j, n)] += a[posicao(i, k, n)] * b[posicao(k, j, n)];

    #pragma acc parallel loop collapse(2)   \
            copyin(c[:n*n], p[:n*n])        \
            copy(d[:n*n])
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            d[posicao(i, j, n)] = p[posicao(i, j, n)] + c[posicao(i, j, n)];

}

