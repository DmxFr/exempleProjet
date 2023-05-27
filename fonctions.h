#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 200
#define MAX_TAILLE_TABLEAU 100
#define MAX_TAILLE_MAGASIN 500
#define NOM_FICHIER_MAGASIN "produits.csv"

//Structure d'un produit
typedef struct produit {
	char nom[MAX_CHARS];
	int numeroRef;
	int quantite;
	float prix;
	int taille; // 1 (petit), 2 (moyen), 4 (grand)
} produit;

//Structure d'un client
typedef struct client {
	char nom[MAX_CHARS];
	char prenom[MAX_CHARS];
	char historiqueAchat[MAX_TAILLE_TABLEAU][MAX_CHARS];
	int nbAchat;
} client;


//Fonctions
void lireFichierProduit(char* nomFichier, produit produits[], int* nbProduit);
void lireFichierClient(char* nomFichier, client* cli);
void sauvegarderFichierProduit(char* nomFichier, produit produits[], int nbProduit);
void sauvegarderFichierClient(client cli);

void gestion(produit produits[], int *nbProduit);
void affichageInitialGestion(produit produits[], int nbProduit);
int tailleActuelleMagasin(produit produits[], int nbProduit);
void afficherProduits(produit produits[], int nbProduit);
int chercherProduitParNom(produit produits[], int nbProduit, char* nomProduit);
int chercherProduitParRef(produit produits[], int nbProduit, int refProduit);

void modeAchat(produit produits[], int *nbProduit);

//Exemple de contenu du fichier produits.csv
/*
Nom;Numéro de référence;Quantité;Prix;Taille
Livre;1;20;50;1
Imprimante 3D;2;10;200;2
Ordinateur pc HP;3;30;1000;1
Ordinateur pc ASUS;4;45;1500;1
Ordinateur desktop Gamer;5;0;2500;3
Ecran 4K;6;30;2000;3
Clavier;7;60;20;1
Souris;8;70;15;1
*/

// Exemple de contenu de fichier d'un client nommé "John DOE"
/*
Nom;Prenom;
DOE;John;
;;
Historique des achats;;
Produit;Quantité;Prix
Exemple 1; 12 exemplaires; 523(euros)
Exemple 2; 13 exemplaires; 43564(euros)
Exemple 3; 2 exemplaires; 675(euros)
Exemple 4; 16 exemplaires; 574(euros)
Exemple 5; 5 exemplaires; 467(euros)
Exemple 6; 6 exemplaires; 48(euros)
Exemple 7; 9 exemplaires; 34(euros)
*/