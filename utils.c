#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"


void creerVoitures(int i, int nbr) {
	voitures[i].number = nbr;    	//Numero de voiture
	voitures[i].nbrTour = 0;   		//Nombre de tours effectués
	voitures[i].tempsTour = 0;  	//Temps effectué pour le tour en cours
	voitures[i].bestS1 = 0;      	//Meilleur temps secteur 1
	voitures[i].bestS2 = 0;       	//Meilleur temps secteur 2
	voitures[i].bestS3 = 0;       	//Meilleur temps secteur 3
	voitures[i].bestTour = 0;  		//Meilleur tour de circuit
	voitures[i].tempsTotal = 0;    	//Temps écoulé depuis le début de la course
	voitures[i].nbrStand = 0;      	//Nombre d'arrêts au stand (1-3)
	voitures[i].isOut = 0;        	//Se met à 1 si la voiture se crash
	voitures[i].isQualifiedFor2 = 0;//Se met à 1 si la voiture est qualifiée pour la 2e qualif
	voitures[i].isQualifiedFor3 = 0;//Se met à 1 si la voiture est qualifiée pour la 3e qualif
}

struct sembuf semPlus = {0,1,SEM_UNDO|IPC_NOWAIT}; // +1 au sémaphore pour le locker
struct sembuf semMoins = {0,-1,SEM_UNDO|IPC_NOWAIT}; // -1 au sémaphore pour le délocker

double genereRandom(double min, double max){
    double div = RAND_MAX/(max - min);
    return min + (rand() / div);
}

void arret(int i) {
	if(voitures[i].nbrStand < 3) {
		if((genereRandom(0,2000) + (voitures[i].tempsTotal/100)) > 2001) {
			voitures[i].nbrStand++;
		}
	}
}

void crash(int numPid){
    if (genereRandom(0,800) > 799){
        voitures[numPid].isOut = 1;
    }
}

int calculerTempsMax(int tailleCircuit){
		tempsMinParKm = 20;
		tempsMaxParKm = 30;
		tempsMinS1 = (tempsMinParKm * tailleCircuit)/4;
		tempsMaxS1 = (tempsMaxParKm * tailleCircuit)/4;
		tempsMinS2 = 45*(tempsMinParKm * tailleCircuit)/100;
		tempsMaxS2 = 45*(tempsMaxParKm * tailleCircuit)/100;
		tempsMinS3 = 3*(tempsMinParKm * tailleCircuit)/10;
		tempsMaxS3 = 3*(tempsMaxParKm * tailleCircuit)/10;
}

void tempsS1(int i) {
    semop(SemId, &semPlus, 1);
    double temps;
	double tempsRandom = genereRandom(tempsMinS1,tempsMaxS1);

	crash(i);
    if(voitures[i].isOut == 0){
        temps = tempsRandom;
		
        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        if(voitures[i].bestS1 < 1 || temps < voitures[i].bestS1){
            voitures[i].bestS1 = temps;
        }
    }
    semop(SemId, &semMoins, 1);
}

void tempsS2(int i) {
    semop(SemId, &semPlus, 1);
    double temps;
    double tempsRandom = genereRandom(tempsMinS2, tempsMaxS2);

    crash(i);

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        if(voitures[i].bestS2 < 1 || temps < voitures[i].bestS2){
            voitures[i].bestS2 = temps;
        }
    }
    semop(SemId, &semMoins, 1);
}
void tempsS3(int i) {
    semop(SemId, &semPlus, 1);
    double temps;
    double tempsRandom = genereRandom(tempsMinS3, tempsMaxS3);
	arret(i);
    crash(i);

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        // Modification du meilleur moment pour le secteur 3 si le nouveau est meilleur
        if(voitures[i].bestS3 < 1 || temps < voitures[i].bestS3){
            voitures[i].bestS3 = temps;
        }
    }
    semop(SemId, &semMoins, 1);
}

