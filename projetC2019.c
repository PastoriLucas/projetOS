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

//le premier sémaphore gère le segment de mémoire partagée des voitures (cras, tutureQualif 2 et 3)
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




int genererP1(int i) {
	int x;
	for(x=0; x<4; x++) {
		if(fork() == 0) {
			printf("%s%d%s\n", " voiture ", x, " : ");
			double temps_random;
			int i, n;
			time_t t;
			double temps_total;
			n = 3;
			temps_total = 0;
			srand(time(NULL));
			
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 1 : ", temps_random);
			
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 2 : ", temps_random);
				
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 3 : ", temps_random);
			
			printf("%s%.3f\n", "temps total pour la course : ", temps_total);
			return 0;
		}
	sleep(1);
	}
	/*
	printf("%s%d%s%d\n", "Meilleur temps pour P1 : ", bestTimeP1[1], ". Voiture ", bestTimeP1[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P2 : ", bestTimeP2[1], ". Voiture ", bestTimeP2[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P3 : ", bestTimeP3[1], ". Voiture ", bestTimeP3[0]);
	*/
}
	
int principal(int nbrVoitures) {
    int pid;
	int essaiF = 0;
	int essaiP = 0;
	for(int x=0; x<nbrVoitures; x++) {
		pid = fork();
		if (pid < 0) {
		    printf("%s", "Error fork < 0");
		}
		else if (pid == 0) {
			srand(time(NULL)+getpid());
			sleep(1);
		   
		    int index;
		   
		    semop(SemId, &semWait2, 1);
		    semop(SemId, &semDo2, 1);
			index = indexOf(getpid(), 21, listePid);
			semop(SemId, &semPost2, 1);
			return 0;
		}
		else if(pid > 0) {
		    semop(SemId, &semWait2, 1);
			semop(SemId, &semDo2, 1);
			listePid[21-(x+1)] = pid;
			semop(SemId, &semPost2, 1);
		}
	}
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
	shMem = shmat(shmid1, NULL, 1);
	listePid = shmat(shmid2, NULL, 1);
	qualifiedFor2 = shmat(shmid3, NULL, 1);
	qualifiedFor3 = shmat(shmid4, NULL, 1);
	
	int numVoitures[20] = {7,99,5,16,8,20,4,55,10,26,44,77,11,18,23,33,3,27,63,88};
	for(int i=0; i<20; i++)
	{
		//Verouillage semopore
		semop(SemId, &semWait0, 1);
		semop(SemId, &semDo0, 1);
		initialiserVoitures(i,numVoitures[i]);
		semop(SemId, & semPost0, 1);
		//startPosition[i]=0;
		//déverouillage du semopore
	}
	
	semop(SemId, &semWait1, 1);
	semop(SemId, &semDo1, 1);
	shMem[0]=0; //p1
	shMem[1]=0; //p2
	shMem[2]=0; //p3
	shMem[3]=0; //q1
	shMem[4]=0; //q2
	shMem[5]=0; //q3
	shMem[6]=0; //r
	shMem[7]=0; //topS1
	shMem[8]=0; //topS2
	shMem[9]=0; //topS3
	shMem[10]=0; //topTour
	semop(SemId, &semPost1, 1);
	
	semop(SemId, &semWait2, 1);
	semop(SemId, &semDo2, 1);
	listePid[0]=getpid();
	listePid[1]=-1;
	listePid[2]=-1;
	listePid[3]=-1;
	listePid[4]=-1;
	listePid[5]=-1;
	listePid[6]=-1;
	listePid[7]=-1;
	listePid[8]=-1;
	listePid[9]=-1;
	listePid[10]=-1;
	listePid[11]=-1;
	listePid[12]=-1;
	listePid[13]=-1;
	listePid[14]=-1;
	listePid[15]=-1;
	listePid[16]=-1;
	listePid[17]=-1;
	listePid[18]=-1;
	listePid[19]=-1;
	listePid[20]=-1;
	semop(SemId, &semPost2, 1);
	principal(20);
}