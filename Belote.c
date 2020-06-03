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
// output : Array initialized to -1
void InitializedArray(CARTE* Deckofcards, int Sizeofdeckofcards){
	for (int i = 0; i < Sizeofdeckofcards; i++){
		Deckofcards[i].valeur = -1;
		Deckofcards[i].couleur = -1;
	}
}

// This function takes the IA card game and plays the IA, it returns the card played by the IA.
// input paramater : remaining decks of cards to be played
// input paramater : current turn number (use only for access to the correct portion of the array that implements the deck of cards)
// parmater output : Played Card by IA
// output : Card deck remaining to be played reinitialized so that the played card is removed and the array is consistent in relation to (Currentturnnumber + 1)
CARTE PlayIA(CARTE* IAcardgame, int Currentturnnumber){
	int i=0;
	int iMax = 0;
	int maxRemainingCardNumber = carteparjoueur - Currentturnnumber;
	for (i = 1; i < maxRemainingCardNumber; i++){
		if (IAcardgame[i].valeur > IAcardgame[iMax].valeur){
			iMax = i;
		}
	}
	printf("The IA chose to play the card %s of %s\n", TabValeur[IAcardgame[iMax].valeur], TabCouleur[IAcardgame[iMax].couleur]);
	printf("\n");

	//Find index of card to be removed
	
	for (int i = iMax; i < maxRemainingCardNumber -1; i++){
		IAcardgame[i] = IAcardgame[i + 1];
	}
	return IAcardgame[iMax];
}




//This function takes as input parameter an array initialized at -1 to fill it with map. The function returns the array of cards, that is the deck of cards
// input paramater : Empty card game  
// output: card game  which is sorted by color and ascending order
void FillAnArrayWithCards(CARTE* Emptycardgame){
	int val, coul, i;;
	i = 0;
	for (coul = 0; coul < nombrejoueur; coul++){
		for (val = 0; val < carteparjoueur; val++){
			Emptycardgame[i].valeur = val;
			Emptycardgame[i].couleur = coul;
			printf(" %d -- %s de %s \n", i, TabValeur[Emptycardgame[i].valeur], TabCouleur[Emptycardgame[i].couleur]);
			i++;
		}
		printf("\n");
	}
}


// The ShuffleADeckOfCards function takes an incrementally ordered deck of cardsand returns a deck that is a random permutation of the incoming deck.  
// parameter input : a sorted card game
// return : a shuffled card game with random permutation
void ShuffleADeckOfCards(CARTE* Sortedcardgame){
	for (int iCarte = (nombrecartepaquet - 1); iCarte >= 0; --iCarte){
		int jCarte = rand() % (iCarte + 1);
		CARTE temp = Sortedcardgame[iCarte];
		Sortedcardgame[iCarte] = Sortedcardgame[jCarte];
		Sortedcardgame[jCarte] = temp;
	}
}

// This function does'nt takes any parameter input but it allocates a piece of memory to an array. it allocates this memory for an array of arrays (two dimensional array)
// output :  Array of arrays allocated
CARTE** AllocateMemoryForAnArrayofArrays() {
	CARTE** Twodimensionalarray = malloc(nombrejoueur * sizeof(CARTE*));
	for (int i = 0; i < nombrejoueur; i++) {
		Twodimensionalarray[i] = (CARTE*)malloc(carteparjoueur * sizeof(CARTE));
	}
	return Twodimensionalarray;
}

// The function DistributeADeckOfCardsPerPlayer takes a shuffled deck of cards and an empty per-player card array  and returns the per-player card array filled with the elements of the shuffled deck of cards (games).
// input : a deck of cards which is shuffled
// input : a two dimensional array which is the per-player card array 
// output : an array of arrays fill of shuffled cards -> i.e. cards per player
CARTE** DistributeADeckOfCardsPerPlayer(CARTE* Shuffleddeckofcards, CARTE** Cardsperplayer){
	int i, j, m;
	m = 0;
	for (i = 0; i < nombrejoueur; i++){
		for (j = 0; j < carteparjoueur; j++){
			Cardsperplayer[i][j] = Shuffleddeckofcards[m];
			printf("Player %d card number %d = %s de %s \n", i, j, TabValeur[(Cardsperplayer[i][j]).valeur], TabCouleur[(Cardsperplayer[i][j]).couleur]);
			m++;
		}
		printf("\n");
	}
	return Cardsperplayer;
}

