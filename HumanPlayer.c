#include "Defs.h"
#include "HumanPlayer.h"

// This fonction has as goal to ask to human player how many point he projects to do during the part of the games.
// The function has in entry the deck of cards of the human and return the contract of the human.
// input : deck of cards of the human 
// input : Asset
// output : Human contract
CONTRACT ContractOfAHuman(CARD* Deckofcardshuman, CONTRACT Bestcontractofthegame) {
	CONTRACT humancontract;
	int answer;
	int answer2;
	printf("\n");
	printf("Here are your cards : \n");
	printf("\n");
	for (int i = 0; i < numberofcardperplayer; i++) {
		printf("| %s%s |   ", TabCardName[Deckofcardshuman[i].index], TabColor[Deckofcardshuman[i].color]);
	}
	printf("\n");
	printf("\n");
	printf("		     You have two choice : \n");
	printf("\n");
	printf("PASS : 0						CONTRACT : 1\n");
	printf("\n");
	scanf("%d", &answer);
	while (answer != 1 && answer != 0) {
		printf("Error, try again : \n");
		printf("\n");
		scanf("%d", &answer);
	}
	if (answer == 0) {
		humancontract.valueContract = 0;
		humancontract.colorContract = -1;

	}
	else if (answer == 1) {
		printf("		Choose the color of your contract : \n");
		printf("\n");
		printf("\n");
		printf("%s : 0			%s : 1			%s : 2			%s : 3	", TabColor[0], TabColor[1], TabColor[2], TabColor[3]);
		printf("\n");
		scanf("%d", &(humancontract.colorContract));
		while ((humancontract.colorContract) < 0 || (humancontract.colorContract) > 3) {
			printf("Error, try again :\n");
			printf("\n");
			scanf("%d", &(humancontract.colorContract));
		}
		printf("Choose your contract between 80 and 160 : \n");
		printf("\n");
		scanf("%d", &(humancontract.valueContract));
		while (humancontract.valueContract < 80 || humancontract.valueContract > 160 || humancontract.valueContract <= Bestcontractofthegame.valueContract) {
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
	return humancontract;
}

// This function takes a player's deck of cards, and the number of the current turn. It asks to the player which card he want to play during the current turn and returns the chosen card.
// input : a player's deck of cards
// input : the number of the current turn ( this number will be used to accesses to the good portion of the array ).
// output : the chosen card by the player
CARD ChooseACardToPlay(CARD* Deckofcardofoneplayer, int Numberofthecurrentturn, int Firstplayer, CARD* Referencingarrayofplayedcard, int Humannumber) {
	int temp = 0;
	CARD chosencard = { 0,0 };
	int i = 0;
	int askedcolor = Referencingarrayofplayedcard[Firstplayer].color;
	if (Firstplayer == Humannumber) {
		printf("\n");
		printf("Choose the card you want to play by typing the card number:\n");
		printf("\n");
		printf("\n");
		for (i = 0; i < numberofcardperplayer - Numberofthecurrentturn; i++) {
			printf(" %d : | %s%s |   ", i, TabCardName[Deckofcardofoneplayer[i].index], TabColor[Deckofcardofoneplayer[i].color]);

		}
		printf("\n");
		scanf("%d", &i);
		while (i < 0 || i >= numberofcardperplayer - Numberofthecurrentturn) {
			printf("This card does not exist, choose another number :\n");
			scanf("%d", &i);
		}
		printf("You play the card : | %s%s |\n", TabCardName[Deckofcardofoneplayer[i].index], TabColor[Deckofcardofoneplayer[i].color]);
		printf("\n");
		chosencard = Deckofcardofoneplayer[i];
	}
	else {
		printf("Choose the card you want to play by typing the card number:\n");
		printf("\n");
		printf("\n");
		for (i = 0; i < numberofcardperplayer - Numberofthecurrentturn; i++) {
			printf(" %d : | %s%s |   ", i, TabCardName[Deckofcardofoneplayer[i].index], TabColor[Deckofcardofoneplayer[i].color]);
			if (Deckofcardofoneplayer[i].color == Referencingarrayofplayedcard[Firstplayer].color) {
				temp++;
			}

		}
		printf("\n");
		scanf("%d", &i);
		while (Deckofcardofoneplayer[i].color != askedcolor && temp > 0) {
			printf("If you have a card of the color %s, you have to play this card !\n", TabColor[Referencingarrayofplayedcard[Firstplayer].color]);
			scanf("%d", &i);
		}
		while (i < 0 || i >= numberofcardperplayer - Numberofthecurrentturn) {
			printf("This card does not exist, choose another number :\n");
			scanf("%d", &i);
			printf("\n");
		}
		printf("\n");
		chosencard = Deckofcardofoneplayer[i];
	}
	return chosencard;
}

// This function uses the previous functions ChooseACardToPlay and ResizingAnArrayAfterPlayingACard to choose and play a card.
// input : a deck of cards of one player
// input : the number of the current turn
// output : the played card by to player.
CARD ChooseAndPlayACard(CARD* Deckofcardsofoneplayer, int Numberofthecurrentturn, int Firstplayer, CARD* Referencingarrayofplayedcard, int Humannumber) {
	CARD chosencard = { 0,0 };
	CARD playedcard;
	chosencard = ChooseACardToPlay(Deckofcardsofoneplayer, Numberofthecurrentturn, Firstplayer, Referencingarrayofplayedcard, Humannumber);
	playedcard = ResizingAnArrayAfterPlayingACard(Deckofcardsofoneplayer, chosencard, Numberofthecurrentturn);
	return playedcard;
}

// This function takes the deck of cards of the human, the referencing array of the played cards during the turn, the number of played cards during the turn, and the number of the current turn.
// This function has as goal to do play the human player.
// input : deck of cards of human
// input : referencing array of the played cards
// input : number of played cards
// input : player score counter
void PlayAHumanPlayer(CARD* Deckofcardsofhuman, CARD* Referencingarrayoftheplayedcards, int Numberoftheplayer, int Numberofcurrentturn, int Firstplayer) {
	CARD playedcard = { 0,0 };
	playedcard = ChooseAndPlayACard(Deckofcardsofhuman, Numberofcurrentturn, Firstplayer, Referencingarrayoftheplayedcards, Numberoftheplayer);
	AddPlayedCardToReferencingArray(playedcard, Referencingarrayoftheplayedcards, Numberoftheplayer);

}