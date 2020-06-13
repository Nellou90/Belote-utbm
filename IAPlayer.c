#include "Defs.h"
#include "IAPlayer.h"

// This fonction has as goal to ask to IA player how many point it projects to do during the part of the games.
// The function has in entry the deck of cards of the IA, the Asset, the number of the IA and return the contract of the IA.
// input : deck of cards of the IA 
// input : Asset
// input : the number of the IA
// output : IA contract
CONTRACT ContractOfAnIA(CARD* DeckofcardsIA, int IAnumber, CONTRACT Bestcontractofthegame) {
	CONTRACT IAcontract = { -1,-1 };
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
	for (int i = 1; i < numberofcolor; i++) {
		if (hardvalueandcolor[i] > hardvalueandcolor[iMax]) {
			iMax = i;
		}
	}
	printf("\n");
	if (hardvalueandcolor[iMax] >= 20 && Bestcontractofthegame.valueContract < 120) {
		IAcontract.valueContract = 120;
		IAcontract.colorContract = iMax;
		if (IAnumber == 2) {
			printf("IA %s %s  announces the CONTRACT :  %d points %s\n", TabName[IAnumber], TabTeamNameAscii[0], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
			printf("\n");
		}
		else {
			printf("IA %s %s  announces the CONTRACT :  %d points %s\n", TabName[IAnumber], TabTeamNameAscii[1], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
			printf("\n");
		}
	}
	else if ((13 <= hardvalueandcolor[iMax]) && (hardvalueandcolor[iMax] < 20) && Bestcontractofthegame.valueContract < 80) {
		IAcontract.valueContract = 80;
		IAcontract.colorContract = iMax;
		if (IAnumber == 2) {
			printf("IA %s %s  announces the CONTRACT :  %d points %s\n", TabName[IAnumber], TabTeamNameAscii[0], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
			printf("\n");
		}
		else {
			printf("IA %s %s  announces the CONTRACT :  %d points %s\n", TabName[IAnumber], TabTeamNameAscii[1], IAcontract.valueContract, TabColor[IAcontract.colorContract]);
			printf("\n");
		}
	}
	else if (hardvalueandcolor[iMax] < 13 || Bestcontractofthegame.valueContract >= 120 || hardvalueandcolor[iMax] < 20 && Bestcontractofthegame.valueContract >= 80) {
		IAcontract.valueContract = 0;
		IAcontract.colorContract = -1;
		if (IAnumber == 2) {
			printf("IA %s %s  announces that it PASS \n", TabName[IAnumber], TabTeamNameAscii[0]);
			printf("\n");
		}
		else {
			printf("IA %s %s  announces that it PASS \n", TabName[IAnumber], TabTeamNameAscii[1]);
			printf("\n");
		}
	}
	return IAcontract;
}

// This function takes the IA card game and plays the IA, it returns the card played by the IA.
// input paramater : remaining decks of cards to be played
// input paramater : current turn number (use only for access to the correct portion of the array that implements the deck of cards)
// parmater output : Played Card by IA
// output : Card deck remaining to be played reinitialized so that the played card is removed and the array is consistent in relation to (Currentturnnumber + 1)
CARD PlayIA(CARD* IAcardgame, int Currentturnnumber, CARD* Referencingarrayofplayedcards, int Firstplayer, int NumberofIA) {
	int i = 0;
	int iMax = 0;
	int j = 0;
	int maxRemainingCardNumber = numberofcardperplayer - Currentturnnumber;
	CARD result = { -1,-1,-1 };
	int colorofthecurrentturn = -1;
	int trumpcolor = DetermineIfTheresAnAssetAndReturnTheColor(IAcardgame, maxRemainingCardNumber);
	CARD bestcardplayedatthistime = { -1,-1,-1 };
	int jBest = 0;
	for (i = 1; i < maxRemainingCardNumber; i++) {
		if (GetValueOfACard(IAcardgame[i]) > GetValueOfACard(IAcardgame[iMax])) {
			iMax = i;
		}
	}
	// First part of tne condition : If the IA is the first player to play, it plays its best card, trump or no trump.
	if (Firstplayer == NumberofIA) {
		result = IAcardgame[iMax];
		if (NumberofIA == 2) {
			printf("The IA %s %s  playes the CARD :	 | %s%s |\n", TabName[NumberofIA], TabTeamNameAscii[0], TabCardName[result.index], TabColor[result.color]);
			printf("\n");
		}
		else {
			printf("The IA %s %s  playes the CARD :	 | %s%s |\n", TabName[NumberofIA], TabTeamNameAscii[1], TabCardName[result.index], TabColor[result.color]);
			printf("\n");
		}

		//Find index of card to be removed
		for (int i = iMax; i < maxRemainingCardNumber - 1; i++) {
			IAcardgame[i] = IAcardgame[i + 1];
		}
	}
	// Second part of the condition : else the IA has to play a card of the first color play to respect the rules of the Belote
	else {
		colorofthecurrentturn = Referencingarrayofplayedcards[Firstplayer].color;
		// Determine the best played card until now
		for (j = 1; j < numberofplayer; j++) {
			if (GetValueOfACard(Referencingarrayofplayedcards[j]) > GetValueOfACard(Referencingarrayofplayedcards[jBest])) {
				jBest = j;
			}
		}
		bestcardplayedatthistime = Referencingarrayofplayedcards[jBest];
		// If the best played card until now is of the asked color, the IA has two choice.
		if (bestcardplayedatthistime.color == colorofthecurrentturn) {
			//1
			CARD IAhasaskedcolor = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, colorofthecurrentturn, -1);
			// First choice : the IA has the asked color: if it can wins, it playes the smallest card which allows it to win.
			if (IAhasaskedcolor.index != -1) {
				//3
				result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, colorofthecurrentturn, GetValueOfACard(bestcardplayedatthistime));
				//else if it can't wins, it playes the smallest card of the asked color.
				if (result.index == -1) {
					result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, colorofthecurrentturn, -1);
				}
			}
			else {
				//4
				// If the IA has a trump, IA plays the smallest card with asset color *****************************
				if (trumpcolor != -1) {
					//5
					result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, trumpcolor, GetValueOfACard(bestcardplayedatthistime));
					if (result.index == -1) {
						result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, trumpcolor, -1);
					}

				}
				else {
					//6
					result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, -1, -1);
				}
			}
		}
		else {
			//2
			CARD iaHasAskedColor = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, colorofthecurrentturn, -1);
			if (iaHasAskedColor.index != -1) {
				//7
				result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, colorofthecurrentturn, -1);
			}
			else {
				//8
				int bestcardtrump = 0;
				result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, trumpcolor, bestcardtrump);
				if (result.index == -1) {
					result = DetermineTheSmallestCardOfAColor(IAcardgame, maxRemainingCardNumber, trumpcolor, -1);
				}

			}
		}

		int iResult = 0;
		for (int m = 0; m < maxRemainingCardNumber; m++) {
			if ((IAcardgame[m].color == result.color) && (IAcardgame[m].index == result.index)) {
				iResult = m;
				break;
			}
		}
		if (NumberofIA == 2) {
			printf("The IA %s %s  playes the CARD :	 | %s%s |\n", TabName[NumberofIA], TabTeamNameAscii[0], TabCardName[IAcardgame[iResult].index], TabColor[IAcardgame[iResult].color]);
			printf("\n");
		}
		else if (NumberofIA == 1 || NumberofIA == 3) {
			printf("The IA %s %s  playes the CARD :	 | %s%s |\n", TabName[NumberofIA], TabTeamNameAscii[1], TabCardName[IAcardgame[iResult].index], TabColor[IAcardgame[iResult].color]);
			printf("\n");
		}

		//Find index of card to be removed
		for (int i = iResult; i < maxRemainingCardNumber - 1; i++) {
			IAcardgame[i] = IAcardgame[i + 1];
		}
	}
	return result;
}

// This function takes the deck of cards of one IA, the referencing array of the played cards during the turn, the number of played cards during the turn, and the number of the current turn.
// This function has as goal to do play an IA player.
// input : deck of cards of one IA
// input : referencing array of the played cards
// input : number of played cards
// input : player score counter
void PlayAnIAPlayer(CARD* DeckofcardsofoneIA, CARD* Referencingarrayoftheplayedcards, int Numberoftheplayer, int Numberofcurrentturn, int Firstplayeroftheround) {
	CARD playedcard = { -1,-1 };
	playedcard = PlayIA(DeckofcardsofoneIA, Numberofcurrentturn, Referencingarrayoftheplayedcards, Firstplayeroftheround, Numberoftheplayer);
	AddPlayedCardToReferencingArray(playedcard, Referencingarrayoftheplayedcards, Numberoftheplayer);
}

