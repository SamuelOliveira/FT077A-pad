#include <stdio.h>
#include <omp.h>

#define tamanho 100

int main ()  
{
 int   i, chunk;
 float a[tamanho], b[tamanho], result;

 /* Some initializations */
 chunk = 10;
 result = 0.0;

 for (i=0; i < tamanho; i++)
 {
   a[i] = i * 1.0;
   b[i] = i * 2.0;
 }

#pragma omp parallel for      \
   default(shared) private(i)  \
   schedule(static,chunk)      \
   reduction(+:result)
   for (i=0; i < tamanho; i++)
      result = result + (a[i] * b[i]);

 printf("Final result= %f\n",result);

}
