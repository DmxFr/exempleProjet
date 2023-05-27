#include "fonctions.h"

/*
IL EST IMPORTANT QUE TOUS LES FICHIERS CONTENANT DES INFORMATIONS DE CLIENTS OU
PRODUITS SOIENT AU FORMAT CSV ET CONTENANT AUANT DE COLONNES QUE DE VARIABLE DE
LA STRUCTURE CORRESPONDANTE ET DANS LES MÊMES ORDRES QUE LA LECTURE DES
VARIABLE DANS CES STRUCTURES. SINON	RISQUE DE COMPOREMENT ANORMAL DU PROGRAMME.
*/

//Cette fonction lit le fichier des produits
void lireFichierProduit(char* nomFichier, produit produits[], int* nbProduit)
{
	FILE* fichier=NULL;
	char nomTmp[] = "produits/";
	strcat(nomTmp, nomFichier);
	fichier = fopen(nomTmp, "r");
	if (fichier==NULL)
	{
		printf("\nAucun produit en stock !!!\n");
	}
	else
	{
		char ligne[MAX_CHARS];
		*nbProduit = 0;
		//On ignore l'en-tête
		fgets(ligne, MAX_CHARS, fichier);
		//On récupère le reste des lignes
		while (fgets(ligne, MAX_CHARS, fichier)) {
			produit tmp;
			char *token;

			token = strtok(ligne, ";");
			strcpy(tmp.nom, token);

			token = strtok(NULL, ";");
			tmp.numeroRef = atoi(token);

			token = strtok(NULL, ";");
			tmp.quantite = atoi(token);

			token = strtok(NULL, ";");
			tmp.prix = atof(token);

			token = strtok(NULL, ";\n");
			tmp.taille = atoi(token);

			//On ajoute le nouveau produit récupéré dans le tableau de produits
			produits[*nbProduit] = tmp;

			///On incrémente le nombre de produit
			*nbProduit = *nbProduit + 1;
		}

		fclose(fichier);
	}
}

//Cette fonction lit et charge les informations d'un client
void lireFichierClient(char* nomFichier, client* cli)
{
	FILE* fichier=NULL;
	char nomTmp[] = "clients/";
	strcat(nomTmp, nomFichier);
	fichier = fopen(nomTmp, "r");
	if (fichier==NULL)
	{
		printf("\nCe client n'est pas enregistré !!!\n");
	}
	else
	{
		char *token;
		char ligne[MAX_CHARS];
		
		//On ignore l'en-tête
		fgets(ligne, MAX_CHARS, fichier);

		//On récupère le nom et le prénom
		fgets(ligne, MAX_CHARS, fichier);
		token = strtok(ligne, ";");
		strcpy(cli->nom, token);
		token = strtok(NULL, ";");
		strcpy(cli->prenom, token);

		//On ignore une ligne vide et deux lignes d'en-tête
		fgets(ligne, MAX_CHARS, fichier);
		fgets(ligne, MAX_CHARS, fichier);
		fgets(ligne, MAX_CHARS, fichier);

		//On récupère l'historique d'achat
		cli->nbAchat = 0;
		while (fgets(ligne, MAX_CHARS, fichier) && cli->nbAchat < MAX_TAILLE_TABLEAU) {
			strcpy(cli->historiqueAchat[cli->nbAchat], token);

			///On incrémente le nombre d'achat
			cli->nbAchat = cli->nbAchat + 1;
		}

		fclose(fichier);
	}
}

//Cette fonction sauvegarde la liste des produits dans le fichier des produits
void sauvegarderFichierProduit(char* nomFichier, produit produits[], int nbProduit)
{
	FILE* fichier=NULL;
	char nomTmp[] = "produits/";
	strcat(nomTmp, nomFichier);
	fichier = fopen(nomTmp, "w+");
	if (fichier==NULL)
	{
		printf("\nErreur lors de l'ouverture du fchier des produits !!!\n");
	}
	else
	{
		printf("...Debut de la sauvegarde des produits\n");
		fprintf(fichier, "Nom;Numéro de référence;Quantité;Prix;Taille\n");
		for (int i = 0; i < nbProduit; i++)
		{
			fprintf(fichier, "%s;%d;%d;%.2f;%d\n", produits[i].nom, produits[i].numeroRef, produits[i].quantite, produits[i].prix, produits[i].taille);
		}

		fclose(fichier);
		printf("...Fin de la sauvegarde des produits\n");
	}
}

