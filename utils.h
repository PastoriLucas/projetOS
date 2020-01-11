#ifndef utils_h
#define utils_h
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef struct structCar {
		int number;         //numero de la voiture
		double bestTour; 	//Meilleur temps sur un tour de circuit
		double bestS1;      //Meilleur temps sur le premier secteur
		double bestS2;      //Meilleur temps sur le deuxieme secteur
		double bestS3;      //Meilleur temps sur le troisieme secteur
		int nbrTour;    	//Nombre de tours déjà effectués
		double tempsTotal;  //Temps écoulé depuis le début de la course
		double tempsTour; 	//Heure actuelle de la course
		int nbrStand;       //nombre de fois qu'il a passé le stand (entre 1 et 3)
		int isOut;          //0 si la voiture est toujours en marche, 1 si c'est le crash
		int isQualifiedFor2;
		int isQualifiedFor3;
	}structCar;
	
int SemId;
double *brain;
structCar *voitures;

extern struct sembuf semPlus;
extern struct sembuf semMoins;

void creerVoitures(int i, int nbr);

double genereRandom(double min, double max);
void arret(int i);
void crash(int numPid);
void tempsS1(int i);
void tempsS2(int i);
void tempsS3(int i);
void triVoitures(structCar voituresATrier[], int numCourse);

char demandeKilometrage();
int calculerTempsMax(int tailleCircuit);
	int tempsMinParKm;
	int tempsMaxParKm;
	int tempsMinS1;
	int tempsMaxS1;
	int tempsMinS2;
	int tempsMaxS2;
	int tempsMinS3;
	int tempsMaxS3;
char demandeContinuer(int numCourse);

int genererEssai(int essai, int numPid);
int genererQualif(int qualif, int numPid);
int genererCourse(int numPid);

void afficherResultatsEssai();
void afficherResultatsQualif(int qualif);
void afficherResultatsCourse();
#endif