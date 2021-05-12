#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"
#include "consts.h"
#include "serial.h"
#include "omp_paralelo.h"

int *matrizA, *matrizB, *matrizC, *matrizD, *matrizP;

int main(int argc, char* argv[]) {
    srand(time(NULL));
      
	// Dividindo o total de threads entre as operações
    int thds_p;  // Threads para a operação produto
    int thds_s;  // Threads para a operação soma

    // Variaveis de controle para posição do parametro
    char *ret;
    char *tmp;
    char optc = 0;

    // Variaveis para os parametros e argumentos
    int tamanho = 0;    // Opcao 't'
    int threads = 0;    // Opcao 'r'
    short verbose = 0;  // Opcao 'v'
    short summary = 0;  // Opcao 's'

    // Sem argumentos
    if(argc == 1) {
        options_list();
        exit(0);
    }

    // Argumentos insuficientes
    if(argc != 4) {
        options_list();
        printf("\x1b[41mAviso:\x1b[0m\x1b[33m Argumentos insuficientes!\x1b[0m\n");
        exit(0);
    }

    // Recuperando parametros e argumentos
    // http://mindbending.org/pt/argumentos-e-parametros-em-c
    // https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/?ref=rp
    while((optc = getopt(argc, argv, "t:vr:s")) != -1) {
        switch(optc) {
            case 'v' : // Verbose
                verbose = 1;
                break;
            case 's' : // Summary
                summary = 1;
                break;
            case 'r' : // Threads
                tmp = argv[1];
                ret = strstr(tmp, "rt");
                if(ret) {
                    threads = atoi(argv[2]);
                    tamanho = atoi(argv[3]);
                }
                break;
            case 't' : // Tamanho
                tmp = argv[1];
                ret = strstr(tmp, "tr");
                if(ret) {
                    tamanho = atoi(argv[2]);
                    threads = atoi(argv[3]);
                }
                break;
            default : // Qualquer parametro nao tratado
                printf("Parametros incorretos.\n");
                exit(0);
        }
    }

    // Threads insuficientes
	// Menos de 2 Threads é um Processo Serial
    if(threads < 2) {
        options_list();
        printf("\x1b[41mAviso:\x1b[0m\x1b[33m Threads insuficientes!\x1b[0m\n");
        exit(0);
    }

    // neste momento estamos alocando espaço em memória
    // as matrizes são quadradas
    matrizA = aloca_matriz(tamanho);
    matrizB = aloca_matriz(tamanho);
    matrizC = aloca_matriz(tamanho);
    matrizD = aloca_matriz(tamanho);
    matrizP = aloca_matriz(tamanho);

    // como não estamos interessados em computar o tempo do carregamento
    // deixamos esta parte fora da contagem do tempo
    carrega_matriz(matrizA,tamanho);
    carrega_matriz(matrizB,tamanho);
    carrega_matriz(matrizC,tamanho);
    carrega_matriz(matrizD,tamanho);

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

    // obs.:    Dividimos a quantidade total de threads entre as duas operações
    //          Prevenimos a quantidade de threads informada ser um numero primo realizamos a divisão
    //          por módulo do numero de threads e acrescentamos o resto a etapa 'produto_matriz_paralelo'
    thds_s = (int) (threads / 2);
    thds_p = thds_s + ((int) (threads % 2));

    // Inicia Tempo. Processo Paralelo
    clock_t inicioParalelo = clock();

    // Aqui ralizamos as operaçãoes com as matrizes
    // dentro da função criamos a área para paralelização

    // operações com as matrizes, produto
    produto_matriz_omp(matrizA,matrizB,matrizP,tamanho,thds_p);

    // operações com as matrizes, soma
    soma_matriz_omp(matrizP,matrizC,matrizD,tamanho,thds_s);

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
        printf("  Threads:  \x1b[33m%d\x1b[0m\n",threads);
        printf("  SpeedUp:  \x1b[33m%.6fs\x1b[0m\n",speedup);
        printf("  Matriz:   \x1b[33m%dx%d\x1b[0m\n",tamanho, tamanho);
        printf("  Serial:   \x1b[33m%.6fs\x1b[0m\n",tempoSerial);
        printf("  Paralelo: \x1b[33m%.6fs\x1b[0m\n",tempoParalelo);
        printf("\n");
    }

    free(matrizA);
    free(matrizB);
    free(matrizC);
    free(matrizD);
    free(matrizP);
}
