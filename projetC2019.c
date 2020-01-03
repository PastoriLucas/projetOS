#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "cars.h"
#include "utils.h"
#include "essai.h"
#include "qualif.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>



//le premier sémaphore gère le segment de mémoire partagée des voitures (cars, tutureQualif 2 et 3)
//le deuxième sémaphore gère le segment de mémoire partagée pour différentes variables
//le troisième sémaphore gère le segment de mémoire partagée pour la liste pid
	
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
				numPid = x;
				
				//ESSAI 1
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererEssai(1, numPid);
					sleep(1);
				//ESSAI 2
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererEssai(2, numPid);
					sleep(1);
				//ESSAI 3
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererEssai(3, numPid);
					sleep(1);
				//QUALIF 1
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererQualif(1, numPid);
					sleep(1);
				//QUALIF 2
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererQualif(2, numPid);
					sleep(1);
				//QUALIF 3
					while(brain[11] != 1) {
						sleep(0.50);
					}

					genererQualif(3, numPid);
					sleep(1);
				return 0;
			}
			else if(pid > 0) {
				semop(SemId, &semPlus2, 1);
				listePid[21-(x+1)] = pid;
				semop(SemId, &semMoins2, 1);
			}
		}
	//EXECUTION DE L'ENTRAINEMENT NUMERO 1
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		
		demandeContinuer(1);
		if(brain[11] == 0) {
			return 0;
		}

		while(brain[0]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);

		triVoitures(voitures, 1);

		afficherResultatsEssai();
		
		
	//EXECUTION DE L'ENTRAINEMENT NUMERO 2
	
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		demandeContinuer(2);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[1]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);
		
		triVoitures(voitures, 2);
		afficherResultatsEssai();
		
	//EXECUTION DE L'ENTRAINEMENT NUMERO 3
	
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		demandeContinuer(3);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[2]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);
		
		triVoitures(voitures, 3);
		afficherResultatsEssai();
		
	//EXECUTION DE LA QUALIFICATION NUMERO 1
	
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		demandeContinuer(4);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[3]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);
		
		triVoitures(voitures, 4);
		
		semop(SemId, &semPlus0, 1);
		for(int i=0; i<15; i++) {
			voitures[i].isQualifiedFor2 = 1;
		}
		semop(SemId, &semMoins0, 1);
		afficherResultatsQualif(1);
		
	//EXECUTION DE LA QUALIFICATION NUMERO 2
	
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		demandeContinuer(5);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[4]!=15) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);
		
		triVoitures(voitures, 5);
		semop(SemId, &semPlus0, 1);
		for(int i=0; i<10; i++) {
			voitures[i].isQualifiedFor3 = 1;
		}
		semop(SemId, &semMoins0, 1);
		afficherResultatsQualif(2);	
		
	//EXECUTION DE LA QUALIFICATION NUMERO 3
	
		semop(SemId, &semPlus1, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
		semop(SemId, &semMoins1, 1);
		demandeContinuer(6);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[5]!=10) {
			sleep(0.50);
		}
		semop(SemId, &semPlus1, 1);
		brain[11] = -1;
		semop(SemId, &semMoins1, 1);
		
		triVoitures(voitures, 6);
		afficherResultatsQualif(3);
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
		semop(SemId, &semPlus1, 1);
			brain[0]=0; //P1
			brain[1]=0; //P2
			brain[2]=0; //P3
			brain[3]=0; //Q1
			brain[4]=0; //Q2
			brain[5]=0; //Q3
			brain[6]=0; //Final
			brain[7]=-1; //topS1
			brain[8]=-1; //topS2
			brain[9]=-1; //topS3
			brain[10]=-1;//topTour
			brain[11]=0;//Continuer ou pas
		semop(SemId, &semMoins1, 1);
	
	listePid = shmat(shmid2, NULL, 1);
		semop(SemId, &semPlus2, 1);
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
		semop(SemId, &semMoins2, 1);
		
	qualifiedFor2 = shmat(shmid3, NULL, 1);
	
	qualifiedFor3 = shmat(shmid4, NULL, 1);
	
	int numVoitures[20] = {7,99,5,16,8,20,4,55,10,26,44,77,11,18,23,33,3,27,63,88};
	for(int i=0; i<20; i++)
	{
		semop(SemId, &semPlus0, 1);
		initialiserVoitures(i,numVoitures[i]);
		semop(SemId, & semMoins0, 1);
	}
	
	demandeKilometrage();
	principal(20);
}