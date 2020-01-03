#include "cars.h"
#include "utils.h"
#include "essai.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int genererEssai(int essai, int numPid) {
	int tempsTotalEssai;
	if(essai == 1 || essai == 2) {
		tempsTotalEssai = 5400;
	}
	if(essai == 3) {
		tempsTotalEssai = 3600; //Normalement 3600 (1h00)
	}
	voitures[numPid].bestS1 = 0;
	voitures[numPid].bestS2 = 0;
	voitures[numPid].bestS3 = 0;
	voitures[numPid].isOut = 0;
	voitures[numPid].bestTour = 0;
	voitures[numPid].tempsTotal = 0;
	
										/* ************************************
										Début de la boucle de la séance d'essai
										************************************ */
										
										
	while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalEssai) {
		voitures[numPid].tempsTour = 0;
		if(voitures[numPid].isOut == 0) {
			tempsS1(numPid);	
			if((voitures[numPid].bestS1 < (double)brain[7]) || ((double)brain[7] < 1)) {
				semop(SemId, &semPlus1, 1);
				brain[7] = (voitures[numPid].bestS1);
				semop(SemId, &semMoins1, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			tempsS2(numPid);
			if((voitures[numPid].bestS2 < (double)brain[8]) || ((double)brain[8] < 1)) {
				semop(SemId, &semPlus1, 1);
				brain[8] = (voitures[numPid].bestS2);
				semop(SemId, &semMoins1, 1);
			}
		}
		
		if(voitures[numPid].isOut == 0) {
			tempsS3(numPid);
			if((voitures[numPid].bestS3 < (double)brain[9]) || ((double)brain[9] < 1)) {
				semop(SemId, &semPlus1, 1);
				brain[9] = (voitures[numPid].bestS3);
				semop(SemId, &semMoins1, 1);
			}
		}	
		if(voitures[numPid].isOut == 0) {
			if(voitures[numPid].bestTour < 1 || voitures[numPid].tempsTour < voitures[numPid].bestTour) {
				voitures[numPid].bestTour = voitures[numPid].tempsTour;
			}
		}
	}
	if(voitures[numPid].isOut == 0) {
		arret(numPid);
	}
	
	if(essai == 1) {
		semop(SemId, &semPlus1, 1);
		brain[0]++;
		semop(SemId, &semMoins1, 1);
	}
	if(essai == 2) {
		semop(SemId, &semPlus1, 1);
		brain[1]++;
		semop(SemId, &semMoins1, 1);
	}
	if(essai == 3) {
		semop(SemId, &semPlus1, 1);
		brain[2]++;
		semop(SemId, &semMoins1, 1);
	}	
}