void triVoitures(structCar voituresATrier[], int numCourse) {
	if(numCourse == 1 || numCourse == 2 || numCourse == 3 || numCourse == 4) {
		for(int i=0;i<20;i++) {
			for(int j=0;j<20;j++) {
				if(voituresATrier[i].bestTour == 0) {
					
				}
				else if(voituresATrier[j].bestTour > voituresATrier[i].bestTour || voituresATrier[j].bestTour == 0) {
					semop(SemId, &semPlus, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins, 1);
				}
			}
		}
	}
	else if(numCourse == 5) {
		for(int i=0;i<15;i++) {
			for(int j=0;j<15;j++) {
				if(voituresATrier[j].bestTour > voituresATrier[i].bestTour) {
					semop(SemId, &semPlus, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins, 1);
				}
			}
		}
	}
	else if(numCourse == 6) {
		for(int i=0;i<10;i++) {
			for(int j=0;j<10;j++) {
				if(voituresATrier[j].bestTour > voituresATrier[i].bestTour) {
					semop(SemId, &semPlus, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins, 1);
				}
			}
		}
	}
	else if(numCourse == 7) {
		for(int i=0;i<20;i++) {
			for(int j=0;j<20;j++) {
				if(voituresATrier[j].nbrTour < voituresATrier[i].nbrTour) {
					semop(SemId, &semPlus, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins, 1);
				}
				else if(voituresATrier[j].nbrTour == voituresATrier[i].nbrTour) {
					if(voituresATrier[j].tempsTotal > voituresATrier[i].tempsTotal) {
						semop(SemId, &semPlus, 1);
						structCar temporaire = voituresATrier[i];
						voituresATrier[i] = voituresATrier[j];
						voituresATrier[j] = temporaire;
						semop(SemId, &semMoins, 1);
					}
				}
			}
		}
	}
}

char demandeKilometrage() {
	int km;
	char s[100];
	printf("Bienvenue au Grand Prix de Formule 1 !\n");
	do
	{
		puts("Choisissez la longueur du circuit. Celle-ci doit être comprise entre 3 et 7");

		if (fgets(s, 100, stdin) == NULL) {
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}

		sscanf(s, "%d", &km);
	} while (km<3||km>7);
	calculerTempsMax(km);
}

char demandeContinuer(int numCourse){
	int o;
	char n[100];
	do
	{
		if(numCourse == 1) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer le 1er entrainement ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 2) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer le 2eme entrainement ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 3) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer le 3eme entrainement ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 4) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer la 1ere qualification ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 5) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer la 2eme qualification ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 6) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer la 3eme qualification ? \n Oui (1) / Non (0)");
		}
		if(numCourse == 7) {
			puts("\n\nLes voitures sont sur les starting blocks, voulez vous lancer la course finale ? \n Oui (1) / Non (0)");
		}

		if (fgets(n, 100, stdin) == NULL) {
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}

		sscanf(n, "%d", &o);
	} while (o<0||o>1);
	if(o == 1) {
		semop(SemId, &semPlus, 1);
		brain[11] = 1;
		semop(SemId, &semMoins, 1);
	}
	else {
		semop(SemId, &semPlus, 1);
		brain[11] = 0;
		semop(SemId, &semMoins, 1);
	}
}


void afficherResultatsEssai() {
	printf("|%s|  %s  | %s|     %s    |     %s    |     %s    |    %s   |   %s  |   %s   |\n", "Classement", "Numero", "Nombre tours", "Best S1", "Best S2", "Best S3", "Best Tour", "Stand", "Out ?");
	printf("----------------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<20;i++) {
		printf("|    %2d    |    %2d    |      %2d     |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %2d    |    %2d     |\n", i+1, voitures[i].number,voitures[i].nbrTour, voitures[i].bestS1, voitures[i].bestS2, voitures[i].bestS3, voitures[i].bestTour, voitures[i].nbrStand, voitures[i].isOut);
	}
	printf("\n%s%.2f\n", "Meilleur S1 : ", brain[7]);
	printf("\n%s%.2f\n", "Meilleur S2 : ", brain[8]);
	printf("\n%s%.2f\n", "Meilleur S3 : ", brain[9]);
	printf("\n%s%.2f\n", "Meilleur tour : ", brain[10]);
}