//Cette fonction sauvegarde les informations d'un client dans son fichier
/*
LE NOM DU FICHIER D'UN CLIENT EST TOUJOURS SOUS LA FORME prenom_nom.csv 
IL EST DONC IMPORTANT D'ENREGISTRER UN SEUL NOM (séparer par des _ au cas 
où le nom est en plusieurs mots) ET UN SEUL PRENOM (séparer par des _ au cas 
où le prénom est en plusieurs mots) POUR CHAQUE CLIENT ET 
NE PAS LES INTERVERTIR
*/
void sauvegarderFichierClient(client cli)
{
	FILE* fichier=NULL;
	char nomFichier[MAX_CHARS];
	strcpy(nomFichier, "clients/");
	strcat(nomFichier, cli.prenom);
	strcat(nomFichier, "_");
	strcat(nomFichier, cli.nom);
	strcat(nomFichier, ".csv");

	fichier = fopen(nomFichier, "w+");
	if (fichier==NULL)
	{
		printf("\nErreur lors de l'ouverture du fchier client %s !!!\n", nomFichier);
	}
	else
	{
		fprintf(fichier, "Nom;Prenom;\n");
		fprintf(fichier, "%s;%s;\n", cli.nom, cli.prenom);
		fprintf(fichier, ";;\n");
		fprintf(fichier, "Historique des achats;;\n");
		fprintf(fichier, "Produit;Quantité;Prix\n");

		for (int i = 0; i < cli.nbAchat; i++)
		{
			fprintf(fichier, "%s", cli.historiqueAchat[i]);
		}

		fclose(fichier);
	}
}

//Cette fonction exécute le mode GESTION
void gestion(produit produits[], int *nbProduit)
{
	int choixGestion=0;
	int indiceSelectonne=-1;
	int intTmp=0;
	affichageInitialGestion(produits, *nbProduit);
	do {
		printf("\nChoisissez une action :\n");
		printf("1 - Afficher la liste complète des produits\n");
		printf("2 - Augmenter le stock d'un produit\n");
		printf("3 - Chercher un produit avec son nom\n");
		printf("4 - Chercher un produit avec sa référence\n");
		printf("5 - Quitter le mode GESTION\n");
		//L'utilisateur doit faire un choix correct
		do {
			scanf("%d", &choixGestion);
			if (choixGestion<1 || choixGestion>5)
			{
				printf("Faites un choix correct : ");
			}
		}while(choixGestion<1 || choixGestion>5);
		//Exécution du choix
		switch(choixGestion)
		{
		case 1:
			afficherProduits(produits, *nbProduit);
			break;
		case 2:
			printf("\nEntrez le numéro de référence du produit : ");
			scanf("%d", &intTmp);
			indiceSelectonne = chercherProduitParRef(produits, *nbProduit, intTmp);
			if (indiceSelectonne==-1)
			{
				printf("Cette référence ne correspond à aucun produit. Voulez vous créer un nouveau produit avec cette référence ? (1=oui, 0=non) : ");
				int nouvelleRef = intTmp;
				scanf("%d", &intTmp);
				if (intTmp==1)
				{
					printf("\nEntrez le nom du produits (mettez _ à la place des espaces) : ");
					scanf("%s", produits[*nbProduit].nom);
					for (int i = 0; i < (int)strlen(produits[*nbProduit].nom); i++)
					{
						if (produits[*nbProduit].nom[i]=='_')
						{
							produits[*nbProduit].nom[i] = ' ';
						}
					}
					//printf("...produits[%d].nom = _%s_\n", *nbProduit, produits[*nbProduit].nom);
					produits[*nbProduit].numeroRef = nouvelleRef;
					printf("Entrez la quantité du produit : ");
					scanf("%d", &produits[*nbProduit].quantite);
					printf("Entrez le prix du produit : ");
					scanf("%f", &produits[*nbProduit].prix);
					printf("Entrez la taille du produit : ");
					scanf("%d", &produits[*nbProduit].taille);
					int taillePrediction = (produits[*nbProduit].quantite * produits[*nbProduit].taille) + tailleActuelleMagasin(produits, *nbProduit);
					if (taillePrediction > MAX_TAILLE_MAGASIN)
					{
						printf("Espace insuffisant dans le magasin !! Il manque %d place(s) pour accepter ce ravitaillement.\n", taillePrediction - MAX_TAILLE_MAGASIN);
					}
					else
					{
						produits[indiceSelectonne].quantite += intTmp;
						printf("Produit (%s) ajouté avec succès !\n", produits[*nbProduit].nom);
						*nbProduit = *nbProduit + 1;
						sauvegarderFichierProduit(NOM_FICHIER_MAGASIN, produits, *nbProduit);
					}
				}
			}
			else
			{
				//printf("%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", indiceSelectonne, produits[indiceSelectonne].nom, produits[indiceSelectonne].numeroRef, produits[indiceSelectonne].quantite, produits[indiceSelectonne].prix, produits[indiceSelectonne].taille);
				printf("\nEntrez la quantité du nouvel arrivage : ");
				scanf("%d", &intTmp);
				int taillePrediction = (intTmp * produits[indiceSelectonne].taille) + tailleActuelleMagasin(produits, *nbProduit);
				if (taillePrediction > MAX_TAILLE_MAGASIN)
				{
					printf("Espace insuffisant dans le magasin !! Il manque %d place(s) pour accepter ce ravitaillement.\n", taillePrediction - MAX_TAILLE_MAGASIN);
				}
				else
				{
					printf("Stock augmenté avec succès !\n");
					produits[indiceSelectonne].quantite += intTmp;
					sauvegarderFichierProduit(NOM_FICHIER_MAGASIN, produits, *nbProduit);
				}
			}
			break;
		case 3:
			printf("\nEntrez le nom du produits (ou un mot contenu dans le nom) : ");
			char nomTmp[MAX_CHARS];
			scanf("%s", nomTmp);
			for (int i = 0; i < (int)strlen(nomTmp); i++)
			{
				nomTmp[i] = (char)toupper(nomTmp[i]);
			}
			if (chercherProduitParNom(produits, *nbProduit, nomTmp)==-1)
			{
				printf("AUCUN PRODUIT CORRESPONDANT !!\n");
			}
			break;
		case 4:
			printf("\nEntrez le numéro de référence du produits : ");
			scanf("%d", &intTmp);
			if (chercherProduitParRef(produits, *nbProduit, intTmp)==-1)
			{
				printf("AUCUN PRODUIT CORRESPONDANT !!\n");
			}
			break;
		case 5:
			printf("\nFin du mode GESTION\n");
			break;
		}
	}while(choixGestion!=5);
}

