#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if defined(_WIN32) || defined(__MSDOS__)
#include<windows.h>
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#else
#define SPADE   "Spade" //\xE2\x99\xA0"
#define CLUB    "Club"  //\xE2\x99\xA3"
#define HEART   "Heart" // \xE2\x99\xA5"
#define DIAMOND "Diamond" //\xE2\x99\xA6"
#endif

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
//const  char typejoueur1[] = "humain";
//const char typejoueur2[] = "IA";
const int numberofplayer = 4;
const int numberofcardsinthedeck = 32;
const int numberofcardperplayer = 8;
const int sizeofreferencingarray = 4;
const int numberofcolor = 4;


// This is the constant value of cards
const char* TabValue[] = { "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
// This is the constant color of cards
const char* TabColor[] = { CLUB, SPADE, HEART, DIAMOND };
// This is the constant name of players
const char* TabName[] = { "Human", "George", "Audrey", "Jack" };

// The struct CONTRACT integrates in it-self the value of the contract and the color of the contract
typedef struct _CONTRACT_ {
	int valueContract;
	int colorContract;
} CONTRACT;

// The struct CARD integrates in it-self the value and the color of a card and if the card is an atout or not
typedef struct _CARD_ {
	int index;
	int color;
	int trump;
} CARD;

// This function allows for each card of a player's game to say if it is a trump: 1 yes, 0 no.
// It takes in entry the deck of cards of a player and the trump of the part.
// It returns the deck of cards of a player with the trump part in the struct CARD filled.
void FillTheTrumpPartOfTheStructCard(CARD* Deckofcardsplayer, int Trump) {
	for (int i = 0; i < numberofcardperplayer; i++) {
		if (Deckofcardsplayer[i].color == Trump) {
			Deckofcardsplayer[i].trump = 1;
		}
		else {
			Deckofcardsplayer[i].trump = 0;
		}
	}
}

// The purpose of this function is to randomly draw the player who will start bidding.
// It hasn't parameter input but it returns the player who will start bidding.
// output : Player who will start bidding;
int ChooseRandomlyAPlayerWhoWillStartBidding() {
	int playerwhowillstartbidding = rand() % 4;
	return playerwhowillstartbidding;
}

// This fonction has as goal to ask to human player how many point he projects to do during the part of the games.
// The function has in entry the deck of cards of the human and return the contract of the human.
// input : deck of cards of the human 
// input : Asset
// output : Human contract
CONTRACT ContractOfAHuman(CARD* Deckofcardshuman, CONTRACT Bestcontractofthepart) {
	CONTRACT humancontract;
	int answer;
	int answer2;
	printf("\n");
	printf("Here are your cards : \n");
	for (int i = 0; i < numberofcardperplayer; i++) {
		printf("%s of %s\n", TabValue[Deckofcardshuman[i].index], TabColor[Deckofcardshuman[i].color]);
	}
	printf("\n");
	printf("You have two choice : \n");
	printf("\n");
	printf("PASS : 0          			CONTRACT : 1\n");
	printf("\n");
	scanf("%d", &answer);
	while (answer != 1 && answer != 0) {
		printf("Error, try again : ");
		printf("\n");
		scanf("%d", &answer);
	}
	if (answer == 0) {
		humancontract.valueContract = 0;
		humancontract.colorContract = -1;

	}
	else if (answer == 1) {
		printf("Choose the color of your contract : \n");
		printf("\n");
		printf("\n");
		printf("%s : 0			%s : 1			%s : 2			%s : 3	", TabColor[0], TabColor[1], TabColor[2], TabColor[3]);
		printf("\n");
		scanf("%d", &(humancontract.colorContract));
		while (humancontract.colorContract < 0 && humancontract.colorContract >3) {
			printf("Error, try again :\n");
			printf("\n");
			scanf("%d", &(humancontract.colorContract));
		}
		printf("Choose your contract between 80 and 160 : \n");
		printf("\n");
		scanf("%d", &(humancontract.valueContract));
 		while (humancontract.valueContract < 80 && humancontract.valueContract > 160 || humancontract.valueContract <= Bestcontractofthepart.valueContract) {
			printf("Attention your contract must be superior to the contract of the previous player. \n Press 0 to PASS and 1 to CONTINUE\n");
			printf("\n");
			scanf("%d", &answer2);
			while (answer2 != 0 && answer2 != 1) {
				printf("Error, try again :\n");
				printf("\n");
				scanf("%d", &answer2);
			}
			if (answer2 == 0) {
				humancontract.valueContract = 0;
				humancontract.colorContract = -1;
				break;
			}
			else if (answer2 == 1) {
				scanf("%d", &(humancontract.valueContract));
			}
		}
	}
	printf("\n");
	return humancontract;
}

// This fonction has as goal to ask to IA player how many point it projects to do during the part of the games.
// The function has in entry the deck of cards of the IA, the Asset, the number of the IA and return the contract of the IA.
// input : deck of cards of the IA 
// input : Asset
// input : the number of the IA
// output : IA contract
CONTRACT ContractOfAnIA(CARD* DeckofcardsIA, int IAnumber, CONTRACT Bestcontractofthepart) {
	CONTRACT IAcontract;
	int hardvalueandcolor[4] = { 0 };
	for (int j = 0; j < numberofcolor; j++) {
		for (int i = 0; i < numberofcardperplayer; i++) {
			if (DeckofcardsIA[i].index == 4 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 8;
			}
			else if (DeckofcardsIA[i].index == 2 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 7;
			}
			else if (DeckofcardsIA[i].index == 7 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 6;
			}
			else if (DeckofcardsIA[i].index == 3 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 5;
			}
			else if (DeckofcardsIA[i].index == 6 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 4;
			}
			else if (DeckofcardsIA[i].index == 5 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 3;
			}
			else if (DeckofcardsIA[i].index == 1 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 2;
			}
			else if (DeckofcardsIA[i].index == 0 && DeckofcardsIA[i].color == j) {
				hardvalueandcolor[j] = hardvalueandcolor[j] + 1;
			}
		}
	}
	int iMax = 0;
	printf("%d de %s\n", hardvalueandcolor[0], TabColor[0]);
	for (int i = 1; i < numberofcolor; i++) {
		printf("%d de %s\n", hardvalueandcolor[i], TabColor[i]);
		if (hardvalueandcolor[i] > hardvalueandcolor[iMax]) {
			iMax = i;
		}
	}
	printf("ench�re sur %d de %s\n", hardvalueandcolor[iMax], TabColor[iMax]);
	printf("\n");
	if (hardvalueandcolor[iMax] >= 20 && Bestcontractofthepart.valueContract < 120) {
		IAcontract.valueContract = 120;
		IAcontract.colorContract = iMax;
		printf("IA %s announces a CONTRACT of %d points of %s\n", TabName[IAnumber], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
	}
	else if ((13 <= hardvalueandcolor[iMax]) && (hardvalueandcolor[iMax] < 20) && Bestcontractofthepart.valueContract < 80) {
		IAcontract.valueContract = 80;
		IAcontract.colorContract = iMax;
		printf("IA %s announces a CONTRACT of %d points of %s\n", TabName[IAnumber], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
	}
	else if(hardvalueandcolor[iMax] < 13 || Bestcontractofthepart.valueContract >= 120 || hardvalueandcolor[iMax] < 20 && Bestcontractofthepart.valueContract >= 80){
		IAcontract.valueContract = 0;
		IAcontract.colorContract = -1;
		printf(" the IA %s announces that it PASS \n", TabName[IAnumber]);
	}
	printf("\n");
	return IAcontract;
}


//The purpose of this function is to manage the bids at the beginning of the game and to determine an trump based on the winner of the bids.
// It takes in entry the first player who will start bidding and the decks of cards of players. But also the number of each IA.
// It returnes an array of CONTRACT that contain the contract and the color of the contract of each player.
CONTRACT* DetermineTrumpColorAndManageBids(int Firstplayerwhostart, CARD* Deckofcardshuman, CARD* DeckofcardsIA1, CARD* DeckofcardsIA2, CARD* DeckofcardsIA3, int IA1number, int IA2number, int IA3number) {
	CONTRACT max = { 0,-1 };
	CONTRACT* contractplayerandcolortrump = (CONTRACT*)malloc(numberofcardsinthedeck * sizeof(CONTRACT));
	if (Firstplayerwhostart == 0) {
		contractplayerandcolortrump[0] = ContractOfAHuman(Deckofcardshuman, max);
		if (contractplayerandcolortrump[0].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[0];
		contractplayerandcolortrump[1] = ContractOfAnIA(DeckofcardsIA1, IA1number, max);
		if (contractplayerandcolortrump[1].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[1];
		contractplayerandcolortrump[2] = ContractOfAnIA(DeckofcardsIA2, IA2number, max);
		if (contractplayerandcolortrump[2].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[2];
		contractplayerandcolortrump[3] = ContractOfAnIA(DeckofcardsIA3, IA3number, max);
	}
	else if (Firstplayerwhostart == 1) {
		contractplayerandcolortrump[1] = ContractOfAnIA(DeckofcardsIA1, IA1number, max);
		if (contractplayerandcolortrump[1].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[1];
		contractplayerandcolortrump[2] = ContractOfAnIA(DeckofcardsIA2, IA2number, max);
		if (contractplayerandcolortrump[2].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[2];
		contractplayerandcolortrump[3] = ContractOfAnIA(DeckofcardsIA3, IA3number, max);
		if (contractplayerandcolortrump[3].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[3];
		contractplayerandcolortrump[0] = ContractOfAHuman(Deckofcardshuman, max);
	}
	else if (Firstplayerwhostart == 2) {
		contractplayerandcolortrump[2] = ContractOfAnIA(DeckofcardsIA2, IA2number, max);
		if (contractplayerandcolortrump[2].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[2];
		contractplayerandcolortrump[3] = ContractOfAnIA(DeckofcardsIA3, IA3number, max);
		if (contractplayerandcolortrump[3].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[3];
		contractplayerandcolortrump[0] = ContractOfAHuman(Deckofcardshuman, max);
		if (contractplayerandcolortrump[0].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[0];
		contractplayerandcolortrump[1] = ContractOfAnIA(DeckofcardsIA1, IA1number, max);
	}
	else if (Firstplayerwhostart == 3) {
		contractplayerandcolortrump[3] = ContractOfAnIA(DeckofcardsIA3, IA3number, max);
		if (contractplayerandcolortrump[3].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[3];
		contractplayerandcolortrump[0] = ContractOfAHuman(Deckofcardshuman, max);
		if (contractplayerandcolortrump[0].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[0];
		contractplayerandcolortrump[1] = ContractOfAnIA(DeckofcardsIA1, IA1number, max);
		if (contractplayerandcolortrump[1].valueContract >= max.valueContract)
			max = contractplayerandcolortrump[1];
		contractplayerandcolortrump[2] = ContractOfAnIA(DeckofcardsIA2, IA2number, max);
	}
	return contractplayerandcolortrump;
}

void figergrainealeatoire() {
	srand(time(NULL));
}



// This fonction determines the strenght of cards concidering if the card is an atout and the index of the card.
// It takes in entry one card and return the strenght of this card.
// input : Card
// output : Strenght of the card
int GetValueOfACard(CARD Card) {
	if (Card.trump == 0) {
		return Card.index;
	}
	else if (Card.trump == 1) {
		if (Card.index == 2) {
			return 19;
		}
		else if (Card.index == 4) {
			return 20;
		}
		else if (Card.index == 7) {
			return 18;
		}
		else if (Card.index == 3) {
			return 17;
		}
		else {
			return (Card.index + 10);
		}
	}
	return -1;
}



// This function has as goal to choose a random atout.
// It returns the color of the atout for the part.
//int ChooseARandomAtout() {
//	int atoutfortheparty = rand() % 4;
//	printf("The atout that has been choose is %s\n", TabColor[atoutfortheparty]);
//	printf("\n");
//	return atoutfortheparty;
//}





// This function takes two cards as input and returns an equality between the two cards.
// input parameter : Card 1.
// input parameter : Card 2.
// parameter output : Card 1 equal Card 2.
int EqualsCards(CARD c0, CARD c1) {
	return ((c0.index == c1.index) && (c0.color == c1.color));
}

// This function takes a deck of cards as input and returns an initialized deck of cards.
// input parameter : a deck of cards ( in the form of an array)
// input parameter : the size of the array to browse it
// output : Array initialized to -1
void InitializedArray(CARD* Deckofcards, int Sizeofdeckofcards){
	for (int i = 0; i < Sizeofdeckofcards; i++){
		Deckofcards[i].index = -1;
		Deckofcards[i].color = -1;
		Deckofcards[i].trump = -1;
	}
}

// This function takes the IA card game and plays the IA, it returns the card played by the IA.
// input paramater : remaining decks of cards to be played
// input paramater : current turn number (use only for access to the correct portion of the array that implements the deck of cards)
// parmater output : Played Card by IA
// output : Card deck remaining to be played reinitialized so that the played card is removed and the array is consistent in relation to (Currentturnnumber + 1)
CARD PlayIA(CARD* IAcardgame, int Currentturnnumber){
	int i=0;
	int iMax = 0;
	int maxRemainingCardNumber = numberofcardperplayer - Currentturnnumber;
	for (i = 1; i < maxRemainingCardNumber; i++){
		if (GetValueOfACard(IAcardgame[i]) > GetValueOfACard(IAcardgame[iMax])){
			iMax = i;
		}
	}
	printf("The IA chose to play the card %s of %s\n", TabValue[IAcardgame[iMax].index], TabColor[IAcardgame[iMax].color]);
	printf("\n");

	//Find index of card to be removed
	CARD result = IAcardgame[iMax];
	for (int i = iMax; i < maxRemainingCardNumber -1; i++){
		IAcardgame[i] = IAcardgame[i + 1];
	}
	return result;
}




//This function takes as input parameter an array initialized at -1 to fill it with map. The function returns the array of cards, that is the deck of cards
// input paramater : Empty card game  
// output: card game  which is sorted by color and ascending order
void FillAnArrayWithCards(CARD* Emptycardgame){
	int val, coul, i;;
	i = 0;
	for (coul = 0; coul < numberofplayer; coul++){
		for (val = 0; val < numberofcardperplayer; val++){
			Emptycardgame[i].index = val;
			Emptycardgame[i].color = coul;
			printf(" %d -- %s of %s \n", i, TabValue[Emptycardgame[i].index], TabColor[Emptycardgame[i].color]);
			i++;
		}
		printf("\n");
	}
}


// The ShuffleADeckOfCards function takes an incrementally ordered deck of cardsand returns a deck that is a random permutation of the incoming deck.  
// parameter input : a sorted card game
// return : a shuffled card game with random permutation
void ShuffleADeckOfCards(CARD* Sortedcardgame){
	for (int iCarte = (numberofcardsinthedeck - 1); iCarte >= 0; --iCarte){
		int jCarte = rand() % (iCarte + 1);
		CARD temp = Sortedcardgame[iCarte];
		Sortedcardgame[iCarte] = Sortedcardgame[jCarte];
		Sortedcardgame[jCarte] = temp;
	}
}

// This function does'nt takes any parameter input but it allocates a piece of memory to an array. it allocates this memory for an array of arrays (two dimensional array)
// output :  Array of arrays allocated
CARD** AllocateMemoryForAnArrayofArrays() {
	CARD** Twodimensionalarray = malloc(numberofplayer * sizeof(CARD*));
	for (int i = 0; i < numberofplayer; i++) {
		Twodimensionalarray[i] = (CARD*)malloc(numberofcardperplayer * sizeof(CARD));
	}
	return Twodimensionalarray;
}

// The function DistributeADeckOfCardsPerPlayer takes a shuffled deck of cards and an empty per-player card array  and returns the per-player card array filled with the elements of the shuffled deck of cards (games).
// input : a deck of cards which is shuffled
// input : a two dimensional array which is the per-player card array 
// output : an array of arrays fill of shuffled cards -> i.e. cards per player
CARD** DistributeADeckOfCardsPerPlayer(CARD* Shuffleddeckofcards, CARD** Cardsperplayer){
	int i, j, m;
	m = 0;
	for (i = 0; i < numberofplayer; i++){
		for (j = 0; j < numberofcardperplayer; j++){
			Cardsperplayer[i][j] = Shuffleddeckofcards[m];
			printf("Player %d card number %d = %s of %s \n", i, j, TabValue[(Cardsperplayer[i][j]).index], TabColor[(Cardsperplayer[i][j]).color]);
			m++;
		}
		printf("\n");
	}
	return Cardsperplayer;
}

// This function doesn't have a in put parameter but it allocates memory for a deck of cards , fills and shuffles this deck of cards. Secondly it allocates memory for a two dimensional array which is the cards per-player and distribute the cards of the deck between the players
// output : a two dimensional array which correspond to the cards per-player
CARD** DistributingAndShufflingADeckOfCards(){
	CARD* deckofcards = (CARD*)malloc(numberofcardsinthedeck * sizeof(CARD));
	InitializedArray(deckofcards, numberofcardsinthedeck);
	FillAnArrayWithCards(deckofcards);
	ShuffleADeckOfCards(deckofcards);
	CARD** cardsperplayer = AllocateMemoryForAnArrayofArrays();
	DistributeADeckOfCardsPerPlayer(deckofcards, cardsperplayer);
	return cardsperplayer;
}

// This function takes in entry a two dimensional array and tranforms it on a one dimensional array : in order to do so you need the index (which is actually the player's number) of the first dimension of the array which will correspond to the player's cards in the second dimension of the array.
//This function allocates memory to an array and returns the array filled by the cards of one player of the two dimensional array.
// input : a two dimensional array fills by the cards per-player
// input : the player number which corresponds to the index
// output : the cards of one player on an array.
CARD* ChangeFromATwoDimensionalArrayToASingleArray(CARD** Cardsperplayer, int Playernumber){
	CARD* cardsofoneplayer = malloc(numberofcardperplayer * sizeof(CARD));
	InitializedArray(cardsofoneplayer, numberofcardperplayer);
	for (int i = 0; i < numberofcardperplayer; i++){
		cardsofoneplayer[i] = Cardsperplayer[Playernumber][i];
	}
	return cardsofoneplayer;
}

// This function takes a player's deck of cards, the card he has chosen to play during the current turn, and the number of the current turn. 
// It returns the played card and the array that represents the player's deck of cards. This array has been resized taking into account the played card.
// input : The deck of cards of one player
// input : The card which were choose during the turn
// input : the number of the current turn ( this number will be used to resize the array )
// output : the played card by the player
CARD ResizingAnArrayAfterPlayingACard(CARD* Deckofcardsofoneplayer, CARD Chosencardduringthecurrentturn, int Numberofthecurrentturn){
	printf("You play the card that has a value of %s de %s\n", TabValue[Chosencardduringthecurrentturn.index], TabColor[Chosencardduringthecurrentturn.color]);
	printf("\n");
	printf("You now have the following cards left :\n");
	printf("\n");
	for (int i = 0; i < numberofcardperplayer-Numberofthecurrentturn; i++){
		if (Deckofcardsofoneplayer[i].index == Chosencardduringthecurrentturn.index && Deckofcardsofoneplayer[i].color == Chosencardduringthecurrentturn.color){
			while (i < numberofcardperplayer - Numberofthecurrentturn){
				Deckofcardsofoneplayer[i] = Deckofcardsofoneplayer[i + 1];
				i++;
			}
			break;
		}
	}
	for (int i = 0; i < numberofcardperplayer - Numberofthecurrentturn - 1; i++)
		printf(" %d -- %s of %s \n", i, TabValue[Deckofcardsofoneplayer[i].index], TabColor[Deckofcardsofoneplayer[i].color]);
	CARD playedcard = Chosencardduringthecurrentturn;
	return playedcard;
}

// This function takes a player's deck of cards, and the number of the current turn. It asks to the player which card he want to play during the current turn and returns the chosen card.
// input : a player's deck of cards
// input : the number of the current turn ( this number will be used to accesses to the good portion of the array ).
// output : the chosen card by the player
CARD ChooseACardToPlay(CARD* Deckofcardofoneplayer, int Numberofthecurrentturn){
	CARD chosencard = { 0,0 };
	int i = 0;
	printf("Choose the card you want to play by typing the card number:\n");
	printf("\n");
	for (i = 0; i < numberofcardperplayer - Numberofthecurrentturn; i++){
		printf(" %d -- %s of %s\n", i, TabValue[Deckofcardofoneplayer[i].index], TabColor[Deckofcardofoneplayer[i].color]);
	}
	scanf("%d", &i);
	while (i < 0 || i >= numberofcardperplayer - Numberofthecurrentturn){
		printf("This card does not exist, choose another number :\n");
		scanf("%d", &i);
	}
	printf("\n");
	printf("You have chosen the card number %d which has the following value %s of %s\n", i, TabValue[Deckofcardofoneplayer[i].index], TabColor[Deckofcardofoneplayer[i].color]);
	chosencard = Deckofcardofoneplayer[i];
	return chosencard;
}

// This function uses the previous functions ChooseACardToPlay and ResizingAnArrayAfterPlayingACard to choose and play a card.
// input : a deck of cards of one player
// input : the number of the current turn
// output : the played card by to player.
CARD ChooseAndPlayACard(CARD* Deckofcardsofoneplayer, int Numberofthecurrentturn){
	CARD chosencard = { 0,0 };
	CARD playedcard;
	chosencard = ChooseACardToPlay(Deckofcardsofoneplayer, Numberofthecurrentturn);
	playedcard = ResizingAnArrayAfterPlayingACard(Deckofcardsofoneplayer, chosencard, Numberofthecurrentturn);
	return playedcard;
}

// This function allows to determine if the player is human or not but I don't use it anymore
//const char* TesterTypeJoueur(){
//	const char* typedujoueur;
//	int reponse;
//	printf("Es-tu un humain ? (1 pour oui 0 pour non)\n");
//	scanf("%d", &reponse);
//	if (reponse == 1){
//		typedujoueur = typejoueur1;
//	}
//	else{
//		typedujoueur = typejoueur2;
//	}
//	printf("Vous etes donc du type %s\n", typedujoueur);
//	return typedujoueur;
//}

// This fonction takes a played card by a player, an array that references the played cards during the turn in order of the players, the number of played card during this turn.
// This function allows  to add to the referencing array the played card of a player during the current turn. This array will then be used in the program to determine the winner.
// input : A referencing array of played cards of the current turn
// input : the played card
// input : the number of played card during the current turn 
void AddPlayedCardToReferencingArray(CARD Playedcard, CARD* Referencingarrayofplayedcardofturn, int Numberoftheplayer){
	Referencingarrayofplayedcardofturn[Numberoftheplayer].index = Playedcard.index;
	Referencingarrayofplayedcardofturn[Numberoftheplayer].color = Playedcard.color;
	Referencingarrayofplayedcardofturn[Numberoftheplayer].trump = Playedcard.trump;

}





// This function has as goal to determined a winner between the player.
// It takes in entry a referencing array of played cards during the turn, the number of played card to browse the array of referencing, and a players score counter (in the form of an array).
// input : a referencing array of played cards
// input : number of played cards during the turn
// input : a player score counter
// output : a boolean which corresponds to the existence of a winner or not
int DeterminingAWinnerAmongThePlayers(CARD* Referencingarrayofplayedcards, int* Playerscorecounter){
	int i;
	CARD max = Referencingarrayofplayedcards[0];
	int winningplayernumber = -1;
	int winnerspoints = Referencingarrayofplayedcards[0].index;
	for (i = 0; i < numberofplayer; i++){
		winnerspoints += Referencingarrayofplayedcards[i].index;
		if (GetValueOfACard(Referencingarrayofplayedcards[i]) > GetValueOfACard(max)){
			max=Referencingarrayofplayedcards[i];
			winningplayernumber = i;
		}
		else if (GetValueOfACard(Referencingarrayofplayedcards[i]) == GetValueOfACard(max)) {
			winningplayernumber = -1;
		}
	}

	if (winningplayernumber != -1) {
		Playerscorecounter[winningplayernumber] = Playerscorecounter[winningplayernumber] + winnerspoints;
		printf("Player %d, wins. His score is increased by %d, and reaches %d.\n", winningplayernumber, winnerspoints, Playerscorecounter[winningplayernumber]);
		printf("\n");
	}
	else {
		printf("At least 2 players are tied, The sum of the lost points is %d.\n", winnerspoints);
		printf("\n");
	}
	return (winningplayernumber != -1);
}


// This function takes the deck of cards of the human, the referencing array of the played cards during the turn, the number of played cards during the turn, and the number of the current turn.
// This function has as goal to do play the human player.
// input : deck of cards of human
// input : referencing array of the played cards
// input : number of played cards
// input : player score counter
void PlayAHumanPlayer(CARD* Deckofcardsofhuman, CARD* Referencingarrayoftheplayedcards, int Numberoftheplayer, int Numberofcurrentturn){
	CARD playedcard = { 0,0 };
	playedcard = ChooseAndPlayACard(Deckofcardsofhuman, Numberofcurrentturn);
	AddPlayedCardToReferencingArray(playedcard, Referencingarrayoftheplayedcards, Numberoftheplayer);
	
}

// This function takes the deck of cards of one IA, the referencing array of the played cards during the turn, the number of played cards during the turn, and the number of the current turn.
// This function has as goal to do play an IA player.
// input : deck of cards of one IA
// input : referencing array of the played cards
// input : number of played cards
// input : player score counter
void PlayAnIAPlayer(CARD* DeckofcardsofoneIA, CARD* Referencingarrayoftheplayedcards,  int Numberoftheplayer, int Numberofcurrentturn){
	CARD playedcard = { -1,-1 };
	playedcard = PlayIA(DeckofcardsofoneIA, Numberofcurrentturn);
	AddPlayedCardToReferencingArray(playedcard, Referencingarrayoftheplayedcards, Numberoftheplayer);
}

// This function has as goal to play a turn. It means that the role of this function is to make the human and the three AIs play in a successive way.
// This function allocates memory for the referencing array of the played cards.
// input : deck of cards of the human, the first IA, the second IA, and the third IA.
// input : players score counter
// input : the number of the current turn
void PlayOneTurn(CARD* Humandeck, CARD* IA1deck, CARD* IA2deck, CARD* IA3deck, int* Playerscorecounter, int Numberofthecurrentturn, int Firstplayernumber){
	int winneroftheturn = 0;
	CARD* referencingarrayoftheplayedcards = malloc(sizeofreferencingarray * sizeof(CARD));
	InitializedArray(referencingarrayoftheplayedcards, sizeofreferencingarray);
	int numberofeachplayer[4] = { 0,1,2,3 };
	for (int iPlayer = 0; iPlayer < numberofplayer; iPlayer++) {
		int numPlayer = (Firstplayernumber + iPlayer) % numberofplayer;
		if (numPlayer == 0) {
			PlayAHumanPlayer(Humandeck, referencingarrayoftheplayedcards, numberofeachplayer[0], Numberofthecurrentturn);
		}
		else {
			switch (numPlayer) {
			 case 1:
				 PlayAnIAPlayer(IA1deck, referencingarrayoftheplayedcards, numberofeachplayer[1], Numberofthecurrentturn);
				 break;
			 case 2:
				 PlayAnIAPlayer(IA2deck, referencingarrayoftheplayedcards, numberofeachplayer[2], Numberofthecurrentturn);
				 break;
			 case 3:
				 PlayAnIAPlayer(IA3deck, referencingarrayoftheplayedcards, numberofeachplayer[3], Numberofthecurrentturn);
				 break;
			}
		}		
		printf("\n");
	}
	winneroftheturn = DeterminingAWinnerAmongThePlayers(referencingarrayoftheplayedcards, Playerscorecounter);
}

// The purpose of this function is to play a party, i.e. to play several turns (as many as there are cards in the player's hands).
// There is no input parameters but the function dynamically allocates a  piece of memory to deck of cards of the human and IAs
// The function displays the winner of this party.
void PlayOnePart(){
	int playerscorecounter[4] = { 0 };
	CARD** deckofcardsperplayer;
	deckofcardsperplayer = DistributingAndShufflingADeckOfCards();
	CARD* humancards = malloc(numberofcardperplayer * sizeof(CARD*));
	CARD* IA1cards = malloc(numberofcardperplayer * sizeof(CARD*));
	CARD* IA2cards = malloc(numberofcardperplayer * sizeof(CARD*));
	CARD* IA3cards = malloc(numberofcardperplayer * sizeof(CARD*));
	int humanplayernumber = 0;
	int IA1playernumber = 1;
	int IA2playernumber = 2;
	int IA3playernumber = 3;
	humancards = ChangeFromATwoDimensionalArrayToASingleArray(deckofcardsperplayer, humanplayernumber);
	IA1cards = ChangeFromATwoDimensionalArrayToASingleArray(deckofcardsperplayer, IA1playernumber);
	IA2cards = ChangeFromATwoDimensionalArrayToASingleArray(deckofcardsperplayer, IA2playernumber);
	IA3cards = ChangeFromATwoDimensionalArrayToASingleArray(deckofcardsperplayer, IA3playernumber);
	int firstplayerwhobidding = 0;
	firstplayerwhobidding = ChooseRandomlyAPlayerWhoWillStartBidding();
	CONTRACT* contractplayer;
	contractplayer = DetermineTrumpColorAndManageBids(firstplayerwhobidding, humancards, IA1cards, IA2cards, IA3cards, IA1playernumber, IA2playernumber, IA3playernumber);
	int iMax = 0;
	printf("%d de %s\n", contractplayer[0].valueContract, TabColor[contractplayer[0].colorContract]);
	for (int i = 1; i < numberofplayer; i++) {
		printf("%d de %s\n", contractplayer[i].valueContract, TabColor[contractplayer[i].colorContract]);
		if (contractplayer[i].valueContract > contractplayer[iMax].valueContract) {
			iMax = i;
		}
	}
	int playerwhobiginsthepart = iMax;
	int trumpforthepart = contractplayer[iMax].colorContract;
	FillTheTrumpPartOfTheStructCard(humancards, trumpforthepart);
	FillTheTrumpPartOfTheStructCard(IA1cards, trumpforthepart);
	FillTheTrumpPartOfTheStructCard(IA2cards, trumpforthepart);
	FillTheTrumpPartOfTheStructCard(IA3cards, trumpforthepart);
	int numberofthecurrentturn = 0;
	for (int i = 0; i < numberofcardperplayer; i++){
		PlayOneTurn(humancards, IA1cards, IA2cards, IA3cards, playerscorecounter, numberofthecurrentturn, playerwhobiginsthepart);
		numberofthecurrentturn++;
	}
}




int main(){
	figergrainealeatoire();
#if defined(_WIN32) || defined(__MSDOS__)
	SetConsoleOutputCP(65001);
#endif
	PlayOnePart();
}
