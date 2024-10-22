#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Nombre total de thread
#define NB_THREAD 4
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Tableau contenant les threads
pthread_t threads[NB_THREAD];
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Structure de données contenant le mutex
typedef struct mutex_data
{
	bool end_request = false;
	char data = 'A';
	pthread_mutex_t mutex_1;
	pthread_mutex_t mutex_2;
	pthread_mutex_t mutex_3;
	pthread_mutex_t mutex_4;

} mutex_data;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_1(void *arg)
{
	printf("Début du thread [1]\n");

		mutex_data *md = (mutex_data*) arg;

	while ( md->end_request == false )
	{
		// Vérouillage du mutex
		pthread_mutex_lock( &(md->mutex_1 ));

		// On affiche la lettre de l'alphabet
		printf("thread [1] : letter = [%c]\n", md->data);
		md->data = (md->data == 'Z') ? 'A' : md->data + 1;

		// Pause l'exécution du thread pendant 1 seconde
		sleep(1);

		// Dévérouillage du mutex du thread suivant
		pthread_mutex_unlock( &(md->mutex_2) );
	}
	printf("Fin du thread [1]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_2(void *arg)
{
	printf("Début du thread [2]\n");

	mutex_data *md = (mutex_data*) arg;

	while ( md->end_request == false )
	{
		// Vérouillage du mutex
		pthread_mutex_lock( &(md->mutex_2 ));

		// On affiche la lettre de l'alphabet
		printf("thread [2] : letter = [%c]\n", md->data);
		md->data = (md->data == 'Z') ? 'A' : md->data + 1;

		// Pause l'exécution du thread pendant 1 seconde
		sleep(1);

		// Dévérouillage du mutex du thread suivant
		pthread_mutex_unlock( &(md->mutex_3) );
	}

	printf("Fin du thread [2]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_3(void *arg)
{
	printf("Début du thread [3]\n");

	mutex_data *md = (mutex_data*) arg;

	while ( md->end_request == false )
	{
		// Vérouillage du mutex
		pthread_mutex_lock( &(md->mutex_3 ));

		// On affiche la lettre de l'alphabet
		printf("thread [3] : letter = [%c]\n", md->data);
		md->data = (md->data == 'Z') ? 'A' : md->data + 1;

		// Pause l'exécution du thread pendant 1 seconde
		sleep(1);

		// Dévérouillage du mutex du thread suivant
		pthread_mutex_unlock( &(md->mutex_4) );
	}
	printf("Fin du thread [3]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_4(void *arg)
{
	printf("Début du thread [4]\n");

	mutex_data *md = (mutex_data*) arg;

	while ( md->end_request == false )
	{
		// Vérouillage du mutex
		pthread_mutex_lock( &(md->mutex_4 ));

		// On affiche la lettre de l'alphabet
		printf("thread [4] : letter = [%c]\n", md->data);
		md->data = (md->data == 'Z') ? 'A' : md->data + 1;

		// Pause l'exécution du thread pendant 1 seconde
		sleep(1);

		// Dévérouillage du mutex du thread suivant
		pthread_mutex_unlock( &(md->mutex_1) );
	}
	printf("Fin du thread [4]\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Fonction principale
int main()
{

	//
	// Création de la structure de données
	//
	mutex_data md;

	//
	// Initialisation du mutex
	//
	assert( pthread_mutex_init(&md.mutex_1, NULL) == 0);
	assert( pthread_mutex_init(&md.mutex_2, NULL) == 0);
	assert( pthread_mutex_init(&md.mutex_3, NULL) == 0);
	assert( pthread_mutex_init(&md.mutex_4, NULL) == 0);

	pthread_mutex_lock( &md.mutex_2 );
	pthread_mutex_lock( &md.mutex_3 );
	pthread_mutex_lock( &md.mutex_4 );

	//
	// Initialisation du mutex
	//
	assert( pthread_create(&threads[0], NULL, thread_1, &md) == 0);
	assert( pthread_create(&threads[1], NULL, thread_2, &md) == 0);
	assert( pthread_create(&threads[2], NULL, thread_3, &md) == 0);
	assert( pthread_create(&threads[3], NULL, thread_4, &md) == 0);

	//
	// En attente des threads
	//
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);

	//
	// Destruction du mutex
	//

	pthread_mutex_destroy(&md.mutex_1);
	pthread_mutex_destroy(&md.mutex_2);
	pthread_mutex_destroy(&md.mutex_3);
	pthread_mutex_destroy(&md.mutex_4);

	return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//