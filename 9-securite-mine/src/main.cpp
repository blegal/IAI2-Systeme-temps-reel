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
typedef struct shared_data {

	//
	// LISTE DES EVENEMENTS POUVANT ETRE ECHANGES ENTRE
	// LE CONTROLEUR DE LA MINE ET LES AUTRES PROCESSUS
	// DE TRAITEMENT
	//


	//
	// LA FILE DE MESSAGE PERMETTANT L'ECHANGE D'INFO
	//


	//
	// LES DIFFERENTS NIVEAUX PREDETERMINES
	//

	const int NIV_EAU_HAUT  =  300;
	const int NIV_EAU_BAS   =  100;
	const int NIV_METH_HAUT = 1000;
	const int NIV_METH_BAS  =  300;

	//
	// VARIABLES PARTAGEE CORRESPONDANT AUX E/S DU SYSTEME
	//

	int NIV_EAU            =  200;
	int NIV_METH           =    0;

	//
	// LA FILE DE MESSAGE PERMETTANT L'ECHANGE D'INFO
	//

    pthread_t thread_0;
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;
    pthread_t thread_4;

	//
	// LES MUTEX QUI VONT PERMETTRE DE FAIRES LES ENABLEs
	//


	//
	// LES BOOL PARTAGES POUR FAIRE LES
	//


	//
	// LE BOOL PARTAGE CLORE L'EXECUTION DU SYSTEME
	//

	bool exit_cmd       = false;

	//
	// LA VALEUR INDIQUANT LA VALEUR DE L'ALARME
	//

	int  alarm_level    = 1;

} shared_data;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_keyboard(void *arg)
{
	printf("(II) Starting thread_controleur\n");
	shared_data *md = (shared_data*) arg;

	// ( c == 's' ) 				: start the system
    // ( c == 'S' ) 				: stop  the system
	// (c == 'm') || (c == 'M') )	: increase methane level by 50
	// (c == 'e') || (c == 'E') )	: increase water   level by 50
	// (c == 'i') || (c == 'I') )	: printf methane and water level (for debug)
	// (c == 'f') || (c == 'F') )	: close the application

	printf("(II) Ending thread_keyboard\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
void* thread_controleur(void *arg)
{
	printf("(II) Starting thread_controleur\n");
	shared_data *md = (shared_data*) arg;


	printf("(II) Ending thread_controleur\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_methane(void *arg)
{
	printf("(II) Starting thread_methane\n");
	shared_data *md = (shared_data*) arg;


	printf("(II) Ending thread_methane\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_eau(void *arg)
{
	printf("(II) Starting thread_eau\n");
	shared_data *md = (shared_data*) arg;


	printf("(II) Ending thread_eau\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_pompe(void *arg)
{
	printf("(II) Starting thread_pompe\n");
	shared_data *md = (shared_data*) arg;


	printf("(II) Ending thread_pompe\n");
	pthread_exit(NULL);
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void* thread_alarme(void *arg)
{
	printf("(II) Starting thread_alarme\n");
	shared_data *md = (shared_data*) arg;


	printf("(II) Ending thread_alarme\n");
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
	shared_data md;

	//
	// Initialisation du mutex
	//
	int result = pipe (md.pipe_ctrl);
   	if (result < 0){ perror("pipe "); exit(1); }

	//
	// Boucle de création des mutex
	//


	//
	// Boucle de création des mutex
	//

	pthread_create(&(md.thread_0), NULL, thread_keyboard,   &md);
	pthread_create(&(md.thread_1), NULL, thread_controleur, &md);
	pthread_create(&(md.thread_2), NULL, thread_methane,    &md);
	pthread_create(&(md.thread_3), NULL, thread_eau,        &md);
	pthread_create(&(md.thread_4), NULL, thread_pompe,      &md);

	//
	// En attente de la completion de l'ensemble des threads
	//

	pthread_join(md.thread_0, NULL);
	pthread_join(md.thread_1, NULL);
	pthread_join(md.thread_2, NULL);
	pthread_join(md.thread_3, NULL);
	pthread_join(md.thread_4, NULL);

	//
	// Destruction des mutex
	//

	return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//