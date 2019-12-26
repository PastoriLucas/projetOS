int genererEntrainement(int i) {
	int x;

	for(x=0; x<4; x++) {
		if(fork() == 0) {
			printf("%s%d%s\n", " voiture ", x, " : ");
			double temps_random;
			int i, n;
			time_t t;
			double temps_total;
			n = 3;
			temps_total = 0;
			srand(time(NULL));
			
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 1 : ", temps_random);
			
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 2 : ", temps_random);
				
			sleep(0.50);
				temps_random = ((double)rand()/RAND_MAX*6.0-0.0)+24;
				temps_total += temps_random;
				printf("%s%.3f\n", "temps au secteur 3 : ", temps_random);
			
			printf("%s%.3f\n", "temps total pour la course : ", temps_total);
			return 0;
		}
	sleep(1);
	}
	semop(SemId, &semPost0, 1);
	/*
	printf("%s%d%s%d\n", "Meilleur temps pour P1 : ", bestTimeP1[1], ". Voiture ", bestTimeP1[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P2 : ", bestTimeP2[1], ". Voiture ", bestTimeP2[0]);
	printf("%s%d%s%d\n", "Meilleur temps pour P3 : ", bestTimeP3[1], ". Voiture ", bestTimeP3[0]);
	*/
	
}