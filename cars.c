#include "cars.h"
#include "utils.h"

void initialiserVoitures(int i, int nbr) {
	voitures[i].number = nbr;    	//Numero de la voiture
	voitures[i].bestTour = 0;  		//Meilleur temps sur un tour de circuit
	voitures[i].bestS1 = 0;      	//Meilleur temps sur le premier secteur
	voitures[i].bestS2 = 0;       	//Meilleur temps sur le deuxieme secteur
	voitures[i].bestS3 = 0;       	//Meilleur temps sur le troisieme secteur
	voitures[i].nbrTour = 0;   		//Nombre de tours déjà effectués
	voitures[i].tempsTotal = 0;    	//Temps écoulé depuis le début de la course
	voitures[i].tempsTour = 0;  	//Temps effectué pour le tour en cours
	voitures[i].nbrStand = 0;      	//Nombre de fois qu'il a passé le stand (entre 1 et 3)
	voitures[i].isOut = 0;        	//0 si la voiture continue de rouler, 1 si elle s'écrase
	voitures[i].isQualifiedFor2 = 0;
	voitures[i].isQualifiedFor3 = 0;
}