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
	//while(voitures[numPid].isOut == 0 && voitures[numPid].tempsTotal < tempsTotalEssai) {
		
	tempsS1(numPid);	
	if(voitures[numPid].bestS1 < (double)brain[7]) {
		semop(SemId, &semWait1, 1);
		semop(SemId, &semDo1, 1);
		brain[7] = (voitures[numPid].bestS1);
		semop(SemId, &semPost1, 1);
	}
	//}
	semop(SemId, &semWait1, 1);
	semop(SemId, &semDo1, 1);
	brain[0]++;
	semop(SemId, &semPost1, 1);
}