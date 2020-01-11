#include "cars.h"
#include "utils.h"
#include "qualif.h"
#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Fonction qui effectue tous les besoins de la course finale
*	-> Assigne des temps à la voiture donnée en paramètre
*	-> Vérifie si la voiture effectue un meilleur temps à chaque secteur
*	-> Effectue ça en boucle jusqu'à ce que la voiture aie atteint le temps maximal pour la course
*/

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