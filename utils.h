#ifndef utilitaire_h
#define utilitaire_h

#include "voiture.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Variables globales qui restent constantes pendant l'exécution du programme

/*
 * Nombre de tours pendant une course
 */
int nbrLapMax;

/*
 * Longueur du circuit. Cette valeur est entrée par l'utilisateur.
 */
int longueurCircuit;

/*
 * C'est le pointeur sur le segment de mémoire partagée qui contient les structures des voitures
 */
structTuture *voitures;

/*
 * C'est le pointeur sur le segment de mémoire partagée qui contient les variables globales qui doivent être partagées par
 * tout le processus et modifiées au cours de la durée d'exécution du programme.
 */
int *smv;

/*
 * C'est le pointeur sur le segment de mémoire partagée qui contient la liste des pids.
 */
int *pidList;


/*
 * C'est le pointeur sur les sémaphores.
 */
int id_sem;

/*
 * C'est le pointeur sur le segment de mémoire partagée qui contient les structures des voitures pour
 * les voitures en seconde qualification
 */
structTuture *voituresQualif2;

/*
 * C'est le pointeur sur le segment de mémoire partagée qui contient les structures
 * des voitures pour les voitures en cours de la troisième qualification.
 */
structTuture *voituresQualif3;

/*
 * Position de départ pour la course (indiquez le numéro de la voiture)
 */
int startPosition[20];

/*
 * Ceci est un drapeau pour savoir si c'est la course ou pas 0 = pas et 1 = course
 */
int isCourse;

//Structures pour les sémaphores
//- le premier sémaphore gère le segment de mémoire partagée des voitures (cras, tutureQualif 2 et 3)
//- le deuxième sémaphore gère le segment de mémoire partagée pour différentes variables
//- le troisième sémaphore gère le segment de mémoire partagée pour la liste pid
extern struct sembuf semWait;
extern struct sembuf semDo;
extern struct sembuf semPost;
extern struct sembuf semWait1;
extern struct sembuf semDo1;
extern struct sembuf semPost1;
extern struct sembuf semWait2;
extern struct sembuf semDo2;
extern struct sembuf semPost2;



/*
 * Cette fonction génère un nombre aléatoire compris entre min et max.
 * @pre : min_number < max_number
 * @post : min_number < x < max_number & @retourne x
 */
int genereRandom(int min, int max);

/*
 * Cette fonction génère un arrêt au stand (basé sur une fonction aléatoire). i est l'indice de la voiture dans la structure des voitures
 * @pre : 0 <= i <= |voitures|
 * @post : si le pitStop incrémente tuture [i] .pitStop et renvoie l'heure de ce pitStop, sinon renvoie 0.
 */
int arret(int i);

/*
 * Cette fonction génère un crash aléatoire. index est l'indice de la voiture dans les voitures.
 * @pre : 0 <= index <= |voitures|
 * @post : returns 1 si crash, 0 otherwise
 */
void crash(int index);

/*
 * Cette fonction obtient le temps maximum actuel des voitures
 * @pre : structTuture *voitures exists
 * @post : returns le max de temps actuelle des voitures
 */
double getCurrTemps();

/*
 * Cette fonction calcule le nombre de tours requis pour cette piste. Ce nombre est le plus petit nombre de tours de manière à ce que
 * les kilomètres parcourus soient> = 305 km.
 * @pre : km > 0
 * @post : returns x = 305/km if km%2==0|| x=1+305/km
 */
int nbrTour(int km);

/*
 * Cette fonction fait correspondre l'index du processus (dans pidList) à un index dans les voitures. i est la pidList à comparer,
 * longueur est la longueur de la tabulation, t est la tabulation.
 * @pre : length>0
 * @post : returns l'index si i est dans la table si ce n'est pas
 */
int indexOf(int i, int longueur, int t[]);

/*
 * Cette fonction vérifie si la voiture est ou non dans le tableau. Il retourne 1 s'il est et 0 s'il ne l'est pas
 * @pre: length>0
 * @post: returns 1 si le nom n'est pas dedans, 0 otherwise
 */
int isIn(int nom, int longueur, structTuture t[]);

/*
 * Cette fonction génère le temps nécessaire à une voiture structTuture pour effectuer le premier secteur. i est l'indice de la voiture dans les voitures.
 * @pre : 0 <= i <= |voitures|
 * @post : returns nothing and modify the following parameters from the tuture : currTemps, currCircuit and if needed bestS1
 */
void genereTempsS1(int i);

/*
 * Cette fonction génère le temps nécessaire à une voiture structTuture pour effectuer le premier secteur. i est l'indice de la voiture dans les voitures.
 * @pre : 0 <= i <= |voitures|
 * @post : returns nothing and modify the following parameters from the tuture : currTemps, currCircuit and if needed bestS2
 */
void genereTempsS2(int i);

/*
 * Cette fonction génère le temps nécessaire à une voiture structTuture pour effectuer le premier secteur. i est l'indice de la voiture dans les voitures.
 * @pre : 0 <= i <= |voitures|
 * @post : returns nothing and modify the following parameters from the tuture : currTemps, currCircuit and if needed bestS3 and bestCircuit
 */
void genereTempsS3(int i);

/*
 * Cette fonction demande à l’utilisateur une entrée et effectue une boucle jusqu’à ce que l’entrée soit correcte.
 * Cette entrée est un tutureactère.
 * @pre :/
 * @post : return the character
 */
char demandeAction();

/*
 * Cette fonction gère l'interaction avec l'utilisateur et le meurtre des enfants si nécessaire.
 * i est l'indice de la variable à réinitialiser.
 * @pre:/
 * @post : if the user wants to stop, calls killchildren
 */
void interaction(int i);

/*
 * Cette fonction permet au processus parent de tuer tous ses enfants.
 * @pre:/
 * @post: returns nothing. All the children processes have been killed.
 */
void killIt();

/*
 * Cette fonction permet au processus parent de réveiller tous ses enfants.
 * @pre:/
 * @post: returns nothing. All the children processes have been woken up.
 */
void wake();

/*
 * Cette fonction trie un tableau de voitures en fonction de leur heure globale actuelle.
 * @pre:/
 * @post: returns nothing, the array voituresQualif has been sorteded.
 */
void sortCourse(structCar voituresQualif[], int sizeArrayVoitures);
/*
 * Cette fonction ajoute le temps par position de la voiture pour la course.
 * @pre:/
 * @post: returns nothing. Ajout du temps aux voitures.
 */
void ajouteTempsEnFctPosition();

/*
 * Cette fonction définit les variables des voitures qui ne peuvent pas "concourir en q
 * to 1.
 * @pre: q==2||q==3
 * @post: Ne retourne rien. Out a été modifié pour les bonnes voitures
 */
void setOut(int q);

#endif // utilitaire_h
