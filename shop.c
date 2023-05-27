#include "fonctions.h"

/*
Fonction principale du programme
*/
int main()
{
	int choixMenu=0;
	int nbPoduits=0;
	produit magasin[MAX_TAILLE_TABLEAU];

	lireFichierProduit(NOM_FICHIER_MAGASIN, magasin, &nbPoduits);

	//Menu principal
	printf("\nMENU PRINCIPAL\n\n");
	do {
		printf("Choisissez le mode :\n");
		printf("1 - Mode GESTION\n");
		printf("2 - Mode ACHAT\n");
		printf("3 - Quitter le programme\n");
		//L'utilisateur doit faire un choix correct
		do {
			scanf("%d", &choixMenu);
			if (choixMenu<1 || choixMenu>3)
			{
				printf("Faites un choix correct : ");
			}
		}while(choixMenu<1 || choixMenu>3);
		//Exécution du mode choisi
		switch(choixMenu)
		{
		case 1:
			printf("\nMODE GESTION\n");
			gestion(magasin, &nbPoduits);
			break;
		case 2:
			printf("\nMODE ACHAT\n");
			modeAchat(magasin, &nbPoduits);
			break;
		case 3:
			printf("\nFIN DU PROGRAMME\n");
			break;
		}
	}while(choixMenu!=3);
	return 0;
}