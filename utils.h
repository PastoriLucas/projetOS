#include "cars.h"
#ifndef utilitaire_h
#define utilitaire_h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
void arret(int i);
double genereRandom(double min, double max);
int SemId;
structCar *voitures;
double *brain;
int *listePid;
structCar *qualifiedFor2;
structCar *qualifiedFor3;
int indexOf(int i, int longueur, int t[]);
void killIt();
int startPosition;
char demandeContinuer(int numCourse);
char demandeKilometrage();

int tempsMinParKm;
int tempsMaxParKm;
int tempsMinS1;
int tempsMaxS1;
int tempsMinS2;
int tempsMaxS2;
int tempsMinS3;
int tempsMaxS3;

int calculerTempsMax(int tailleCircuit);
void tempsS1(int i);
void tempsS2(int i);
void tempsS3(int i);
void triVoitures(structCar voituresATrier[], int numCourse);
void afficherResultatsEssai();
void afficherResultatsQualif(int qualif);
void afficherResultatsCourse();

extern struct sembuf semPlus0;
extern struct sembuf semMoins0;
extern struct sembuf semPlus1;
extern struct sembuf semMoins1;
extern struct sembuf semPlus2;
extern struct sembuf semMoins2;

#endif