void afficherResultatsQualif(int qualif) {
	int nbrVoitures;
	if(qualif == 1) {
		nbrVoitures = 20;
	}
	if(qualif == 2) {
		nbrVoitures = 15;
	}
	if(qualif == 3) {
		nbrVoitures = 10;
	}
	printf("|%s|  %s  | %s|     %s    |     %s    |     %s    |    %s   |   %s  |   %s   |\n", "Classement", "Numero", "Nombre tours", "Best S1", "Best S2", "Best S3", "Best Tour", "Stand", "Out ?");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<nbrVoitures;i++) {
		printf("|    %2d    |    %2d    |      %2d     |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %2d    |    %2d     |\n", i+1, voitures[i].number,voitures[i].nbrTour, voitures[i].bestS1, voitures[i].bestS2, voitures[i].bestS3, voitures[i].bestTour, voitures[i].nbrStand, voitures[i].isOut);
	}
	printf("\n%s%.2f\n", "Meilleur S1 : ", brain[7]);
	printf("\n%s%.2f\n", "Meilleur S2 : ", brain[8]);
	printf("\n%s%.2f\n", "Meilleur S3 : ", brain[9]);
	printf("\n%s%.2f\n", "Meilleur tour : ", brain[10]);	
}
void afficherResultatsCourse() {
	printf("|%s|  %s  | %s|     %s    |     %s    |     %s    |    %s   |   %s  |   %s  |   %s   |\n", "Classement", "Numero", "Nombre tours", "Best S1", "Best S2", "Best S3", "Best Tour", "Temps Total", "Stand", "Out ?");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<20;i++) {
		printf("|    %2d    |    %2d    |      %2d     |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %2d    |    %2d     |\n", i+1, voitures[i].number, voitures[i].nbrTour, voitures[i].bestS1, voitures[i].bestS2, voitures[i].bestS3, voitures[i].bestTour, voitures[i].tempsTotal, voitures[i].nbrStand, voitures[i].isOut);
	}
	printf("\n%s%.2f\n", "Meilleur S1 : ", brain[7]);
	printf("\n%s%.2f\n", "Meilleur S2 : ", brain[8]);
	printf("\n%s%.2f\n", "Meilleur S3 : ", brain[9]);
	printf("\n%s%.2f\n", "Meilleur tour : ", brain[10]);
}

