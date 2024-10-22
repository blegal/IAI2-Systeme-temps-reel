#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Structure de données partagée par les threads
typedef struct mutex_data {
	char values[5] = { 0 };
    int  nElements = 0;

	int pipe_1[2];
	int pipe_2[2];
	int pipe_3[2];

    pthread_t thread_0;
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;
} mutex_data;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_keyboard(void *arg)
{
	printf("(II) Starting thread_keyboard\n");
	mutex_data *md = (mutex_data*) arg;


	printf("(II) Ending thread_keyboard\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_store(void *arg)
{
	printf("(II) Starting thread_store\n");
	mutex_data *md = (mutex_data*) arg;


	printf("(II) Ending thread_store\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_clear(void *arg)
{
	printf("(II) Starting thread_clear\n");
	mutex_data *md = (mutex_data*) arg;


	printf("(II) Ending thread_clear\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_show(void *arg)
{
	printf("(II) Starting thread_show\n");
	mutex_data *md = (mutex_data*) arg;


	printf("(II) Ending thread_show\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Fonction principale
int main() {

	//
	// Création de la structure de données
	//
	mutex_data md;

	//
	// Initialisation des 5 données
	//
    md.nElements = 0;
	bzero( md.values, 6);

	//
	// Initialisation du mutex
	//
	int result = pipe (md.pipe_1);
   	if (result < 0){ perror("pipe "); exit(1); }

	result = pipe (md.pipe_2);
   	if (result < 0){ perror("pipe "); exit(1); }

	result = pipe (md.pipe_3);
   	if (result < 0){ perror("pipe "); exit(1); }

	//
	// Boucle de création des threads
	//

	int err = pthread_create(&(md.thread_0), NULL, thread_keyboard, &md);
	if (err != 0) {
		printf("Echec de la création du thread: [%s]", strerror(err));
        exit( EXIT_FAILURE );
	}

	err = pthread_create(&(md.thread_1), NULL, thread_store, &md);
	if (err != 0) {
		printf("Echec de la création du thread: [%s]", strerror(err));
        exit( EXIT_FAILURE );
	}

	err = pthread_create(&(md.thread_2), NULL, thread_clear, &md);
	if (err != 0) {
		printf("Echec de la création du thread: [%s]", strerror(err));
        exit( EXIT_FAILURE );
	}

	err = pthread_create(&(md.thread_3), NULL, thread_show, &md);
	if (err != 0) {
		printf("Echec de la création du thread: [%s]", strerror(err));
        exit( EXIT_FAILURE );
	}


	//
	// En attente de la completion de l'ensemble des threads
	//

	pthread_join(md.thread_0, NULL);
	pthread_join(md.thread_1, NULL);
	pthread_join(md.thread_2, NULL);
	pthread_join(md.thread_3, NULL);

	return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//