//Cette fonction essaie d'afficher le top 5 des produits à faibles effectifs non nuls ainsi que les produits en rupture de stock
void affichageInitialGestion(produit produits[], int nbProduit)
{
	//Indices des produits critiques
	int produitsCritiques[5] = {-1, -1, -1, -1, -1};
	int quantites[nbProduit];
	int indice[nbProduit];
	
	//On essaie de trouver le top 5 des produits à faibles effectifs non nuls
	//On récupère d'abord les quantités et leurs indices
	for (int i = 0; i < nbProduit; i++)
	{
		quantites[i] = produits[i].quantite;
		indice[i] = i;
	}
	//Ensuite on tri le tableau des quantités par ordre croissant et on s'assure que les indices gardent le même ordre que la quantité correspondantes
	for (int i = 0; i < nbProduit; i++)
	{
		for (int j = i; j < nbProduit; j++)
		{
			if (quantites[i]>quantites[j])
			{
				//Quantités
				int k=quantites[i];
				quantites[i] = quantites[j];
				quantites[j] = k;
				//Indices
				k=indice[i];
				indice[i] = indice[j];
				indice[j] = k;
			}
		}
	}
	//On prélève maintenant le top 5 des plus faibles quantité
	int nul=1;
	int nbIndice=0;
	for (int i = 0; i<nbProduit && nbIndice<5; i++)
	{
		if (quantites[i]!=0)
		{
			nul=0;
		}
		if (nul==0)
		{
			produitsCritiques[nbIndice] = indice[i];
			nbIndice++;
		}
	}

	//On affiche la liste des produits à effectifs critiques
	printf("\n---------------Produits à effectifs critiques---------------\n");
	for (int i = 0; i < 5; i++)
	{
		if (produitsCritiques[i]!=-1)
		{
			printf("%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", produitsCritiques[i], produits[produitsCritiques[i]].nom, produits[produitsCritiques[i]].numeroRef, produits[produitsCritiques[i]].quantite, produits[produitsCritiques[i]].prix, produits[produitsCritiques[i]].taille);
		}
	}
	for (int i = 0; i < nbProduit; i++)
	{
		if (produits[i].quantite==0)
		{
			printf("%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", i, produits[i].nom, produits[i].numeroRef, produits[i].quantite, produits[i].prix, produits[i].taille);
		}
	}
	printf("------------------------------------------------------------\n");
	printf("Charge actuelle du magasin : %d sur %d\n", tailleActuelleMagasin(produits, nbProduit), MAX_TAILLE_MAGASIN);
	if (tailleActuelleMagasin(produits, nbProduit)>MAX_TAILLE_MAGASIN)
	{
		printf("MAGASIN EN SURCHARGE !!!\n");
	}
	printf("------------------------------------------------------------\n");
}

