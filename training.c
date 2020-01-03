#include "cars.h"
#include "utlis.h"
#include "training.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "qualif.h"
#include "course.h"

double t5400 = 5400;
double t3600 = 3600;

void training(int index, int nbrTraining){
    semop(id_sem, &semWait, 1);
    semop(id_sem, &semDo, 1);
    double temps = getCurrTemps();
    semop(id_sem, &semPost, 1);

    if (nbrTraining == 1 || nbrTraining == 2){
        double x = t5400;
    }
    if (nbrTraining == 3){
        double x = t3600;
    }

    while(temps < x && (voitures[index].isOut == 0)){

        TempsS1(index);

        if(voitures[index].bestS1 < smv[7]){
            semop(id_sem, &semWait1 < 1);
            semop(id_sem, &semDo1, 1);
            smv[7] = voitures[index].bestS1;
            semop(id_sem, &semPost1, 1);
        }

        TempsS2(index);

        if(voitures[index].bestS2 < smv[8]){
            semop(id_sem, &semWait1 < 1);
            semop(id_sem, &semDo1, 1);
            smv[8 = voitures[index].bestS2;
            semop(id_sem, &semPost1, 1);
        }

        TempsS3(index);

        if(voitures[index].bestS3 < smv[9]){
            semop(id_sem, &semWait1 < 1);
            semop(id_sem, &semDo1, 1);
            smv[9] = voitures[index].bestS3;
            semop(id_sem, &semPost1, 1);
        }
    }

    for (int i = 1; i < 4; i++){
        if (nbrTraining == i){
            semop(id_sem, &semWait1, 1);
            semop(id_sem, &semDo1, 1);
            smv[i-1]++;
            semop(id_sem, &semPost1, 1);
        }
    }
}

void RecapTraining(){

    structCar tableau[20];
    for (int i = 0 ; i < 20 ; i++){
        tableau[i] = voitures[i];
    }

    triVoitures(tableau, 20);

    printf("Voiture    |    S1    |    S2    |    S3    |    Meilleur Tour    |    Total    |    Stand    |    Sortie    |\n");
    for (int j = 0; j <20 ; j++) {
        printf ("* %2d       * %10.21f sec * %10.21f sec * %10.21 sec * %10.21f sec * 10.21f sec *    %2d    *    %2d    *\n", tableau[j].number, tableau[j].bestS1, tableau[j].bestS2, tableau[j].bestS3, tableau[j].bestTour, tableau[j].tempsTotal, tableau[j].nbrStand, tableau[j].isOut);
    }

    for (int k = 0; k < 20 ; k++) {
        reset(k);
    }
}