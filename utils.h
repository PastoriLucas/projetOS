#include "cars.h"
#ifndef utilitaire_h
#define utilitaire_h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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
char demandeAction();
char demandeKilometrage();

int tempsMinParKm = 20;
int tempsMaxParKm = 30;
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

extern struct sembuf semWait0;
extern struct sembuf semDo0;
extern struct sembuf semPost0;
extern struct sembuf semWait1;
extern struct sembuf semDo1;
extern struct sembuf semPost1;
extern struct sembuf semWait2;
extern struct sembuf semDo2;
extern struct sembuf semPost2;

#endif