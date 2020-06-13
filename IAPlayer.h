#ifndef IA_PLAYER
#define IA_PLAYER

#include "Defs.h"
#include "CardDeckOperations.h"
#include "HumanPlayer.h"
#include "IAPlayer.h"
#include "SerializeScores.h"
#include "GameOperations.h"

CONTRACT ContractOfAnIA(CARD* DeckofcardsIA, int IAnumber, CONTRACT Bestcontractofthegame);
CARD PlayIA(CARD* IAcardgame, int Currentturnnumber, CARD* Referencingarrayofplayedcards, int Firstplayer, int NumberofIA);
void PlayAnIAPlayer(CARD* DeckofcardsofoneIA, CARD* Referencingarrayoftheplayedcards, int Numberoftheplayer, int Numberofcurrentturn, int Firstplayeroftheround);

#endif