// This function doesn't have a in put parameter but it allocates memory for a deck of cards , fills and shuffles this deck of cards. Secondly it allocates memory for a two dimensional array which is the cards per-player and distribute the cards of the deck between the players
// output : a two dimensional array which correspond to the cards per-player
CARTE** DistributingAndShufflingADeckOfCards(){
	CARTE* deckofcards = (CARTE*)malloc(nombrecartepaquet * sizeof(CARTE));
	FillAnArrayWithCards(deckofcards);
	ShuffleADeckOfCards(deckofcards);
	CARTE** cardsperplayer = AllocateMemoryForAnArrayofArrays();
	DistributeADeckOfCardsPerPlayer(deckofcards, cardsperplayer);
	return cardsperplayer;
}

// This function takes in entry a two dimensional array and tranforms it on a one dimensional array : in order to do so you need the index (which is actually the player's number) of the first dimension of the array which will correspond to the player's cards in the second dimension of the array.
//This function allocates memory to an array and returns the array filled by the cards of one player of the two dimensional array.
// input : a two dimensional array fills by the cards per-player
// input : the player number which corresponds to the index
// output : the cards of one player on an array.
CARTE* ChangeFromATwoDimensionalArrayToASingleArray(CARTE** Cardsperplayer, int Playernumber){
	CARTE* cardsofoneplayer = malloc(carteparjoueur * sizeof(CARTE));
	InitializedArray(cardsofoneplayer, carteparjoueur);
	for (int i = 0; i < carteparjoueur; i++){
		cardsofoneplayer[i] = Cardsperplayer[Playernumber][i];
	}
	return cardsofoneplayer;
}


