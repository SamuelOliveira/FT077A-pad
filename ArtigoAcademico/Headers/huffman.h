#ifndef __HUFFMAN_H_
#define __HUFFMAN_H_

/**
* huffman.c
* Um simples compressor de arquivos usando árvores de Huffman.
* @ver 0.1
* @autores: Fabrício Soares
*/
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** Definição do tipo de dados 'byte'
* 'unsigned char': É o tipo que consegue gravar no intervalo que vai de 0 a 255 bytes
*/
typedef unsigned char byte;

/** Definição da árvore */
typedef struct nodeArvore
{
    int                 frequencia;
    byte                c;
    struct nodeArvore   *esquerda;
    struct nodeArvore   *direita;
} nodeArvore;

/** Definição da fila de prioridade (implementada como lista simplesmente encadeada) */

typedef struct nodeLista
{
    nodeArvore          *n;
    struct nodeLista    *proximo;
} nodeLista;

typedef struct lista
{
    nodeLista   *head;
    int         elementos;
} lista;


double CompressName(const char *arquivoEntrada, const char *arquivoSaida);

/** Função que faz alocação de memória e trata os ponteiros soltos acerca de nós da lista encadeada.
* Obs: cada nó da lista encadeada é conectado a um nó 'raiz' de árvore.
* @param: um nó de uma árvore.
*/
nodeLista *novoNodeLista(nodeArvore *nArv);

/** Função que faz alocação de memória e trata os ponteiros soltos acerca de nós da árvore
* @param: o byte a ser gravado no nó, a frequencia do byte, ponteiros para os nós filhos
*/
nodeArvore *novoNodeArvore(byte c, int frequencia, nodeArvore *esquerda, nodeArvore *direita);

/** Função que um novo nó na lista encadeada que representa a fila de prioridade.
* @param: um nó previamente criado, a lista que receberá o nó
*/
void insereLista(nodeLista *n, lista *l);

/** Função que 'solta' o nó apontado por 'head' da lista (o de menor frequência)
* (faz backup do nó e o desconecta da lista)
* @param: uma lista encadeada.
*/
nodeArvore *popMinLista(lista *l);

/** Função que conta a frequência de ocorrências dos bytes de um dado arquivo
* @param: um arquivo, uma lista de bytes
*/
void getByteFrequency(FILE *entrada, unsigned int *listaBytes);

//  Obtem o código começando no nó n, utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket 'tamanho'

/**
/ Função recursiva que percorre uma árvore de huffman e para ao encontrar o byte procurado (c)
/ @param: nó para iniciar a busca, byte a ser buscado, buffer para salvar os nós percorridos, posição para escrever
**/
bool pegaCodigo(nodeArvore *n, byte c, char *buffer, int tamanho);

// Algoritmo para construir a árvore de huffman, inspirado no seguinte pseudocódigo:
// http://www.cs.gettysburg.edu/~ilinkin/courses/Spring-2014/cs216/assignments/a8.html
//
// procedure BUILD-TREE(frequencies):
//     pq ← make empty priority queue
//     for each (symbol, key) in frequencies:
//         h ← make a leaf node for the (symbol, key) pair
//         INSERT(pq, h)
//
//     n ← size[pq]
//     for i = 1 to n-1:
//         h1 ← POP-MIN(pq)
//         h2 ← POP-MIN(pq)
//         h3 ← MAKE-NODE(h1, h2)
//         INSERT(pq, h3)
//
//     return POP-MIN(pq)

/** Função que constrói a árvore de huffman
* @param: a fila de prioridade.
*/
nodeArvore *BuildHuffmanTree(unsigned *listaBytes);

/** Função que libera memória da árvore de huffman
* @param: nó de uma (sub)árvore.
*/
void FreeHuffmanTree(nodeArvore *n);

/** Função que faz bitmasking no byte lido e retorna um valor booleano confirmando sua existência
* Ideia do bitmasking surgiu da leitura de http://ellard.org/dan/www/CS50-95/s10.html
* @param: arquivo para ler o byte, posição que se deseja mascarar o byte, byte a ser feita a checagem
*/
int geraBit(FILE *entrada, int posicao, byte *aux );

/** Função para notificar ausência do arquivo. Encerra o programa em seguida.
*/
void erroArquivo();

/** Função que comprime um arquivo utilizando a compressão de huffman
* @param: arquivo a comprimir, arquivo resultado da compressão
*/
void CompressFile(const char *arquivoEntrada, const char *arquivoSaida);

/** Função que descomprime um arquivo utilizando a compressão de huffman
* @param: arquivo a descomprimir, arquivo resultado da descompressão
*/
void DecompressFile(const char *arquivoEntrada, const char *arquivoSaida);

#endif /* HUFFMAN_H_ */