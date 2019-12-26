#include "cars.h"
#include "utils.h"
#include "essai.h"

int genererEntrainement(int essai) {
	double temps_entrainement;
	if(essai == 1 || essai == 2) {
		temps_entrainement = 300; //Normalement 5400 (1h30)
	}
	if(essai == 3) {
		temps_entrainement = 200; //Normalement 3600 (1h00)
	}
	if(voitures[essai].isOut == 0) {
		
	}
	/*
	printf("%s%d%s%d\n", "Meilleur temps pour P1 : ", bestTimeP1[1], ". Voiture ", bestTimeP1[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P2 : ", bestTimeP2[1], ". Voiture ", bestTimeP2[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P3 : ", bestTimeP3[1], ". Voiture ", bestTimeP3[0]);
	*/
	
}