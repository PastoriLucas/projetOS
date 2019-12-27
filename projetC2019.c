#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "cars.h"
#include "utils.h"
#include "essai.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

int myGlobalStaticContinueVariable;

void handleSignal(int sig) {
	myGlobalStaticContinueVariable = 1;
}

//le premier sémaphore gère le segment de mémoire partagée des voitures (cars, tutureQualif 2 et 3)
//le deuxième sémaphore gère le segment de mémoire partagée pour différentes variables
//le troisième sémaphore gère le segment de mémoire partagée pour la liste pid







void randomCrash(int numeroVoiture) {
	srand(time(NULL));
	int random;
	random = (double)rand()/RAND_MAX*15.0-0.0;
	if(random == 1) {
		printf("%s", "Crashhhhh\n");
		printf("%d\n", random);
	}
	else {
		printf("%s", "Pas de crash cette fois\n");
		printf("%d\n", random);
	}
}
	
int principal(int nbrVoitures) {
    int pid;
	for(int x=0; x<nbrVoitures; x++) {
		pid = fork();
		if (pid < 0) {
		    printf("%s", "Error fork < 0");
		}
		else if (pid == 0) {
			sleep(1);
			srand(time(NULL)+getpid());
		   
		    int numPid;
		   
		    semop(SemId, &semWait2, 1);
		    semop(SemId, &semDo2, 1);
			//numPid = indexOf(getpid(), 20, listePid);
			numPid = x;
			semop(SemId, &semPost2, 1);
			
			genererEssai(1, numPid);
			return 0;
		}
		else if(pid > 0) {
			semop(SemId, &semWait2, 1);
			semop(SemId, &semDo2, 1);
			listePid[21-(x+1)] = pid;
			semop(SemId, &semPost2, 1);
		}
	}
	while(brain[0]!=20) {
	sleep(0.50);
	}
	/* semop(SemId, &semWait1, 1);
	semop(SemId, &semDo1, 1);
	printf("%d\n", brain[7]);
	semop(SemId, &semPost1, 1); */
	printf("%s\n\n", "S1 :");
	for(int i=0; i<20;i++) {
		printf("%.2f\n", voitures[i].bestS1);
	}
	printf("%s%.2f\n", "Best time : ", brain[7]);
	printf("\n%s\n\n", "S2 :");
}
	
	
int main() {
	int key0 = 123;//clé de la mémoire partagée
	int key1 = 789;//deuxieme clé de la mémoire partagée
	int key2 = 999;//troisième clé de la mémoire partagée
	int key3 = 888;//quatrième clé de la mémoire partagée
	int key4 = 777;//cinquième clé de la mémoire partagée
	int keyShm = 456;//clé de la sémaphore

	//Création du sémaphore
	SemId = semget(keyShm, 3, IPC_CREAT|0666);

	//Variables temporaires que nous avons utilisé pour determiner la taille requise de la mémoire partagée
	structCar tailleCar0[20];
	structCar tailleCar3[15];
	structCar tailleCar4[10];
	int tailleCar1[7];
	int tailleCar2[21];

	//Création de mémoires partagées dont nous avions besoin (1 pour les voitures, 1 pour les variables dont nous avions besoin
	//et 1 pour la pidList)
	int shmid0 = shmget(key0, sizeof(tailleCar0), IPC_CREAT|0666); //autorisation 0666??
	int shmid1 = shmget(key1, sizeof(tailleCar1), IPC_CREAT|0666);
	int shmid2 = shmget(key2, sizeof(tailleCar2), IPC_CREAT|0666);
	int shmid3 = shmget(key3, sizeof(tailleCar3), IPC_CREAT|0666);
	int shmid4 = shmget(key4, sizeof(tailleCar4), IPC_CREAT|0666);
	if(shmid0==-1 || shmid1==-1 || shmid2==-1 || shmid3==-1 || shmid4==-1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
	
	voitures = shmat(shmid0, NULL, 1);
	
	brain = shmat(shmid1, NULL, 1);
		semop(SemId, &semWait1, 1);
		semop(SemId, &semDo1, 1);
			brain[0]=0; //P1
			brain[1]=0; //P2
			brain[2]=0 ; //P3
			brain[3]=0; //Q1
			brain[4]=0; //Q2
			brain[5]=0; //Q3
			brain[6]=0; //r
			brain[7]=1000; //topS1
			brain[8]=0; //topS2
			brain[9]=0; //topS3
			brain[10]=0;//topTour
		semop(SemId, &semPost1, 1);
	
	listePid = shmat(shmid2, NULL, 1);
		semop(SemId, &semWait2, 1);
		semop(SemId, &semDo2, 1);
			listePid[0]=0;
			listePid[1]=0;
			listePid[2]=0;
			listePid[3]=0;
			listePid[4]=0;
			listePid[5]=0;
			listePid[6]=0;
			listePid[7]=0;
			listePid[8]=0;
			listePid[9]=0;
			listePid[10]=0;
			listePid[11]=0;
			listePid[12]=0;
			listePid[13]=0;
			listePid[14]=0;
			listePid[15]=0;
			listePid[16]=0;
			listePid[17]=0;
			listePid[18]=0;
			listePid[19]=0;
			listePid[20]=0;
		semop(SemId, &semPost2, 1);
	
	qualifiedFor2 = shmat(shmid3, NULL, 1);
	
	qualifiedFor3 = shmat(shmid4, NULL, 1);
	
	int numVoitures[20] = {7,99,5,16,8,20,4,55,10,26,44,77,11,18,23,33,3,27,63,88};
	for(int i=0; i<20; i++)
	{
		semop(SemId, &semWait0, 1);
		semop(SemId, &semDo0, 1);
		initialiserVoitures(i,numVoitures[i]);
		semop(SemId, & semPost0, 1);
	}
	
	
	
	
	
	
	principal(20);
}