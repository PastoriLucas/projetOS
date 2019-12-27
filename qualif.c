#include "cars.h"
#include "utils.h"
#include "qualif.h"
#include <stdio.h>
#include <stdlib.h>

double tempsQ1 = 1080;
double tempsQ2 = 900;
double tempsQ3 = 720;

//Tri de voitures
void triVoitures(structCar carQualif[], int sizeArrayCar)
{
    int i=0;
    structCar tempsCar;
    int j = 0;
    //Compare les voitures entre elles (1 avec 1, 1 avec 2, etc)
    for(i=0; i < sizeArrayCar; i++)
        //Remplit le i du tableau
    {
        for(j = i+1; j < sizeArrayCar; j++)
            //Vérifie s'il n'y a pas de nb plus petits dans le cas suivant   PQ
        {
            if(carQualif[j].bestTour < carQualif[i].bestTour)
            {
                //Si vrai, switch les nombres
                tempsCar = carQualif[i];
                carQualif[i] = carQualif[j];
                carQualif[j] = tempsCar;
            }
        }
    }
}

/* void startingBlock(structCar carQualif[], int q){
    int conservee = 0;
    int startArray = 0;
    int conservee2 = 0;
    int startArray2 =0;

    if (q == 1){
        conservee = 20;
        startArray = 15;

        conservee2 = 15;
        startArray2 = 10;
    }
    if (q == 2) {
        conservee = 15;
        startArray = 10;

        conservee2 = 10;
        startArray2 = 0;
    }
    if (q == 3) {
        conservee = 10;
        startArray = 0;
    }

    for(int i = startArray ; i < conservee; i++){
        startPosition[i] = carQualif[i].number;
    }

    for(int i=startArray2; i< conservee2; i++){
        if (q == 1) {
            qualifiedFor2[i] = carQualif[i];
        }
        else if (q == 2){
            qualifiedFor3[i] = carQualif[i];
        }
    }
} 

void qualif(int index, int q){
    semop(SemId, &semWait0, 1);
    semop(SemId, &semDo0, 1);
    double temps = getCurrTemps();
    semop(SemId, &semPost0, 1);
    double tempsQualif = 0.0;

    //determine la durée de l'essai
    if(q==1)
    {
        tempsQualif = tempsQ1;
    }
    if(q==2)
    {
        tempsQualif = tempsQ2;
    }
    if(q==3)
    {
        tempsQualif = tempsQ3;
    }

    //boucle jusqu'à ce que le temps soit écoulé ou que la voiture ait abandonné
    while(temps<tempsQualif && voitures[index].isOut == 0)
    {
        genereTempsS1(index);

        //si la voiture a un meilleur temps pour S1 que toutes les autres, mise à jour de la variable globale
        if(voitures[index].bestS1<brain[7])
        {
            semop(SemId, &semWait1, 1);
            semop(SemId, &semDo1, 1);
            smv[7] = voitures[index].bestS1;
            semop(SemId, &semPost1, 1);
        }
        genereTempsS2(index);

        //si la voiture a un meilleur temps pour S2 que toutes les autres, mise à jour de la variable globale
        if(voitures[index].bestS2<smv[8])
        {
            semop(SemId, &semWait1, 1);
            semop(SemId, &semDo1, 1);
            smv[8] = voitures[index].bestS2;
            semop(SemId, &semPost1, 1);
        }
        genereTempsS3(index);

        //si la voiture a un meilleur temps pour S3 que toutes les autres, mise à jour de la variable globale
        if(voitures[index].bestS3<smv[9])
        {
            semop(SemId, &semWait1, 1);
            semop(SemId, &semDo1, 1);
            smv[9] = voitures[index].bestS3;
            semop(SemId, &semPost1, 1);
        }
        //si la voiture a un meilleur temps du circuit que toutes les autres, mise à jour de la variable globale
        if(voitures[index].bestTour<smv[10])
        {
            semop(SemId, &semWait1, 1);
            semop(SemId, &semDo1, 1);
            brain[10] = voitures[index].bestTour;
            semop(SemId, &semPost1, 1);
        }
        // mise à jour de l'heure actuelle de la course
        semop(SemId, &semWait, 1);
        semop(SemId, &semDo, 1);
        temps = getTemps();
        semop(SemId, &semPost, 1);
    }
    //Ici, mise à jour de la valeur de smv [3], [4] ou [5],
    //indique au processus parent que la voiture a terminé son cycle de qualification.
    if(q==1)
    {
        id_sem = semop(id_sem, &semWait1, 1);
        id_sem = semop(id_sem, &semDo1, 1);
        smv[3]++;
        id_sem = semop(id_sem, &semPost1, 1);
    }
    if(q==2)
    {
        id_sem = semop(id_sem, &semWait1, 1);
        id_sem = semop(id_sem, &semDo1, 1);
        smv[4]++;
        id_sem = semop(id_sem, &semPost1, 1);
    }
    if(q==3)
    {
        id_sem = semop(id_sem, &semWait1, 1);
        id_sem = semop(id_sem, &semDo1, 1);
        smv[5]++;
        id_sem = semop(id_sem, &semPost1, 1);
    }
}

void genereRecapQualifFile()
{
    FILE *fichier = NULL;

    //ouverture du fichier avec l'argument "a" pour annexer chaque entrainement
    fichier = fopen("RecapQualifFile.txt", "a");//cree et ouvre le fichier

    if(fichier != NULL){

        structCar qualif[20];
        for(int i =0; i<20; i++)
        {
            qualif[i]=voitures[i];
        }
        triVoitures(qualif, 20);


        fprintf(fichier, "\n|   Voiture |       Secteur 1 |       Secteur 2  |      Secteur 3  |     Best Tour    |    Temps Total  |   STAND P   |    ABANDON  |\n");
        for(int i = 0; i < 20; i++){

            fprintf(fichier, "*     %2d    *  %10.2lf sec *  %10.2lf sec  * %10.2lf sec  *  %10.2lf sec  *  %10.2lf sec *      %2d     *      %2d     *\n", qualif[i].nombre,qualif[i].bestS1,qualif[i].bestS2,qualif[i].bestS3,qualif[i].bestTour,qualif[i].elapsedTime,qualif[i].nbrStand,qualif[i].isOut);

        }
        fclose(fichier);
    }
    else{
        printf("Ouverture du fichier recap impossible");
    }
    //Après avoir sauvegardé les valeurs dans le fichier, on les initialise, les voitures vont redémarrer
    //l'entrainement suivant avec un nouvel état

    for(int i=0; i<20; i++)
    {
        reset(i);
    }
}
*/
