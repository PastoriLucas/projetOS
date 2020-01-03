#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>


struct sembuf semPlus0 = {0,1,SEM_UNDO|IPC_NOWAIT}; // +1 au sémaphore pour le locker
struct sembuf semMoins0 = {0,-1,SEM_UNDO|IPC_NOWAIT}; // -1 au sémaphore pour le délocker
struct sembuf semPlus1 = {1,1,SEM_UNDO|IPC_NOWAIT}; // +1 au sémaphore pour le locker
struct sembuf semMoins1 = {1,-1,SEM_UNDO|IPC_NOWAIT}; // -1 au sémaphore pour le délocker
struct sembuf semPlus2 = {2,1,SEM_UNDO|IPC_NOWAIT}; // +1 au sémaphore pour le locker
struct sembuf semMoins2 = {2,-1,SEM_UNDO|IPC_NOWAIT}; // -1 au sémaphore pour le délocker

double genereRandom(double min, double max){
    double div = RAND_MAX/(max - min);
    return min + (rand() / div);
}

void arret(int i) {
    int randomStand = (int)genereRandom(0,11);
	if(randomStand < 1) {
		voitures[i].nbrStand = 3;
		voitures[i].tempsTotal += (15);
	}
	else if(randomStand < 2) {
		voitures[i].nbrStand = 3;
		voitures[i].tempsTotal += (15);
	}
	else if(randomStand < 3) {
		voitures[i].nbrStand = 3;
		voitures[i].tempsTotal += (15);
	}
	else if(randomStand < 4) {
		voitures[i].nbrStand = 3;
		voitures[i].tempsTotal += (15);
	}
	else if(randomStand < 5) {
		voitures[i].nbrStand = 2;
		voitures[i].tempsTotal += (10);
	}
	else if(randomStand < 6) {
		voitures[i].nbrStand = 2;
		voitures[i].tempsTotal += (10);
	}
	else if(randomStand < 7) {
		voitures[i].nbrStand = 2;
		voitures[i].tempsTotal += (10);
	}
	else if(randomStand < 8) {
		voitures[i].nbrStand = 2;
		voitures[i].tempsTotal += (10);
	}
	else if(randomStand < 9) {
		voitures[i].nbrStand = 1;
		voitures[i].tempsTotal += (5);
	}
	else {
		voitures[i].nbrStand = 0;
	}
}

void crash(int numPid){
    if (genereRandom(0,800) > 799){
        voitures[numPid].isOut = 1;
    }
}

double getTemps() {
    double temps = 0;
    for (int i=0; i<20; i++){
        if(voitures[i].tempsTotal > temps) {
            temps = voitures[i].tempsTotal;
        }
    }
    return temps;
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

int indexOf(int i, int longueur, int t[])
{
    for(int j=0; j<longueur; j++) {
        if(i==t[j]) {
            return j;
        }
    }
	for(int k=0; k<longueur;k++) {
		if(t[k]==0) {
			return k;
		}
	}
}

int isIn(int nom, int longueur, structCar t[])
{
    int k=0;
    for(int j=0; j<longueur; j++)
    {
        if(nom==t[j].number)
        {
            k=1;
            break;
        }
    }
    return k;
}

void tempsS1(int i) {
    semop(SemId, &semPlus0, 1);
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
    semop(SemId, &semMoins0, 1);
}

void tempsS2(int i) {
    semop(SemId, &semPlus0, 1);
    double temps;
    double tempsRandom = genereRandom(tempsMinS2, tempsMaxS2);

    crash(i);

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        // Modification du meilleur moment pour le secteur 2 si le nouveau est meilleur
        if(voitures[i].bestS2 < 1 || temps < voitures[i].bestS2){
            voitures[i].bestS2 = temps;
        }
    }
    semop(SemId, &semMoins0, 1);
}
void tempsS3(int i) {
    semop(SemId, &semPlus0, 1);
    double temps;
    double tempsRandom = genereRandom(tempsMinS3, tempsMaxS3);

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
    semop(SemId, &semMoins0, 1);
}

