#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait0 = {0,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo0 = {0,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost0 = {0,-1,SEM_UNDO|IPC_NOWAIT};

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait1 = {1,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo1 = {1,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost1 = {1,-1,SEM_UNDO|IPC_NOWAIT};

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait2 = {2,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo2 = {2,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost2 = {2,-1,SEM_UNDO|IPC_NOWAIT};

double genereRandom(double min, double max){
    double div = RAND_MAX/(max - min);
    return min + (rand() / div);
}

int arret(int i) {
    int tempsArrete = 0;

    if (genereRandom(0,99) > 80)  {
        voitures[i].nbrStand ++;
        tempsArrete += (genereRandom(24,44)/10,0);
    }
    return tempsArrete;
}

void crash(int numPid){
    if (genereRandom(0,150) > 149){
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
    semop(SemId, &semWait0, 1);
    semop(SemId, &semDo0, 1);
	voitures[i].tempsTour = 0.0;
    double temps;
	double tempsRandom = genereRandom(tempsMinS1,tempsMaxS1);

	//crash(i);
    if(voitures[i].isOut == 0){
        temps = tempsRandom;
		
        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        if(voitures[i].bestS1 < 1 || temps < voitures[i].bestS1){
            voitures[i].bestS1 = temps;
        }
    }
    semop(SemId, &semPost0, 1);
}

void tempsS2(int i) {
    semop(SemId, &semWait0, 1);
    semop(SemId, &semDo0, 1);
    double temps;
    double tempsRandom = genereRandom(tempsMinS2, tempsMaxS2);

    //crash(i);

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        // Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
        if(voitures[i].bestS2 < 1 || temps < voitures[i].bestS2){
            voitures[i].bestS2 = temps;
        }
    }
    semop(SemId, &semPost0, 1);
}

void tempsS3(int i)
{
    semop(SemId, &semWait0, 1);
    semop(SemId, &semDo0, 1);
    double temps;

    double tempsRandom = genereRandom(26,32);

    crash(i); //appelle la fonction pour voir si la voiture tombe en panne

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        //Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
        voitures[i].tempsTour += temps;
        voitures[i].tempsTotal += temps;

        // Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
        if(voitures[i].bestS3< 1 || temps < voitures[i].bestS3){
            voitures[i].bestS3 = temps;
        }
    }
    semop(SemId, &semPost0, 1);
    sleep(1);
}

char demandeKilometrage() {
int km;
	char s[100];
	printf("Bienvenue au Grand Prix de Formule 1 !\n");
	do
	{
		puts("Choisissez la longueur du circuit. Celle-ci doit être comprise entre 1 et 10\n");

		if (fgets(s, 100, stdin) == NULL) //It reads a line from the specified stream and stores it into the string pointed to by st
		{
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}

		sscanf(s, "%d", &km); //reads formatted input from a string
	} while (km<1||km>10);
	calculerTempsMax(km);
}

char demandeAction(){
    char o;
    char n[100];
	printf("Voulez-vous continuer?");
	printf("\n[O]ui ou [N]on\n");

	sscanf(n, "%c", &o);
	o = tolower(o);
    return o;
}


void interaction(int i)
{
    char o = demandeAction();
    if(o=='o')
    {
        semop(SemId, &semWait1, 1);
        semop(SemId, &semDo1, 1);
        brain[i]=0;
        semop(SemId, &semPost1, 1);
    }
    else
    {
        killIt();
        exit(0);
    }
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
