#include "cars.h"
#include "utils.h"

void initialiserVoitures(int i, int nbr) {
	voitures[i].number = nbr;       //Numero de la voiture
	voitures[i].bestTour = 0;       //Meilleur temps sur un tour de circuit
	voitures[i].bestS1 = 0;         //Meilleur temps sur le premier secteur
	voitures[i].bestS2 = 0;         //Meilleur temps sur le deuxieme secteur
	voitures[i].bestS3 = 0;          //Meilleur temps sur le troisieme secteur
	voitures[i].nbrTour = 0;         //Nombre de tours déjà effectués
	voitures[i].elapsedTime = 0;     //Temps écoulé depuis le début de la course
	voitures[i].timeTour = 0;       //Heure actuelle de la course
	voitures[i].nbrStand = 0;        /*nombre de fois qu'il a passé le stand (entre 1 et 3) */
	voitures[i].isOut = 0;            //0 si la voiture continue de rouler, 1 si elle s'écrase
	
	if(i<10)
	{
		qualifiedFor2[i].number = nbr;
		qualifiedFor2[i].bestTour = 0;
		qualifiedFor2[i].bestS1 = 0;
		qualifiedFor2[i].bestS2 = 0;
		qualifiedFor2[i].bestS3 = 0;
		qualifiedFor2[i].nbrTour = 0;
		qualifiedFor2[i].elapsedTime = 0;
		qualifiedFor2[i].timeTour = 0;
		qualifiedFor2[i].nbrStand = 0;
		qualifiedFor2[i].isOut = 0;
	}
	if(i>=10 && i< 15)
	{
		qualifiedFor2[i].number = nbr;
		qualifiedFor2[i].bestTour = 0;
		qualifiedFor2[i].bestS1 = 0;
		qualifiedFor2[i].bestS2 = 0;
		qualifiedFor2[i].bestS3 = 0;
		qualifiedFor2[i].nbrTour = 0;
		qualifiedFor2[i].elapsedTime = 0;
		qualifiedFor2[i].timeTour = 0;
		qualifiedFor2[i].nbrStand = 0;
		qualifiedFor2[i].isOut = 0;
		qualifiedFor3[i].number = nbr;
		qualifiedFor3[i].bestTour = 0;
		qualifiedFor3[i].bestS1 = 0;
		qualifiedFor3[i].bestS2 = 0;
		qualifiedFor3[i].bestS3 = 0;
		qualifiedFor3[i].nbrTour = 0;
		qualifiedFor3[i].elapsedTime = 0;
		qualifiedFor3[i].timeTour = 0;
		qualifiedFor3[i].nbrStand = 0;
		qualifiedFor3[i].isOut = 0;
	}
}