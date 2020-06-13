#include "Defs.h"
#include "CardDeckOperations.h"

// This function allows for each card of a player's game to say if it is a trump: 1 yes, 0 no.
// It takes in entry the deck of cards of a player and the trump of the part.
// It returns the deck of cards of a player with the trump part in the struct CARD filled.
void FillTheTrumpGameOfTheStructCard(CARD* Deckofcardsplayer, int Trump) {
	for (int i = 0; i < numberofcardperplayer; i++) {
		if (Deckofcardsplayer[i].color == Trump) {
			Deckofcardsplayer[i].trump = 1;
		}
		else {
			Deckofcardsplayer[i].trump = 0;
		}
	}
}

// This fonction determines the strenght of cards concidering if the card is an atout and the index of the card.
// It takes in entry one card and return the strenght of this card.
// input : Card
// output : Strenght of the card
int GetValueOfACard(CARD Card) {
	if (Card.trump == 0) {
		return TabValues[Card.index];
	}
	else if (Card.trump == 1) {
		if (Card.index == 2) {
			return 24;
		}
		else if (Card.index == 4) {
			return 30;
		}
		else if (Card.index == 7) {
			return 21;
		}
		else if (Card.index == 3) {
			return 20;
		}
		else {
			return (TabValues[Card.index] + 10);
		}
	}
	return -1;
}

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
void InitializedArray(CARD* Deckofcards, int Sizeofdeckofcards) {
	for (int i = 0; i < Sizeofdeckofcards; i++) {
		Deckofcards[i].index = -1;
		Deckofcards[i].color = -1;
		Deckofcards[i].trump = -1;
	}
}

// This function has as goal to determine the smallest card in deck in relation to a color that is above a given value threshold
// It takes in entry the deck of cards of a player, the number of remaining card, the color which will serves to determine the minimum.
// Ti returns the smallest card in the deck in function of the color.
CARD DetermineTheSmallestCardOfAColor(CARD* Deckofcardsofaplayer, int Numberofremainingcard, int Askedcolor, int Valuethreshold) {
	CARD thesmallestcard = { -1,-1,-1 };
	int iSmallest = -1;
	for (int i = 0; i < Numberofremainingcard; i++) {
		if (
			((Deckofcardsofaplayer[i].color == Askedcolor) || (Askedcolor == -1))
			&& ((iSmallest == -1) || (GetValueOfACard(Deckofcardsofaplayer[i]) < GetValueOfACard(Deckofcardsofaplayer[iSmallest])))
			&& (GetValueOfACard(Deckofcardsofaplayer[i]) > Valuethreshold)) {
			iSmallest = i;
		}
	}
	if (iSmallest == -1) {
		thesmallestcard.index = -1;
		thesmallestcard.color = -1;
		thesmallestcard.trump = -1;

	}
	else {
		thesmallestcard = Deckofcardsofaplayer[iSmallest];
	}
	return thesmallestcard;
}

int DetermineIfTheresAnAssetAndReturnTheColor(CARD* Deckofcardsofaplayer, int Numberofremainingcard) {
	for (int i = 0; i < Numberofremainingcard; i++) {
		if (Deckofcardsofaplayer[i].trump == 1) {
			return Deckofcardsofaplayer[i].color;
		}
	}
	return -1;
}

//This function takes as input parameter an array initialized at -1 to fill it with map. The function returns the array of cards, that is the deck of cards
// input paramater : Empty card game  
// output: card game  which is sorted by color and ascending order
void FillAnArrayWithCards(CARD* Emptycardgame) {
	int val, coul, i;;
	i = 0;
	for (coul = 0; coul < numberofplayer; coul++) {
		for (val = 0; val < numberofcardperplayer; val++) {
			Emptycardgame[i].index = val;
			Emptycardgame[i].color = coul;
			i++;
		}
	}
}


// The ShuffleADeckOfCards function takes an incrementally ordered deck of cardsand returns a deck that is a random permutation of the incoming deck.  
// parameter input : a sorted card game
// return : a shuffled card game with random permutation
void ShuffleADeckOfCards(CARD* Sortedcardgame) {
	for (int iCarte = (numberofcardsinthedeck - 1); iCarte >= 0; --iCarte) {
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
CARD** DistributeADeckOfCardsPerPlayer(CARD* Shuffleddeckofcards, CARD** Cardsperplayer) {
	int i, j, m;
	m = 0;
	for (i = 0; i < numberofplayer; i++) {
		for (j = 0; j < numberofcardperplayer; j++) {
			Cardsperplayer[i][j] = Shuffleddeckofcards[m];
			printf("joueur %d : %s de %s\n", i, TabCardName[Shuffleddeckofcards[m].index], TabColor[Shuffleddeckofcards[m].color]);
			m++;
		}
		printf("\n");
	}
	return Cardsperplayer;
}

// This function doesn't have a in put parameter but it allocates memory for a deck of cards , fills and shuffles this deck of cards. Secondly it allocates memory for a two dimensional array which is the cards per-player and distribute the cards of the deck between the players
// output : a two dimensional array which correspond to the cards per-player
CARD** DistributingAndShufflingADeckOfCards() {
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
CARD* ChangeFromATwoDimensionalArrayToASingleArray(CARD** Cardsperplayer, int Playernumber) {
	CARD* cardsofoneplayer = malloc(numberofcardperplayer * sizeof(CARD));
	InitializedArray(cardsofoneplayer, numberofcardperplayer);
	for (int i = 0; i < numberofcardperplayer; i++) {
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
CARD ResizingAnArrayAfterPlayingACard(CARD* Deckofcardsofoneplayer, CARD Chosencardduringthecurrentturn, int Numberofthecurrentturn) {
	for (int i = 0; i < numberofcardperplayer - Numberofthecurrentturn; i++) {
		if (Deckofcardsofoneplayer[i].index == Chosencardduringthecurrentturn.index && Deckofcardsofoneplayer[i].color == Chosencardduringthecurrentturn.color) {
			while (i < numberofcardperplayer - Numberofthecurrentturn) {
				Deckofcardsofoneplayer[i] = Deckofcardsofoneplayer[i + 1];
				i++;
			}
			break;
		}
	}
	CARD playedcard = Chosencardduringthecurrentturn;
	return playedcard;
}

// This fonction takes a played card by a player, an array that references the played cards during the turn in order of the players, the number of played card during this turn.
// This function allows  to add to the referencing array the played card of a player during the current turn. This array will then be used in the program to determine the winner.
// input : A referencing array of played cards of the current turn
// input : the played card
// input : the number of played card during the current turn 
void AddPlayedCardToReferencingArray(CARD Playedcard, CARD* Referencingarrayofplayedcardofturn, int Numberoftheplayer) {
	Referencingarrayofplayedcardofturn[Numberoftheplayer].index = Playedcard.index;
	Referencingarrayofplayedcardofturn[Numberoftheplayer].color = Playedcard.color;
	Referencingarrayofplayedcardofturn[Numberoftheplayer].trump = Playedcard.trump;

}

// This function has as goal to determine the points of a card
int GetPointOfACard(CARD Card) {
	if (Card.trump == 1) {
		return PointTrump[Card.index];
	}
	else if (Card.trump == 0) {
		return PointNormal[Card.index];
	}
	return -1;
}
