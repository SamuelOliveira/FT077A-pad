/**
 * Exemplo Geral basico.
 *
 * Prof. Andre Leon S. Gradvohl
 *
 */
#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

void *printHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit((void *) tid);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  void *status;

  // pthread_create argumentos:
  // thread : Um identificador opaco e exclusivo para o novo thread retornado pela sub-rotina.
  // attr : Um objeto de atributo opaco que pode ser usado para definir atributos de thread. Você pode especificar um objeto de atributos de thread ou NULL para os valores padrão.
  // start_routine : a rotina C que a thread executará depois de criada.
  // arg : Um único argumento que pode ser passado para start_routine. Deve ser passado por referência como um lançamento de ponteiro do tipo void. NULL pode ser usado se nenhum argumento for passado.
  for(t=0;t<NUM_THREADS;t++)
  {
    printf("Criando thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, printHello, (void *)t);

    if (rc)
    {
      printf("ERRO: retorno do pthread_create() e %d\n", rc);
      exit(-1);
    }
  }

  printf("Juntando as threads %ld\n", t);

  for(t=0;t<NUM_THREADS;t++)
  {
     rc = pthread_join(threads[t], &status);

     if (rc)
     {
       printf("ERRO: retorno do pthread_join() e %d\n", rc);
       exit(-1);
     }
     printf("Retorno do thread %ld com status %ld\n", t, (long) status);
  }

  return 0;
}

