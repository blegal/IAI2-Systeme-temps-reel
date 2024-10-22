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
typedef struct mutex_data {

	//
	// LISTE DES EVENEMENTS POUVANT ETRE ECHANGES ENTRE
	// LE CONTROLEUR DE LA MINE ET LES AUTRES PROCESSUS
	// DE TRAITEMENT
	//

	const char EVT_START     = 's';
	const char EVT_STOP      = 'S';
	const char EVT_END       = 'F';
	const char EVT_EAU_BAS   = 'b';
	const char EVT_EAU_HAUT  = 'h';
	const char EVT_METH_BAS  = 'B';
	const char EVT_METH_HAUT = 'H';
	const char EVT_METH_OK   = 'O';

	//
	// LA FILE DE MESSAGE PERMETTANT L'ECHANGE D'INFO
	//

	int pipe_ctrl[2];

	//
	// LA FILE DE MESSAGE PERMETTANT L'ECHANGE D'INFO
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

	pthread_mutex_t mutex_methane;
	pthread_mutex_t mutex_eau;
	pthread_mutex_t mutex_alarm;
	pthread_mutex_t mutex_pompe;

	//
	// LES BOOL PARTAGES POUR FAIRE LES
	//

	bool enable_methane = false;
	bool enable_eau     = false;
	bool enable_alarme  = false;
	bool enable_pompe   = false;

	//
	// LE BOOL PARTAGE CLORE L'EXECUTION DU SYSTEME
	//

	bool exit_cmd       = false;

	//
	// LA VALEUR INDIQUANT LA VALEUR DE L'ALARME
	//

	int  alarm_level    = 1;

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
	printf("(II) Starting thread_controleur\n");
	mutex_data *md = (mutex_data*) arg;

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
	mutex_data *md = (mutex_data*) arg;


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
	mutex_data *md = (mutex_data*) arg;


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
	mutex_data *md = (mutex_data*) arg;


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
	mutex_data *md = (mutex_data*) arg;


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
	mutex_data *md = (mutex_data*) arg;


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
	mutex_data md;

	//
	// Initialisation du mutex
	//
	int result = pipe (md.pipe_ctrl);
   	if (result < 0){ perror("pipe "); exit(1); }

	//
	// Boucle de création des mutex
	//

	pthread_mutex_init(&md.mutex_methane, NULL);
	pthread_mutex_init(&md.mutex_eau,     NULL);
	pthread_mutex_init(&md.mutex_alarm,   NULL);
	pthread_mutex_init(&md.mutex_pompe,   NULL);

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
	// Destruction du mutex
	//

	pthread_mutex_destroy(&md.mutex_methane);
	pthread_mutex_destroy(&md.mutex_eau    );
	pthread_mutex_destroy(&md.mutex_alarm  );
	pthread_mutex_destroy(&md.mutex_pompe  );

	return EXIT_SUCCESS;
}
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//