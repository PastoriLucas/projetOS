#include "cars.h"
#include "utils.h"
#include "course.h"
#include <stdio.h>
#include <stdlib.h>

/*void triVoitures(structCar car[]){
    int i = 0;
    structCar temps;
    int j = 0;

    for(i = 0; i<20; i++){
        for (j = i+1; j<20; j++){
            if(car[j].nbrTour == car[i].nbrTour && car[j].elapsedTime < car[i].elapsedTime){
               temps = car[i];
               car[i] = car[j];
               car[j] = temps;
            }
            else if(car[j].nbrTour > car[i].nbrTour){
                temps = car[i];
                car[i] = car[j];
                car[j] = temps;
            }
        }
    }
}*/