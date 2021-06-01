#include <stdlib.h>
#include <openacc.h>

#include "consts.h"
#include "acc_paralelo.h"

// D = A * B + C
// NVIDIA Developer
// https://www.youtube.com/watch?v=KgMJzmqenuc
void produto_soma_matrizes(int *a, int *b, int *c, int *p, int *d, int N)
{
    int n = N;

    #pragma acc enter data              \
            copyin(a[0:n][0:n], b[0:n][0:n], c[0:n][0:n])  \
            create(p[0:n][0:n], d[0:n][0:n])
    {
        int i, j, k;

        #pragma acc kernels loop collapse(3) device_type(nvidia)
        for (i=0; i<n; i++){
            for (j=0; j<n; j++){
                for (k=0; k<n; k++){
                    p[posicao(i, j, n)] += a[posicao(i, k, n)] * b[posicao(k, j, n)];
                }
            }
        }

        #pragma acc kernels loop collapse(2) device_type(nvidia)
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                d[posicao(i, j, n)] = p[posicao(i, j, n)] + c[posicao(i, j, n)];
            }
        }
    }
    #pragma acc exit data       \
            copyout(d[0:n][0:n])   \
            delete(a,b,c,p)

}