int genererEssai(int essai, int numPid) {
	int tempsTotalEssai;
	if(essai == 1 || essai == 2) {
		tempsTotalEssai = 5400;		//Temps maximal pour les essais 1 et 2. Ici, 1h30
	}
	if(essai == 3) {
		tempsTotalEssai = 3600;		//Temps maximal pour l'essai 3. Ici, 1h
	}
	voitures[numPid].bestS1 = 0;
	voitures[numPid].bestS2 = 0;
	voitures[numPid].bestS3 = 0;
	voitures[numPid].isOut = 0;
	voitures[numPid].nbrTour = 0;
	voitures[numPid].bestTour = 0;
	voitures[numPid].tempsTotal = 0;
	
										/* ************************************
										Début de la boucle de la séance d'essai
										************************************ */
										
										
	while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalEssai) {
		sleep(0.50);
		voitures[numPid].tempsTour = 0;
		if(voitures[numPid].isOut == 0) {
			tempsS1(numPid);	
			if((voitures[numPid].bestS1 < (double)brain[7]) || ((double)brain[7] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[7] = (voitures[numPid].bestS1);
				semop(SemId, &semMoins, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			tempsS2(numPid);
			if((voitures[numPid].bestS2 < (double)brain[8]) || ((double)brain[8] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[8] = (voitures[numPid].bestS2);
				semop(SemId, &semMoins, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			int isStand = voitures[numPid].nbrStand;
			tempsS3(numPid);
			if(voitures[numPid].nbrStand != isStand) {
				voitures[numPid].tempsTotal += 5;
			}
			if((voitures[numPid].bestS3 < (double)brain[9]) || ((double)brain[9] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[9] = (voitures[numPid].bestS3);
				semop(SemId, &semMoins, 1);
			}
		}	
		if(voitures[numPid].isOut == 0) {
			if(voitures[numPid].bestTour < 1 || voitures[numPid].tempsTour < voitures[numPid].bestTour) {
				semop(SemId, &semPlus, 1);
				voitures[numPid].bestTour = voitures[numPid].tempsTour;
				semop(SemId, &semMoins, 1);
				if((voitures[numPid].bestTour < (double)brain[10]) || ((double)brain[10] < 1)) {
					semop(SemId, &semPlus, 1);
					brain[10] = (voitures[numPid].bestTour);
					semop(SemId, &semMoins, 1);
				}
			}
		}
		if(voitures[numPid].isOut == 0) {
			voitures[numPid].nbrTour++;
		}
	}
	
	if(essai == 1) {
		semop(SemId, &semPlus, 1);
		brain[0]++;
		semop(SemId, &semMoins, 1);
	}
	if(essai == 2) {
		semop(SemId, &semPlus, 1);
		brain[1]++;
		semop(SemId, &semMoins, 1);
	}
	if(essai == 3) {
		semop(SemId, &semPlus, 1);
		brain[2]++;
		semop(SemId, &semMoins, 1);
	}	
}

int genererQualif(int qualif, int numPid) {
		int tempsTotalQualif;
		voitures[numPid].bestS1 = 0;
		voitures[numPid].bestS2 = 0;
		voitures[numPid].bestS3 = 0;
		voitures[numPid].isOut = 0;
		voitures[numPid].nbrTour = 0;
		voitures[numPid].bestTour = 0;
		voitures[numPid].tempsTotal = 0;
		
		if(qualif == 1) {
			tempsTotalQualif = 1080;	//Temps maximal pour la qualif 1. Ici, 18min
		}
		else if(qualif == 2) {
			tempsTotalQualif = 900;		//Temps maximal pour la qualif 2. Ici, 15min
			if(voitures[numPid].isQualifiedFor2 == 0) {	//Ejecte de la 2e qualif toutes les voitures non qualifiées
				return 0;
			}
		}
		else if(qualif == 3) {
			tempsTotalQualif = 720;		//Temps maximal pour la qualif 3. Ici, 12min
			if(voitures[numPid].isQualifiedFor3 == 0) {	//Ejecte de la 3e qualif toutes les voitures non qualifiées
				return 0;
			}
		}
		
		
											/* ***********************************
											Début de la boucle de la qualification
											*********************************** */
											
											
		while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalQualif) {
			voitures[numPid].tempsTour = 0;
			if(voitures[numPid].isOut == 0) {
				tempsS1(numPid);	
				if((voitures[numPid].bestS1 < (double)brain[7]) || ((double)brain[7] < 1)) {
					semop(SemId, &semPlus, 1);
					brain[7] = (voitures[numPid].bestS1);
					semop(SemId, &semMoins, 1);
				}
			}
			
			if(voitures[numPid].isOut == 0) {
				tempsS2(numPid);
				if((voitures[numPid].bestS2 < (double)brain[8]) || ((double)brain[8] < 1)) {
					semop(SemId, &semPlus, 1);
					brain[8] = (voitures[numPid].bestS2);
					semop(SemId, &semMoins, 1);
				}
			}
			
			if(voitures[numPid].isOut == 0) {
				int isStand = voitures[numPid].nbrStand;
				tempsS3(numPid);
				if(voitures[numPid].nbrStand != isStand) {
					voitures[numPid].tempsTotal += 5;
				}
				if((voitures[numPid].bestS3 < (double)brain[9]) || ((double)brain[9] < 1)) {
					semop(SemId, &semPlus, 1);
					brain[9] = (voitures[numPid].bestS3);
					semop(SemId, &semMoins, 1);
				}
			}	
			if(voitures[numPid].isOut == 0) {
				if(voitures[numPid].bestTour < 1 || voitures[numPid].tempsTour < voitures[numPid].bestTour) {
					semop(SemId, &semPlus, 1);
					voitures[numPid].bestTour = voitures[numPid].tempsTour;
					semop(SemId, &semMoins, 1);
					if((voitures[numPid].bestTour < (double)brain[10]) || ((double)brain[10] < 1)) {
						semop(SemId, &semPlus, 1);
						brain[10] = (voitures[numPid].bestTour);
						semop(SemId, &semMoins, 1);
					}
				}
			}
			if(voitures[numPid].isOut == 0) {
				voitures[numPid].nbrTour++;
			}
		}
			
		if(qualif == 1) {
			semop(SemId, &semPlus, 1);
			brain[3]++;
			semop(SemId, &semMoins, 1);
		}
		if(qualif == 2) {
			semop(SemId, &semPlus, 1);
			brain[4]++;
			semop(SemId, &semMoins, 1);
		}
		if(qualif == 3) {
			semop(SemId, &semPlus, 1);
			brain[5]++;
			semop(SemId, &semMoins, 1);
		}
}

int genererCourse(int numPid) {
	int tempsTotalCourse = 7200;	//Temps maximal pour la course. Ici, 2h
	
	voitures[numPid].bestS1 = 0;
	voitures[numPid].bestS2 = 0;
	voitures[numPid].bestS3 = 0;
	voitures[numPid].isOut = 0;
	voitures[numPid].nbrTour = 0;
	voitures[numPid].bestTour = 0;
	voitures[numPid].tempsTotal = 0;
	
										/* ****************************
										Début de la boucle de la course
										**************************** */
										
										
	while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalCourse) {
		sleep(0.50);
		voitures[numPid].tempsTour = 0;
		if(voitures[numPid].isOut == 0) {
			tempsS1(numPid);	
			if((voitures[numPid].bestS1 < (double)brain[7]) || ((double)brain[7] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[7] = (voitures[numPid].bestS1);
				semop(SemId, &semMoins, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			tempsS2(numPid);
			if((voitures[numPid].bestS2 < (double)brain[8]) || ((double)brain[8] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[8] = (voitures[numPid].bestS2);
				semop(SemId, &semMoins, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			int isStand = voitures[numPid].nbrStand;
			tempsS3(numPid);
			if(voitures[numPid].nbrStand != isStand) {
				voitures[numPid].tempsTotal += 5;
			}
			if((voitures[numPid].bestS3 < (double)brain[9]) || ((double)brain[9] < 1)) {
				semop(SemId, &semPlus, 1);
				brain[9] = (voitures[numPid].bestS3);
				semop(SemId, &semMoins, 1);
			}
		}	
		if(voitures[numPid].isOut == 0) {
			if(voitures[numPid].bestTour < 1 || voitures[numPid].tempsTour < voitures[numPid].bestTour) {
				semop(SemId, &semPlus, 1);
				voitures[numPid].bestTour = voitures[numPid].tempsTour;
				semop(SemId, &semMoins, 1);
				if((voitures[numPid].bestTour < (double)brain[10]) || ((double)brain[10] < 1)) {
					semop(SemId, &semPlus, 1);
					brain[10] = (voitures[numPid].bestTour);
					semop(SemId, &semMoins, 1);
				}
			}
		}
		if(voitures[numPid].isOut == 0) {
			voitures[numPid].nbrTour++;
		}
	}
	semop(SemId, &semPlus, 1);
	brain[6]++;
	semop(SemId, &semMoins, 1);
}