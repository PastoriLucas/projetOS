#include "cars.h"
#ifndef utilitaire_h
#define utilitaire_h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int SemId;
structCar *voitures;
double *brain;

extern struct sembuf semPlus;
extern struct sembuf semMoins;

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

void afficherResultatsEssai();
void afficherResultatsQualif(int qualif);
void afficherResultatsCourse();
#endif