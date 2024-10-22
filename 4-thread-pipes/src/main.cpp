#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <cassert>
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
int fd[2]; // File descriptor for creating a SINGLE pipe
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
static volatile bool keepRunning = true;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void CRTL_C_handler(int dummy)
{
    keepRunning = false;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* producer(void* arg)
{
	printf("Début du thread [producer]\n");
  char ch = 'A';
  while( keepRunning == true )
  {
    assert(write (fd[1], &ch,1) == 1);
    printf ("Writer send : %c\n", ch);
    ch = (ch == 'Z') ? 'A' : ch + 1;
    sleep( 1 );
  }

  //
  // On envoie une commande de terminaison au thread suivant
  // avant de quitter
  //
  ch = '1';
  assert(write (fd[1], &ch,1) == 1);

	printf("Fin du thread [producer]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* consumer(void* arg)
{
	printf("Début du thread [consumer]\n");
  char ch;
  while( true )
  {
    assert( read (fd[0], &ch, 1) == 1 );

    if( ch == '1')  // Si l'on revoit le char 1, cela signifie que l'on
      break;        // doit s'arreter de fonctionner

    printf ("Reader rcvd : %c\n", ch);
  }
	printf("Fin du thread [consumer]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
int main()
{

  signal(SIGINT, CRTL_C_handler);

  pthread_t tid1;
  pthread_t tid2;

  assert( pipe (fd) >= 0);

  pthread_create(&tid1, NULL, consumer, NULL);
  pthread_create(&tid2, NULL, producer, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//