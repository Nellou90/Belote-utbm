#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
const  char typejoueur1[] = "humain";
const char typejoueur2[] = "IA";
const int nombrejoueur = 4;
const int nombrecartepaquet = 32;
const int carteparjoueur = 8;
const int taillecartedutourjouer = 4;

const char* TabValeur[] = { "7", "8", "9", "10", "valet", "dame", "roi", "As" };
const char* TabCouleur[] = { "trefle", "pique", "coeur", "carreau" };

typedef struct _CARTE_ {
	int valeur;
	int couleur;

} CARTE;

// This function takes two cards as input and returns a tie between the two cards.
// input parameter : Card 1.
// input parameter : Card 2.
// parameter output : Card 1 equal Card 2.
int EqualsCards(CARTE c0, CARTE c1) {
	return ((c0.valeur == c1.valeur) && (c0.couleur == c1.couleur));
}

// This function takes a deck of cards as input and returns an initialized deck of cards.
// input parameter : a deck of cards ( in the form of an array)
// input parameter : the size of the array to browse it

void InitializedArray(CARTE* Deckofcards, int SizeofDeckofcards)
{
	for (int i = 0; i < SizeofDeckofcards; i++)
	{
		Deckofcards[i].valeur = -1;
		Deckofcards[i].couleur = -1;
	}
}

// This function takes the IA card game and plays the IA, it returns the card played by the IA.
// input paramater : remaining decks of cards to be played
// input paramater : current turn number (use only for access to the correct portion of the array that implements the deck of cards)
// parmater output : Played Card
// parmater output : Card deck remaining to be played reinitialized so that the played card is removed and the array is consistent in relation to (Currentturnnumber + 1)
CARTE PlayIA(CARTE* IAcardgame, int Currentturnnumber)
{
	int i=0;
	int iMax = 0;
	int maxRemainingCardNumber = carteparjoueur - Currentturnnumber;
	for (i = 1; i < maxRemainingCardNumber; i++){
		if (IAcardgame[i].valeur > IAcardgame[iMax].valeur){
			iMax = i;
		}
	}
	printf("The IA chose to play the card %s of %s\n", TabValeur[IAcardgame[iMax].valeur], TabCouleur[IAcardgame[iMax].couleur]);

	//Find index of card to be removed
	
	for (int i = iMax; i < maxRemainingCardNumber -1; i++){
		IAcardgame[i] = IAcardgame[i + 1];
	}
	return IAcardgame[iMax];
}




// La fonction Initialiser prend un tableau vide pour le remplir de carte. La fonction retourne le tableau de carte, alias le jeux de carte,  initialisée.
// en entree: jeuxdecarte est 
// en sortie: jeux de carte modifié
void InitialiserJeux(CARTE* jeuxdecarte)
{
	int val, coul, i;;
	i = 0;
	for (coul = 0; coul < nombrejoueur; coul++)
	{
		for (val = 0; val < carteparjoueur; val++)
		{
			jeuxdecarte[i].valeur = val;
			jeuxdecarte[i].couleur = coul;
			printf(" %d -- %s de %s \n", i, TabValeur[jeuxdecarte[i].valeur], TabCouleur[jeuxdecarte[i].couleur]);
			i++;

		}
	}
}

// La fonction melanger prend un jeu de carte ordonné de manière croissante (pCarte) et renvoie un paquet qui est une permutation aleatoire du paquet en entré  
void Melanger(CARTE* pCarte)
{
	for (int iCarte = (nombrecartepaquet - 1); iCarte >= 0; --iCarte)
	{
		int jCarte = rand() % (iCarte + 1);
		CARTE temp = pCarte[iCarte];
		pCarte[iCarte] = pCarte[jCarte];
		pCarte[jCarte] = temp;

	}
}

CARTE** allouerJeuDeCarteParjoueur() {
	CARTE** jeuJoueurs = malloc(nombrejoueur * sizeof(CARTE*));
	for (int i = 0; i < nombrejoueur; i++) {
		jeuJoueurs[i] = (CARTE*)malloc(carteparjoueur * sizeof(CARTE));
	}
	return jeuJoueurs;
}

// La fonction DistribuerCarteParJoueur prend un jeux de carte mélangé (jeux) et un tableau de carte par joueur vide (Cartejoueur) et renvoie le tableau de carte par joueur remplie avec les élément du jeux de carte mélangée (jeux).
CARTE** DistribuerCarteParJoueur(CARTE* jeux, CARTE** Cartejoueur)
{
	int i, j, m;
	m = 0;
	for (i = 0; i < nombrejoueur; i++)
	{
		for (j = 0; j < carteparjoueur; j++)
		{
			Cartejoueur[i][j] = jeux[m];
			printf("joueur %d carte numero %d = %s de %s \n", i, j, TabValeur[(Cartejoueur[i][j]).valeur], TabCouleur[(Cartejoueur[i][j]).couleur]);
			m++;
		}
	}
	return Cartejoueur;
}

