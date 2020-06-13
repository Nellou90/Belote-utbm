#ifndef GAME_OPERATIONS
#define GAME_OPERATIONS

#include "Defs.h"
#include "CardDeckOperations.h"
#include "HumanPlayer.h"
#include "IAPlayer.h"
#include "SerializeScores.h"
#include "GameOperations.h"

void FillName(char* Playername);
int ChooseRandomlyAPlayerWhoWillStartBidding();
CONTRACT* DetermineTrumpColorAndManageBids(int Firstplayerwhostart, CARD* Deckofcardshuman, CARD* DeckofcardsIA1, CARD* DeckofcardsIA2, CARD* DeckofcardsIA3, int IA1number, int IA2number, int IA3number);
int DetermineTheWinnerTeam(int* Playerscorecounter, CONTRACT Contract, int Contractteam, int* scoreteam);
int DeterminingAWinnerAmongThePlayers(CARD* Referencingarrayofplayedcards, int* Playerscorecounter, int FirstPlayer, int Numberofcurrentturn);
int PlayOneRound(CARD* Humandeck, CARD* IA1deck, CARD* IA2deck, CARD* IA3deck, int* Playerscorecounter, int Numberofthecurrentturn, int Firstplayernumber, int Trumpofthegame);
void PlayOneGame();
void FreeAllocString(char* Stringofcharactere);
void FixTheRandomSeed();
#endif