//Cette fonction actueealise la taille actuelle du magasin
int tailleActuelleMagasin(produit produits[], int nbProduit)
{
	int taille = 0;
	for (int i = 0; i < nbProduit; i++)
	{
		taille += (produits[i].taille * produits[i].quantite);
	}
	return taille;
}

//Cette fonction affiche la liste de tous les produits
void afficherProduits(produit produits[], int nbProduit)
{
	printf("\n---------------Liste des produits---------------\n");
	for (int i = 0; i < nbProduit; i++)
	{
		printf("%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", i, produits[i].nom, produits[i].numeroRef, produits[i].quantite, produits[i].prix, produits[i].taille);
	}
	printf("------------------------------------------------\n");
}

//Cette fonction cherche et affiche un produit avec son nom
int chercherProduitParNom(produit produits[], int nbProduit, char* nomProduit)
{
	int retour=-1;
	printf("RESULTATS DE RECHERCHE :\n");
	for (int i = 0; i < nbProduit; i++)
	{
		char nomTmp[strlen(produits[i].nom)];
		for (int j = 0; j < (int)strlen(produits[i].nom); j++)
		{
			nomTmp[j] = toupper(produits[i].nom[j]);
		}
		if (strstr(nomTmp, nomProduit)!=NULL)
		{
			printf("%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", i, produits[i].nom, produits[i].numeroRef, produits[i].quantite, produits[i].prix, produits[i].taille);
			retour = 0;
		}
	}
	return retour;
}

//Cette fonction cherche et affiche un produit avec sa référence
int chercherProduitParRef(produit produits[], int nbProduit, int refProduit)
{
	int indice=-1;
	printf("RESULTATS DE RECHERCHE :\n");
	for (int i = 0; i < nbProduit; i++)
	{
		if (refProduit==produits[i].numeroRef)
		{
			printf("\n%d - %s, (Ref)%d, (Quantité)%d, %.2f(euros), (Taille)%d\n", i, produits[i].nom, produits[i].numeroRef, produits[i].quantite, produits[i].prix, produits[i].taille);
			indice = i;
			break;
		}
	}
	return indice;
}

////////////////////////////////////////////////////////////////////////////

