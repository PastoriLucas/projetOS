#include "cars.h"
#include "utils.h"

void creerVoitures(int i, int nbr) {
	voitures[i].number = nbr;    	//Numero de voiture
	voitures[i].nbrTour = 0;   		//Nombre de tours effectués
	voitures[i].tempsTour = 0;  	//Temps effectué pour le tour en cours
	voitures[i].bestS1 = 0;      	//Meilleur temps secteur 1
	voitures[i].bestS2 = 0;       	//Meilleur temps secteur 2
	voitures[i].bestS3 = 0;       	//Meilleur temps secteur 3
	voitures[i].bestTour = 0;  		//Meilleur tour de circuit
	voitures[i].tempsTotal = 0;    	//Temps écoulé depuis le début de la course
	voitures[i].nbrStand = 0;      	//Nombre d'arrêts au stand (1-3)
	voitures[i].isOut = 0;        	//Se met à 1 si la voiture se crash
	voitures[i].isQualifiedFor2 = 0;//Se met à 1 si la voiture est qualifiée pour la 2e qualif
	voitures[i].isQualifiedFor3 = 0;//Se met à 1 si la voiture est qualifiée pour la 3e qualif
}