void triVoitures(structCar voituresATrier[], int numCourse) {
	if(numCourse == 1 || numCourse == 2 || numCourse == 3 || numCourse == 4 || numCourse == 7) {
		for(int i=0;i<20;i++) {
			for(int j=0;j<20;j++) {
				if(voituresATrier[i].bestTour == 0) {
					
				}
				else if(voituresATrier[j].bestTour > voituresATrier[i].bestTour || voituresATrier[j].bestTour == 0) {
					semop(SemId, &semPlus0, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins0, 1);
				}
			}
		}
	}
	else if(numCourse == 5) {
		for(int i=0;i<15;i++) {
			for(int j=0;j<15;j++) {
				if(voituresATrier[j].bestTour > voituresATrier[i].bestTour) {
					semop(SemId, &semPlus0, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins0, 1);
				}
			}
		}
	}
	else if(numCourse == 6) {
		for(int i=0;i<10;i++) {
			for(int j=0;j<10;j++) {
				if(voituresATrier[j].bestTour > voituresATrier[i].bestTour) {
					semop(SemId, &semPlus0, 1);
					structCar temporaire = voituresATrier[i];
					voituresATrier[i] = voituresATrier[j];
					voituresATrier[j] = temporaire;
					semop(SemId, &semMoins0, 1);
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
		puts("Choisissez la longueur du circuit. Celle-ci doit être comprise entre 1 et 10");

		if (fgets(s, 100, stdin) == NULL) {
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}

		sscanf(s, "%d", &km); //reads formatted input from a string
	} while (km<1||km>10);
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
	} while (o >1000);
	if(o == 1) {
		semop(SemId, &semPlus1, 1);
		brain[11] = 1;
		semop(SemId, &semMoins1, 1);
	}
	else {
		semop(SemId, &semPlus1, 1);
		brain[11] = 0;
		semop(SemId, &semMoins1, 1);
	}
}


/*void interaction(int i)
{
    char o = demandeAction();
    if(o=='o')
    {
        semop(SemId, &semPlus1, 1);
        brain[i]=0;
        semop(SemId, &semMoins1, 1);
    }
    else
    {
        killIt();
        exit(0);
    }
}*/

void afficherResultatsEssai() {
	printf("|%s|  %s  |     %s    |     %s    |     %s    |    %s   |   %s  |   %s   |\n", "Classement", "Numero", "Best S1", "Best S2", "Best S2", "Best Tour", "Stand", "Out ?");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<20;i++) {
		printf("|    %2d    |    %2d    |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %2d    |    %2d     |\n", i+1, voitures[i].number, voitures[i].bestS1, voitures[i].bestS2, voitures[i].bestS3, voitures[i].bestTour, voitures[i].nbrStand, voitures[i].isOut);
	}
	printf("\n%s%.2f\n", "Meilleur S1 : ", brain[7]);
	printf("\n%s%.2f\n", "Meilleur S2 : ", brain[8]);
	printf("\n%s%.2f\n", "Meilleur S3 : ", brain[9]);
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
	printf("|%s|  %s  |     %s    |     %s    |     %s    |    %s   |   %s  |   %s   |\n", "Classement", "Numero", "Best S1", "Best S2", "Best S2", "Best Tour", "Stand", "Out ?");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0; i<nbrVoitures;i++) {
		printf("|    %2d    |    %2d    |    %7.2f     |    %7.2f     |    %7.2f     |    %7.2f     |    %2d    |    %2d     |\n", i+1, voitures[i].number, voitures[i].bestS1, voitures[i].bestS2, voitures[i].bestS3, voitures[i].bestTour, voitures[i].nbrStand, voitures[i].isOut);
	}
	printf("\n%s%.2f\n", "Meilleur S1 : ", brain[7]);
	printf("\n%s%.2f\n", "Meilleur S2 : ", brain[8]);
	printf("\n%s%.2f\n", "Meilleur S3 : ", brain[9]);	
}
void afficherResultatsCourse() {
	
}

void killIt()
{
    for(int i=1; i<21; i++){
        //envoyer un signal pour tuer le processus avec pid = pidList [i]
        kill(listePid[i], SIGKILL);
    }
}

void wake()
{
    for(int i=1; i<21; i++){
        //envoyer un signal pour réveiller le processus avec pid = pidList [i]
        kill(listePid[i], SIGCONT);
    }
}

void sortCourse(structCar carQualif[], int sizeArrayVoitures)
{
    int i=0;
    structCar tmpCar;
    int j = 0;

    for(i=0; i < sizeArrayVoitures; i++)
    {
        for(j = i+1; j < sizeArrayVoitures; j++)
        {
            if((carQualif[j].tempsTotal < carQualif[i].tempsTotal)&&(carQualif[j].isOut==0))
            {
                tmpCar = carQualif[i];
                carQualif[i] = carQualif[j];
                carQualif[j] = tmpCar;
            }
        }
    }
}

void ajouteTempsEnFctPosition()//en fct de la place de la voiture au début de la course, un temps est ajouté
{
    for (int j = 0; j < 20; j++)
    {
        for(int i = 0; i < 20; i++)
        {
            //if (voitures[i].number == startingBlock[j]){   // ajouter du temps par position par rapport à la première
                voitures[i].tempsTotal += j * 0.3;     // à l'heure normale
                voitures[i].tempsTour = j * 0.3;   // chronométrer sur un tour
            //}
        }
    }
}

void setOut(int q)
{
    if(q==2)
    {
        for(int i=0; i<20; i++)
        {
            int j = isIn(voitures[i].number, 15, qualifiedFor2);
            //si la voiture n'est pas dans voituresQuelif2, nous la disqualifions
            if(j==0)
            {
                voitures[i].isOut=1;
            }
        }
    }
    else
    {
        for(int i=0; i<20; i++)
        {
            int j = isIn(voitures[i].number, 10, qualifiedFor3);
            //si la voiture n'est pas dans voituresQuelif3, nous la disqualifions
            if(j==0)
            {
                voitures[i].isOut=1;
            }
        }
    }
}