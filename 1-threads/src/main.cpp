/**
 * 
 * Bertrand LE GAL (bertrand.le-gal@irisa.fr)
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
const long NT = 12;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
struct pthread_arg_t {
   int value;
};
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* task(void* arg)
{
   const int thread_id = ((pthread_arg_t*)arg)->value;
   usleep( rand()%5000000 );
   printf("Hello World from thread n°%d\n", 1 + thread_id);
   pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
int main(int argc,char** argv)
{
   srand(time(NULL));

   pthread_t     threads[NT]; // tableau permettant de mémoriser l'identifiant des threads
   pthread_arg_t argumts[NT]; // tableau contenant les parametres passés aux threads

   printf("(II) The main program starts\n");

   //
   // On cree les NT threads
   //
   for(int i = 0; i < NT; i += 1)
   {
      argumts[i].value = i;
      const int resu   = pthread_create(&threads[i], NULL, task, (void*)&argumts[i]);
      if (resu != 0)
      {
         printf("(EE) Thread creation failed (n°%d)\n", i);
         return EXIT_FAILURE;
      }
   }

   //
   // On attend que tous les threads soient terminés
   //
   for(int i = 0; i < NT; i += 1)
   {
      pthread_join(threads[i], NULL);
   }

   printf("(II) The main program ends\n");

   return 0;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//