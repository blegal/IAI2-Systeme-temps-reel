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
// Structure de données contenant le mutex
typedef struct mutex_data
{
	char values[5] = { 0 };
    int  nElements = 0;
    char signal_id = 0;

	pthread_mutex_t mutex_1;
	pthread_mutex_t mutex_2;
	pthread_mutex_t mutex_3;

    pthread_t thread_0;
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;

    bool stop_request = false;

} mutex_data;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Fonction exécutée dans le thread
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
	if (pthread_mutex_init(&md.mutex_1, NULL) != 0) {
		printf("\n mutex_1 init failed\n");
		return EXIT_FAILURE;
	}
	if (pthread_mutex_init(&md.mutex_2, NULL) != 0) {
		printf("\n mutex_2 init failed\n");
		return EXIT_FAILURE;
	}
	if (pthread_mutex_init(&md.mutex_3, NULL) != 0) {
		printf("\n mutex_3 init failed\n");
		return EXIT_FAILURE;
	}

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

	//
	// Destruction du mutex
	//

	pthread_mutex_destroy(&md.mutex_1);
	pthread_mutex_destroy(&md.mutex_2);
	pthread_mutex_destroy(&md.mutex_3);

	return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//