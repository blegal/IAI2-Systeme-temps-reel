#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <cassert>
#include <fcntl.h>

//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
int pipe_1[2]; // File descriptor for creating a SINGLE pipe
int pipe_2[2]; // File descriptor for creating a SINGLE pipe
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
bool keepRunning = true;
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
    assert( write (pipe_1[1], &ch,1) == 1);
    printf ("Writer send : %c\n", ch);
    ch = (ch == 'Z') ? 'A' : ch + 1;
    sleep( 1 );
  }

  //
  // On envoie une commande de terminaison au thread suivant
  // avant de quitter
  //
  ch = '1';
  assert(write (pipe_1[1], &ch,1) == 1);

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
void* reverser(void* arg)
{
	printf("Début du thread [reverser]\n");
  char tab[26];
  while( true )
  {
    for(int i = 0; i < 26; i+= 1)
    {
      assert( read (pipe_1[0], tab + i, 1) == 1 );
      if( tab[i] == '1')                            // Si l'on revoit le char 1, cela signifie que l'on
      {                                             // doit s'arreter de fonctionner
        assert(write (pipe_2[1], tab + i, 1) == 1); // On envoie le message de fin au thread suivant
        printf("Fin du thread [reverser]\n");
        pthread_exit(NULL);
      }
    }
    for(int i = 0; i < 26; i+= 1)
    {
      assert( write (pipe_2[1], tab + 25 - i, 1) == 1 );
    }
  }

  //
  // On envoie une commande de terminaison au thread suivant
  // avant de quitter
  //

	printf("Fin du thread [reverser]\n");
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
    assert(read (pipe_2[0], &ch, 1) == 1);

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
  pthread_t tid3;

  assert( pipe (pipe_1) >= 0);
  assert( pipe (pipe_2) >= 0);

#ifndef __APPLE__
  fcntl(pipe_1[1], F_SETPIPE_SZ, 4);
  fcntl(pipe_2[1], F_SETPIPE_SZ, 4);
#endif

  pthread_create(&tid1, NULL, consumer, NULL);

  pthread_create(&tid2, NULL, reverser, NULL);

  pthread_create(&tid3, NULL, producer, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//