CARTE JouerUneCarte(CARTE* cartedujoueur, CARTE cartechoisie, int compteurtour){
	printf("Vous jouez la carte qui a pour valeur %s de %s\n", TabValeur[cartechoisie.valeur], TabCouleur[cartechoisie.couleur]);
	printf("Il vous reste maintenant les carte suivant\n");
	for (int i = 0; i < carteparjoueur-compteurtour; i++){
		if (cartedujoueur[i].valeur == cartechoisie.valeur && cartedujoueur[i].couleur == cartechoisie.couleur){
			while (i < carteparjoueur - compteurtour){
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


CARTE ChoisirUneCarte(CARTE* cartedujoueur, int compteurtour){
	CARTE cartechoisi = { 0,0 };
	int i = 0;
	printf("Choisissez la carte que vous voulez jouer en tapant le numero de la carte:\n");
	for (i = 0; i < carteparjoueur - compteurtour; i++){
		printf("Voici la carte %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	}
	scanf("%d", &i);
	while (i < 0 || i >= carteparjoueur - compteurtour){
		printf("Cette carte n'existe pas, choisissez un autre numero :\n");
		scanf("%d", &i);
	}

	printf("Vous avez choisi la carte numero %d qui a pour valeur %s de %s\n", i, TabValeur[cartedujoueur[i].valeur], TabCouleur[cartedujoueur[i].couleur]);
	cartechoisi = cartedujoueur[i];
	return cartechoisi;
}

CARTE JouerHumain(CARTE* cartedujoueur, int compteurtour){
	CARTE cartechoisi = { 0,0 };
	CARTE cartejouer;
	cartechoisi = ChoisirUneCarte(cartedujoueur, compteurtour);
	cartejouer = JouerUneCarte(cartedujoueur, cartechoisi, compteurtour);
	return cartejouer;
}

const char* TesterTypeJoueur(){
	const char* typedujoueur;
	int reponse;
	printf("Es-tu un humain ? (1 pour oui 0 pour non)\n");
	scanf("%d", &reponse);
	if (reponse == 1){
		typedujoueur = typejoueur1;
	}
	else{
		typedujoueur = typejoueur2;
	}
	printf("Vous etes donc du type %s\n", typedujoueur);
	return typedujoueur;
}


void AjouterCarteAuTourCourant(CARTE cartejouer, CARTE* cartedutourjouer, int nombrecartejouer){
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
	for (i = 1; i < nombrecartejouer; i++){
		pointsDuGagnant += cartedutourjouer[i].valeur;
		if (cartedutourjouer[i].valeur > max.valeur){
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
void JouerUnJoueurHumain(CARTE* Cartehumain, CARTE* cartedutourjouer, int nombrecartejouer, int compteurtour){
	CARTE cartejouer = { 0,0 };
	cartejouer = JouerHumain(Cartehumain, compteurtour);
	AjouterCarteAuTourCourant(cartejouer, cartedutourjouer, nombrecartejouer);
	
}

void JouerUnJoueurIA(CARTE* CarteIA, CARTE* cartedutourjouer,  int nombrecartejouer, int compteurtour){
	CARTE cartejouerIA = { 0,0 };
	cartejouerIA = PlayIA(CarteIA, compteurtour);
	AjouterCarteAuTourCourant(cartejouerIA, cartedutourjouer, nombrecartejouer);
}


void JouerUnTour(CARTE* Joueurhumain, CARTE* JoueurIA1, CARTE* JoueurIA2, CARTE* JoueurIA3, int* compteurjoueur, int compteurtour){
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

void JouerUnePartie(){
	int compteurjoueur[4] = { 0 };
	CARTE** Jeuxjoueur;
	Jeuxjoueur = DistributingAndShufflingADeckOfCards();
	CARTE* Joueurhumain0 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA1 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA2 = malloc(carteparjoueur * sizeof(CARTE*));
	CARTE* JoueurIA3 = malloc(carteparjoueur * sizeof(CARTE*));
	int joueurhumain = 0;
	int joueurIA1 = 1;
	int joueurIA2 = 2;
	int joueurIA3 = 3;
	Joueurhumain0 = ChangeFromATwoDimensionalArrayToASingleArray(Jeuxjoueur, joueurhumain);
	JoueurIA1 = ChangeFromATwoDimensionalArrayToASingleArray(Jeuxjoueur, joueurIA1);
	for (int i = 0; i < carteparjoueur; i++){
		printf("IA1 %d -- %s de %s \n", i, TabValeur[JoueurIA1[i].valeur], TabCouleur[JoueurIA1[i].couleur]);
	}
	printf("\n");
	JoueurIA2 = ChangeFromATwoDimensionalArrayToASingleArray(Jeuxjoueur, joueurIA2);
	for (int i = 0; i < carteparjoueur; i++){
		printf("IA2 %d -- %s de %s \n", i, TabValeur[JoueurIA2[i].valeur], TabCouleur[JoueurIA2[i].couleur]);
	}
	printf("\n");
	JoueurIA3 = ChangeFromATwoDimensionalArrayToASingleArray(Jeuxjoueur, joueurIA3);
	for (int i = 0; i < carteparjoueur; i++){
		printf("IA3 %d -- %s de %s \n", i, TabValeur[JoueurIA3[i].valeur], TabCouleur[JoueurIA3[i].couleur]);
	}
	int compteurtour = 0;
	for (int i = 0; i < carteparjoueur; i++){
		JouerUnTour(Joueurhumain0, JoueurIA1, JoueurIA2, JoueurIA3, compteurjoueur, compteurtour);
		compteurtour++;
	}
	
}




int main()
{
	JouerUnePartie();

}
