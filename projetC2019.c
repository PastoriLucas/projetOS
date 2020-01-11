#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
	
//Fonction principale qui gère la création de voitures et le déroulement du week-end
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
				//COURSE FINALE
					while(brain[11] != 1) {
						sleep(0.50);
					}
					genererCourse(numPid);
					sleep(0);
				return 0;
			}
		}
	//EXECUTION DE L'ENTRAINEMENT NUMERO 1
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		
		demandeContinuer(1);
		if(brain[11] == 0) {
			return 0;
		}

		while(brain[0]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);

		triVoitures(voitures, 1);

		afficherResultatsEssai();
		
		
	//EXECUTION DE L'ENTRAINEMENT NUMERO 2
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(2);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[1]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 2);
		afficherResultatsEssai();
		
	//EXECUTION DE L'ENTRAINEMENT NUMERO 3
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(3);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[2]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 3);
		afficherResultatsEssai();
		
	//EXECUTION DE LA QUALIFICATION NUMERO 1
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(4);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[3]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 4);
		
		semop(SemId, &semPlus, 1);
		for(int i=0; i<15; i++) {
			voitures[i].isQualifiedFor2 = 1;
		}
		semop(SemId, &semMoins, 1);
		afficherResultatsQualif(1);
		
	//EXECUTION DE LA QUALIFICATION NUMERO 2
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(5);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[4]!=15) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 5);
		semop(SemId, &semPlus, 1);
		for(int i=0; i<10; i++) {
			voitures[i].isQualifiedFor3 = 1;
		}
		semop(SemId, &semMoins, 1);
		afficherResultatsQualif(2);	
		
	//EXECUTION DE LA QUALIFICATION NUMERO 3
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(6);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[5]!=10) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 6);
		afficherResultatsQualif(3);
		
	//EXECUTION DE LA COURSE FINALE
	
		semop(SemId, &semPlus, 1);
			brain[7] = 0;
			brain[8] = 0;
			brain[9] = 0;
			brain[10] = 0;
		semop(SemId, &semMoins, 1);
		demandeContinuer(7);
		if(brain[11] == 0) {
			return 0;
		}
		while(brain[6]!=20) {
			sleep(0.50);
		}
		semop(SemId, &semPlus, 1);
		brain[11] = -1;
		semop(SemId, &semMoins, 1);
		
		triVoitures(voitures, 7);
		afficherResultatsCourse();
}
	
	
int main() {
	//Création du sémaphore
	
	SemId = semget(0, 3, IPC_CREAT|0666);

	//Création de mémoires partagées
	
	int shmid0 = shmget(1, sizeof(voitures), IPC_CREAT|0666); 	// -> Pour les informations sur les voitures
	int shmid1 = shmget(2, sizeof(brain), IPC_CREAT|0666); 		// -> Pour toutes les autres valeurs à retenir
	
	if(shmid0 == -1 || shmid1 == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
	
	//Le stockage des voitures est assigné à la mémoire partagée shmid0
	voitures = shmat(shmid0, NULL, 1);
	
	//Le stockage des autres informations est assigné à la mémoire partagée shmid1
	brain = shmat(shmid1, NULL, 1);
	semop(SemId, &semPlus, 1);
		brain[0]=0;		//P1
		brain[1]=0; 	//P2
		brain[2]=0; 	//P3
		brain[3]=0; 	//Q1
		brain[4]=0; 	//Q2
		brain[5]=0; 	//Q3
		brain[6]=0; 	//Course finale
		brain[7]=-1; 	//topS1
		brain[8]=-1; 	//topS2
		brain[9]=-1; 	//topS3
		brain[10]=-1;	//topTour
		brain[11]=0;	//Continuer ou pas
	semop(SemId, &semMoins, 1);
	
	//Assignation des numeros de voitues aux 20 voitures créées
	int numVoitures[20] = {7,99,5,16,8,20,4,55,10,26,44,77,11,18,23,33,3,27,63,88};
	for(int i=0; i<20; i++)
	{
		semop(SemId, &semPlus, 1);
		creerVoitures(i,numVoitures[i]);
		semop(SemId, & semMoins, 1);
	}
	
	//Demande la taille du circuit
	demandeKilometrage();
	//Lance le fonction principale
	principal(20);
}