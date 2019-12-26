#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait = {0,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo = {0,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost = {0,-1,SEM_UNDO|IPC_NOWAIT};

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

int genereRandom(int min, int max){
    int randNbr = rand()%(max + 1 - min) + min;
    return randNbr;
}

int arret(int i){
    int tempsArrete = 0;

    if (genereRandom(0,99) > 80)  {
        voitures[i].nbrStand ++;
        tempsArrete += (genereRandom(24,44)/10,0);
    }
    return tempsArrete;
}

void crash(int index){
    if (genereRandom(0,999) > 998){
        voitures[index].isOut = 1;
    }
}

double getTemps() {
    double temps = 0;
    for (int i=0; i<20; i++){
        if(voitures[i].elapsedTime > temps) {
            temps = voitures[i].elapsedTime;
        }
    }
    return temps;
}

int nbrTour(int km){
    int nbr = 5;			// Le nombre de tours par défaut
    int longueurMinCourse = 50;	// longueur minimale pour une course
    if(km == 0)  //si l'utilisateur n'entre pas de paramètre pour les kilomètres
    {
        return nbr;
    }
    if(longueurMinCourse % km == 0)
    {
        nbr = longueurMinCourse/km;
    }
    else
    {
        nbr = 1 + (longueurMinCourse/km);
    }
    return nbr;
}

int indexOf(int i, int longueur, int t[])
{
    for(int j=0; j<longueur; j++)
    {
        if(i==t[j])
        {
            return j;
        }
    }
    //si le pid n'est pas dans l'onglet, nous renvoyons la longueur de l'onglet pour permettre la détection d'erreur
    return longueur;
}

int isIn(int nom, int longueur, structTuture t[])
{
    int k=0;
    for(int j=0; j<longueur; j++)
    {
        if(nom==t[j].nom)
        {
            k=1;
            break;
        }
    }
    return k;
}

void genereTempsS1(int i)
{
    semop(id_sem, &semWait, 1);
    semop(id_sem, &semDo, 1);
    double temps;

    if(!(isCourse == 1 && voitures[i].numCircuit == 0)){
        voitures[i].currCircuit = 0.0;  //réinitialiser la valeur du temps pour le tour en cours
    }
    double tempsRandom = genereRandom(20,28);

    crash(i); //appelle la fonction pour voir si la voiture tombe en panne

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        //Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
        voitures[i].timeTour += temps;
        voitures[i].elapsedTime += temps;

        // Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
        if(voitures[i].bestS1 < 1 || temps < voitures[i].bestS1){
            voitures[i].bestS1 = temps;
        }
    }
    semop(id_sem, &semPost, 1);
}

void genereTempsS2(int i)
{
    semop(id_sem, &semWait, 1);
    semop(id_sem, &semDo, 1);
    double temps;

    double tempsRandom = genereRandom(24,30);

    crash(i); //appelle la fonction pour voir si la voiture tombe en panne

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        //Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
        voitures[i].timeTour += temps;
        voitures[i].elapsedTime += temps;

        // Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
        if(voitures[i].bestS2 < 1 || temps < voitures[i].bestS2){
            voitures[i].bestS2 = temps;
        }
    }
    semop(id_sem, &semPost, 1);
}

void genereTempsS3(int i)
{
    semop(id_sem, &semWait, 1);
    semop(id_sem, &semDo, 1);
    double temps;

    double tempsRandom = genereRandom(26,32);

    crash(i); //appelle la fonction pour voir si la voiture tombe en panne

    if(voitures[i].isOut == 0){
        temps = tempsRandom;

        //Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
        voitures[i].timeTour += temps;
        voitures[i].elapsedTime += temps;

        // Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
        if(voitures[i].bestS3< 1 || temps < voitures[i].bestS3){
            voitures[i].bestS3 = temps;
        }
    }
    semop(id_sem, &semPost, 1);
    sleep(1);
}

char demandeAction(){
    char o;
    char n[100];
    while (o != 'o' && o != 'n');{
        printf("Voulez-vous continuer?");
        printf("\n[O]ui ou [N]on\n");

        if (fgets(n, 100, stdin) == NULL)
        {
            fprintf(stderr, "erreur lors de la lecture");
            exit(EXIT_FAILURE);
        }

        sscanf(n, "%c", &o);
        o = tolower(o);
    }

    return o;
    }
}

void interaction(int i)
{
    char o = demandeAction();
    if(o=='o')
    {
        semop(id_sem, &semWait1, 1);
        semop(id_sem, &semDo1, 1);
        smv[i]=0;
        semop(id_sem, &semPost1, 1);
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
        kill(pidList[i], SIGKILL);
    }
}

void wake()
{
    for(int i=1; i<21; i++){
        //envoyer un signal pour réveiller le processus avec pid = pidList [i]
        kill(pidList[i], SIGCONT);
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
            if((carQualif[j].currTemps < carQualif[i].currTemps)&&(carQualif[j].isOut==0))
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
            if (voitures[i].nbr == startPosition[j]){   // ajouter du temps par position par rapport à la première
                voitures[i].elapsedTime += j * 0.3;     // à l'heure normale
                voitures[i].timeTour = j * 0.3;   // chronométrer sur un tour
            }
        }
    }
}

void setOut(int q)
{
    if(q==2)
    {
        for(int i=0; i<20; i++)
        {
            int j = isIn(voitures[i].nbr, 15, qualifiedFor2);
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
            int j = isIn(voitures[i].nbr, 10, qualifiedFor3);
            //si la voiture n'est pas dans voituresQuelif3, nous la disqualifions
            if(j==0)
            {
                voitures[i].isOut=1;
            }
        }
    }
}
