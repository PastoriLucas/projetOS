#ifndef voiture.h
#define _VOITURE_H

typedef struct structCar {
		int number;         //numero de la voiture
		double bestTour; 	//Meilleur temps sur un tour de circuit
		double bestS1;      //Meilleur temps sur le premier secteur
		double bestS2;      //Meilleur temps sur le deuxieme secteur
		double bestS3;      //Meilleur temps sur le troisieme secteur
		int nbrTour;    	//Nombre de tours déjà effectués
		double elapsedTime; //Temps écoulé depuis le début de la course
		double timeTour; 	//Heure actuelle de la course
		int nbrStand;       //nombre de fois qu'il a passé le stand (entre 1 et 3)
		int isOut;          //0 si la voiture est toujours en marche, 1 si c'est le crash
	}structCar;
	
void initialiserVoitures(int i, int nbr);

void crash(int index);

#endif