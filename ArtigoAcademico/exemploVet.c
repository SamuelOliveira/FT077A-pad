#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define tamanho 3

typedef struct
{
    char *car;
    int peso;    
} Cell;

int soma_faixa(Cell cell[]) {
    int soma = 0;

    // varre lista
    for (int i = 0; i < tamanho; i++)
    {
        int k = 0;  // controla while
        int f = 0;  // acha repetição
        char oldChar, newChar;

        char *car = cell[i].car;
        int peso = cell[i].peso;

        printf("Elemento %d Car = %s, Peso %d\n", i, car, peso);

        // varre até o final da string/char, testa nulo
        while (car[k] != '\0')
        {
            newChar = car[k];

            // verifica char repetido
            if(newChar == oldChar) f = 1;

            oldChar = newChar;
            k++;
        }

        // se achou repetição soma
        if(f != 0) soma = soma + peso;

        f = 0;
    }

    return soma;
}

int main () {
    int vSoma;
    Cell cell;
    Cell lista[tamanho];

    srand(time(NULL));              // Inicializa semente randomica

    cell.car = "yzya";
    cell.peso = rand() % 10 + 1;    // Peso randomico
    lista[0] = cell;

    cell.car = "google";
    cell.peso = rand() % 10 + 1;    // Peso randomico
    lista[1] = cell;

    cell.car = "feel the bass";
    cell.peso = rand() % 10 + 1;    // Peso randomico
    lista[2] = cell;

    vSoma = soma_faixa(lista);

    printf("A soma é %d\n",vSoma);

    return 0;
}