//Cette fonction exécute le mode achat
void modeAchat(produit produits[], int *nbProduit)
{
	int choixAchat=0;
	int indiceSelectonne=-1;
	int intTmp=0;
	int clientExistant=0;
	char nomTmp[MAX_CHARS];
	char nomFichier[MAX_CHARS];
	char nom[MAX_CHARS];
	char prenom[MAX_CHARS];
	char tmp[MAX_CHARS];
	client c;

	afficherProduits(produits, *nbProduit);
	do {
		printf("\nChoisissez une action :\n");
		printf("1 - Faire un achats\n");
		printf("2 - Afficher les informations d'un client\n");
		printf("3 - Quitter le mode ACHAT\n");
		//L'utilisateur doit faire un choix correct
		do {
			scanf("%d", &choixAchat);
			if (choixAchat<1 || choixAchat>3)
			{
				printf("Faites un choix correct : ");
			}
		}while(choixAchat<1 || choixAchat>3);
		//Exécution du choix
		switch(choixAchat)
		{
		case 1:
			printf("IMPORTANT : Si le fichier du client n'existe pas, il sera créer\n");
			strcpy(nomTmp, "clients/");
			printf("Entrez le prénom du client (pas d'espace) : ");
			scanf("%s", tmp);
			strcpy(prenom, tmp);
			
			strcat(nomTmp, tmp);
			strcpy(nomFichier, tmp);
			strcat(nomTmp, "_");
			strcat(nomFichier, "_");
			
			printf("Entrez le nom du client (pas d'espace) : ");
			scanf("%s", tmp);
			strcpy(nom, tmp);
			
			strcat(nomTmp, tmp);
			strcat(nomFichier, tmp);
			strcat(nomTmp, ".csv");
			strcat(nomFichier, ".csv");
			
			//Test d'ouverture pour vérifier que le fichier du client existe
			FILE* test = fopen(nomTmp, "r");
			if (test==NULL)
			{
				clientExistant = 0;
			}
			else 
			{
				clientExistant = 1;
				fclose(test);
			}
			if (clientExistant==1)
			{
				lireFichierClient(nomFichier, &c);
			}
			else
			{
				strcpy(c.nom, nom);
				strcpy(c.prenom, prenom);
				c.nbAchat = 0;
			}
			int finAchat=0;
			int quantiteAchat=0;
			int nbTotalAchat=0;
			float totalAchat=0;
			do
			{
				printf("Faites un choix : \n");
				printf("1 - Nouvel achat\n");
				printf("2 - Fin des achats\n");
				scanf("%d", &finAchat);
				if (finAchat==1)
				{
					printf("\nEntrez le numéro de référence du produit : ");
					scanf("%d", &intTmp);
					indiceSelectonne = chercherProduitParRef(produits, *nbProduit, intTmp);
					if (indiceSelectonne==-1)
					{
						printf("Cette référence ne correspond à aucun produit !!");
					}
					else
					{
						printf("----------------------- Produit\n");
						printf("\nEntrez la quantité à acheter : ");
						scanf("%d", &quantiteAchat);
						if (quantiteAchat>produits[indiceSelectonne].quantite)
						{
							printf("Stock insuffisant !!!\n");
						}
						else
						{
							//L'achat proprement dit se passe ici
							//On réduit le stock
							produits[indiceSelectonne].quantite -= quantiteAchat;
							nbTotalAchat++;
							totalAchat += quantiteAchat*produits[indiceSelectonne].prix;
							sprintf(c.historiqueAchat[c.nbAchat], "%s; %d exemplaires; %.2f(euros)\n", produits[indiceSelectonne].nom, quantiteAchat, quantiteAchat*produits[indiceSelectonne].prix);
							c.nbAchat = c.nbAchat + 1;
							sauvegarderFichierProduit(NOM_FICHIER_MAGASIN, produits, *nbProduit);
							sauvegarderFichierClient(c);
							clientExistant = 1;
						}
					}
				}
				else
				{
					printf("-------------- Total : %.2f\n", totalAchat);
				}
			}while(finAchat!=2);

			int choixFidelite=0;
			printf("\nVoulez vous rester abonné à ce magasin ? (1=oui, 0=non) : \n");
			scanf("%d", &choixFidelite);
			if (choixFidelite==1)
			{
				sauvegarderFichierClient(c);
			}
			else
			{
				if (clientExistant==1)
				{
					if (remove(nomTmp)==0)
					{
						printf("\nFichier client supprimé !\n");
					}
				}
			}
			break;
		case 2:
			printf("Entrez le prénom du client (pas d'espace) : ");
			strcpy(nomTmp, "clients/");
			scanf("%s", tmp);
			strcpy(nomFichier, tmp);
			strcat(nomTmp, tmp);
			strcat(nomFichier, "_");
			strcat(nomTmp, "_");
			printf("Entrez le nom du client (pas d'espace) : ");
			scanf("%s", tmp);
			strcat(nomFichier, tmp);
			strcat(nomTmp, tmp);
			strcat(nomFichier, ".csv");
			strcat(nomTmp, ".csv");
			//Test d'ouverture pour vérifier que le fichier du client existe
			FILE* test2 = NULL;
			test2 = fopen(nomTmp, "r");
			if (test2==NULL)
			{
				clientExistant = 0;
			}
			else 
			{
				clientExistant = 1;
				fclose(test2);
			}
			if (clientExistant==1)
			{
				lireFichierClient(nomFichier, &c);
				printf("\nCompte client :\n");
				printf("--------------------------------\n");
				printf("Prénom : %s\n", c.prenom);
				printf("Nom : %s\n", c.nom);
				printf("Historique des achats :\n");
				printf("Nom;Numéro de référence;Quantité;Prix;Taille\n");
				for (int i = 0; i < c.nbAchat; i++)
				{
					printf("%s", c.historiqueAchat[i]);
				}
				printf("\n--------------------------------\n");
			}
			else
			{
				printf("\nCE CLIENT N'EXISTE PAS !!\n");
			}
			break;
		case 3:
			printf("\nFin du mode ACHAT\n");
			break;
		}
	}while(choixAchat!=3);
}