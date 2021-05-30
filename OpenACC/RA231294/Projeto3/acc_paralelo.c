#include <stdlib.h>
#include <openacc.h>

#include "consts.h"
#include "acc_paralelo.h"

// D = A * B + C
void produto_soma_matrizes(int *a, int *b, int *c, int *p, int *d, int n)
{
    #pragma acc parallel enter data             \
            device_type(nvidia)                 \
            copyin(a[:n∗n], b[:n∗n], c[:n∗n]),  \
            create(p[:n∗n], d[:n∗n])
    {
        int i, j, k;

        #pragma acc loop collapse(3)
        for (i=0; i<n; i++){
            for (j=0; j<n; j++){
                for (k=0; k<n; k++){
                    p[posicao(i, j, n)] += a[posicao(i, k, n)] * b[posicao(k, j, n)];
                }
            }
        }

        #pragma acc loop collapse(2)
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                d[posicao(i, j, n)] = p[posicao(i, j, n)] + c[posicao(i, j, n)];
            }
        }
    }
    #pragma acc exit data copyout(d[:n∗n]) delete(a,b,c,p)
}