#include "cars.h"
#ifndef utilitaire_h
#define utilitaire_h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int SemId;
structCar *voitures;
int *shMem;
int *listePid;
structCar *qualifiedFor2;
structCar *qualifiedFor3;
int indexOf(int i, int longueur, int t[]);
void killIt();

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