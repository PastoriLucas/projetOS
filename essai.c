#include "cars.h"
#include "utils.h"
#include "essai.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int genererEssai(int essai, int numPid) {
	int tempsTotalEssai;
	if(essai == 1 || essai == 2) {
		tempsTotalEssai = 200; //Normalement 5400 (1h30)
	}
	if(essai == 3) {
		tempsTotalEssai = 100; //Normalement 3600 (1h00)
	}
	/* ************************************
	Début de la boucle de la séance d'essai
	************************************ */
	//while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalEssai) {
	
		tempsS1(numPid);	
		if((voitures[numPid].bestS1 < (double)brain[7]) || ((double)brain[7] < 1)) {
			semop(SemId, &semWait1, 1);
			semop(SemId, &semDo1, 1);
			brain[7] = (voitures[numPid].bestS1);
			semop(SemId, &semPost1, 1);
		}

		tempsS2(numPid);
		if((voitures[numPid].bestS2 < (double)brain[8]) || ((double)brain[8] < 1)) {
			semop(SemId, &semWait1, 1);
			semop(SemId, &semDo1, 1);
			brain[8] = (voitures[numPid].bestS2);
			semop(SemId, &semPost1, 1);
		}
		
		tempsS3(numPid);
		if((voitures[numPid].bestS3 < (double)brain[9]) || ((double)brain[9] < 1)) {
			semop(SemId, &semWait1, 1);
			semop(SemId, &semDo1, 1);
			brain[9] = (voitures[numPid].bestS3);
			semop(SemId, &semPost1, 1);
		}
		
	//}
	
	semop(SemId, &semWait1, 1);
	semop(SemId, &semDo1, 1);
	brain[0]++;
	semop(SemId, &semPost1, 1);
}