#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Defs.h"
#include "CardDeckOperations.h"
#include "HumanPlayer.h"
#include "IAPlayer.h"
#include "SerializeScores.h"
#include "GameOperations.h"

CONTRACT ContractOfAHuman(CARD* Deckofcardshuman, CONTRACT Bestcontractofthegame);
CARD ChooseACardToPlay(CARD* Deckofcardofoneplayer, int Numberofthecurrentturn, int Firstplayer, CARD* Referencingarrayofplayedcard, int Humannumber);
CARD ChooseAndPlayACard(CARD* Deckofcardsofoneplayer, int Numberofthecurrentturn, int Firstplayer, CARD* Referencingarrayofplayedcard, int Humannumber);
void PlayAHumanPlayer(CARD* Deckofcardsofhuman, CARD* Referencingarrayoftheplayedcards, int Numberoftheplayer, int Numberofcurrentturn, int Firstplayer);

#endif