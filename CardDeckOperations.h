#ifndef CARD_DECK_OPERATIONS
#define CARD_DECK_OPERATIONS

#include "Defs.h"
#include "CardDeckOperations.h"
#include "HumanPlayer.h"
#include "IAPlayer.h"
#include "SerializeScores.h"
#include "GameOperations.h"

void FillTheTrumpGameOfTheStructCard(CARD* Deckofcardsplayer, int Trump);
int GetValueOfACard(CARD Card);
int EqualsCards(CARD c0, CARD c1);
void InitializedArray(CARD* Deckofcards, int Sizeofdeckofcards);
CARD DetermineTheSmallestCardOfAColor(CARD* Deckofcardsofaplayer, int Numberofremainingcard, int Askedcolor, int Valuethreshold);
int DetermineIfTheresAnAssetAndReturnTheColor(CARD* Deckofcardsofaplayer, int Numberofremainingcard);
void FillAnArrayWithCards(CARD* Emptycardgame);
void ShuffleADeckOfCards(CARD* Sortedcardgame);
CARD** AllocateMemoryForAnArrayofArrays();
CARD** DistributeADeckOfCardsPerPlayer(CARD* Shuffleddeckofcards, CARD** Cardsperplayer);
CARD** DistributingAndShufflingADeckOfCards();
CARD* ChangeFromATwoDimensionalArrayToASingleArray(CARD** Cardsperplayer, int Playernumber);
CARD ResizingAnArrayAfterPlayingACard(CARD* Deckofcardsofoneplayer, CARD Chosencardduringthecurrentturn, int Numberofthecurrentturn);
void AddPlayedCardToReferencingArray(CARD Playedcard, CARD* Referencingarrayofplayedcardofturn, int Numberoftheplayer);
int GetPointOfACard(CARD Card);
#endif