CARTE** Distribuer()
{
	CARTE* Jeuxdecarte = (CARTE*)malloc(nombrecartepaquet * sizeof(CARTE));
	InitialiserJeux(Jeuxdecarte);
	Melanger(Jeuxdecarte);
	CARTE** JeuxJoueur = allouerJeuDeCarteParjoueur();
	DistribuerCarteParJoueur(Jeuxdecarte, JeuxJoueur);
	return JeuxJoueur;
}

// LA fonction TranformationCarteparjoueurEnCartedunjoueur prend les jeux de cartes des joueurs regroupées dans un tableau pour retournée un jeux de carte individuelle.
CARTE* TranformationCarteparjoueurEnCartedunjoueur(CARTE** Carteparjoueur, int numerojoueur)
{
	CARTE* Jeuxdunjoueur = malloc(carteparjoueur * sizeof(CARTE));
	InitializedArray(Jeuxdunjoueur, carteparjoueur);
	for (int i = 0; i < carteparjoueur; i++)
	{
		Jeuxdunjoueur[i] = Carteparjoueur[numerojoueur][i];
	}
	return Jeuxdunjoueur;
}

CARTE JouerUneCarte(CARTE* cartedujoueur, CARTE cartechoisie, int compteurtour)
{
	printf("Vous jouez la carte qui a pour valeur %s de %s\n", TabValeur[cartechoisie.valeur], TabCouleur[cartechoisie.couleur]);
	printf("Il vous reste maintenant les carte suivant\n");
	for (int i = 0; i < carteparjoueur-compteurtour; i++)
	{
		if (cartedujoueur[i].valeur == cartechoisie.valeur && cartedujoueur[i].couleur == cartechoisie.couleur)
		{
			while (i < carteparjoueur - compteurtour)
			{
				cartedujoueur[i] = cartedujoueur[i + 1];
				i++;
			}
			break;
		}
	}

	for (int i = 0; i < carteparjoueur - compteurtour - 1; i++)
		printf(" %d -- %s de %s \n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	CARTE cartejouer = cartechoisie;
	return cartejouer;


}
CARTE ChoisirUneCarte(CARTE* cartedujoueur, int compteurtour)
{
	CARTE cartechoisi = { 0,0 };
	int i = 0;
	printf("Choisissez la carte que vous voulez jouer en tapant le numero de la carte:\n");
	for (i = 0; i < carteparjoueur - compteurtour; i++)
	{

		printf("Voici la carte %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);

	}
	scanf("%d", &i);
	while (i < 0 || i >= carteparjoueur - compteurtour)
	{
		printf("Cette carte n'existe pas, choisissez un autre numero :\n");
		scanf("%d", &i);
	}

	printf("Vous avez choisi la carte numero %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	cartechoisi = cartedujoueur[i];
	return cartechoisi;
}

CARTE JouerHumain(CARTE* cartedujoueur, int compteurtour)
{
	CARTE cartechoisi = { 0,0 };
	CARTE cartejouer;
	cartechoisi = ChoisirUneCarte(cartedujoueur, compteurtour);
	cartejouer = JouerUneCarte(cartedujoueur, cartechoisi, compteurtour);
	return cartejouer;
}

const char* TesterTypeJoueur()
{
	const char* typedujoueur;
	int reponse;
	printf("Es-tu un humain ? (1 pour oui 0 pour non)\n");
	scanf("%d", &reponse);
	if (reponse == 1)
	{
		typedujoueur = typejoueur1;
	}
	else
	{
		typedujoueur = typejoueur2;
	}
	printf("Vous etes donc du type %s\n", typedujoueur);
	return typedujoueur;
}


void AjouterCarteAuTourCourant(CARTE cartejouer, CARTE* cartedutourjouer, int nombrecartejouer)
{
	cartedutourjouer[nombrecartejouer].valeur = cartejouer.valeur;
	cartedutourjouer[nombrecartejouer].couleur = cartejouer.couleur;
}


// 
int CompterResultatDuTour(CARTE* cartedutourjouer, int nombrecartejouer, int* compteurjoueur)
{
	int i;
	CARTE max = cartedutourjouer[0];
	int numeroJoueurGagnant = 0;
	int pointsDuGagnant = cartedutourjouer[0].valeur;
	for (i = 1; i < nombrecartejouer; i++)
	{
		pointsDuGagnant += cartedutourjouer[i].valeur;
		if (cartedutourjouer[i].valeur > max.valeur)
		{
			max=cartedutourjouer[i];
			numeroJoueurGagnant = i;
		}
		else if (cartedutourjouer[i].valeur == max.valeur) {
			numeroJoueurGagnant = -1;
		}
	}

	if (numeroJoueurGagnant != -1) {
		compteurjoueur[numeroJoueurGagnant] = compteurjoueur[numeroJoueurGagnant] + pointsDuGagnant;
		printf("Le joueur %d, gangne. Son score est augmente de %d, et atteint %d.\n", numeroJoueurGagnant, pointsDuGagnant, compteurjoueur[numeroJoueurGagnant]);
	}
	else {
		printf("Aumoins 2 joueurs sont ex aequo, La somme des points perdus est de %d.\n", pointsDuGagnant);
	}
	return (numeroJoueurGagnant != -1);
}


// La fonction JouerUnJoueur prend les carte d'un joueur et retourne la carte jouée.
void JouerUnJoueurHumain(CARTE* Cartehumain, CARTE* cartedutourjouer, int nombrecartejouer, int compteurtour)
{
	CARTE cartejouer = { 0,0 };
	cartejouer = JouerHumain(Cartehumain, compteurtour);
	AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);
	
}

void JouerUnJoueurIA(CARTE* CarteIA, CARTE* cartedutourjouer,  int nombrecartejouer, int compteurtour)
{
	CARTE cartejouerIA = { 0,0 };
	cartejouerIA = PlayIA(CarteIA, compteurtour);
	AjouterCarteAuTourCourant(cartejouerIA, cartedutourjouer, nombrecartejouer);
}


void JouerUnTour(CARTE* Joueurhumain, CARTE* JoueurIA1, CARTE* JoueurIA2, CARTE* JoueurIA3, int* compteurjoueur, int compteurtour)
{
	int gagnanttour = 0;
	CARTE* cartedutourjouer = malloc(taillecartedutourjouer * sizeof(CARTE));
	InitializedArray(cartedutourjouer, taillecartedutourjouer);
	int nombrecartejouer = 0;
	JouerUnJoueurHumain(Joueurhumain, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA1, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA2, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	JouerUnJoueurIA(JoueurIA3, cartedutourjouer, nombrecartejouer, compteurtour);
	nombrecartejouer++;
	printf("\n");
	gagnanttour = CompterResultatDuTour(cartedutourjouer, nombrecartejouer, compteurjoueur);
}

void JouerUnePartie()
{
	int compteurjoueur[4] = { 0 };
	CARTE** Jeuxjoueur;
	Jeuxjoueur = Distribuer();
	CARTE* Joueurhumain0 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA1 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA2 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA3 = malloc(carteparjoueur * sizeof(CARTE*));
	int joueurhumain = 0;
	int joueurIA1 = 1;
	int joueurIA2 = 2;
	int joueurIA3 = 3;
	Joueurhumain0 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurhumain);
	JoueurIA1 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA1);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA1 %d -- %s de %s \n", i, TabValeur[JoueurIA1[i].valeur], TabCouleur[JoueurIA1[i].couleur]);
	}
	printf("\n");
	JoueurIA2 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA2);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA2 %d -- %s de %s \n", i, TabValeur[JoueurIA2[i].valeur], TabCouleur[JoueurIA2[i].couleur]);
	}
	printf("\n");
	JoueurIA3 = TranformationCarteparjoueurEnCartedunjoueur(Jeuxjoueur, joueurIA3);
	for (int i = 0; i < carteparjoueur; i++)
	{
		printf("IA3 %d -- %s de %s \n", i, TabValeur[JoueurIA3[i].valeur], TabCouleur[JoueurIA3[i].couleur]);
	}
	int compteurtour = 0;
	for (int i = 0; i < carteparjoueur; i++)
	{
		JouerUnTour(Joueurhumain0, JoueurIA1, JoueurIA2, JoueurIA3, compteurjoueur, compteurtour);
		compteurtour++;
	}
	
}




int main()
{
	JouerUnePartie();

	




	//	int compteurjoueur[4] = { 0 };
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("%d\n", compteurjoueur[i]);
	//	}
	//	int cartedutourjouer[4] = { 2,2,3,4 };
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("%d\n", cartedutourjouer[i]);
	//	}
	//	 //int nombrecartejouer = 0;
	//	// initialisertour(cartedutourjouer);
	//	 //testertypejoueur();
	//	/*int mescarte[4]={1,2,3,4};
	//	int cartejouer;
	//	cartejouer=jouerhumain(mescarte, nombrecarte);*/
	//	/*nombrecartejouer=AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);*/
	//	int nombrecarte = 4;
	//    CompterResultatDuTour(cartedutourjouer, nombrecarte, compteurjoueur);
	//	for (int i = 0; i < 4; i++)
	//    {
	//	    printf("%d\n", compteurjoueur[i]);
	//	}
	//
}
