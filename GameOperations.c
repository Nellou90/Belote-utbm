#include "Defs.h"
#include "GameOperations.h"

// This is the constant name of players
char** TabName=NULL;

void FreeAllocString(char* Stringofcharactere) {
	free(Stringofcharactere);
}

void FixTheRandomSeed() {
	srand((unsigned int)time(NULL));
}

void FillName(char* Playername) {
	TabName = malloc(sizeof(char*) * 4);
	TabName[0] = malloc(strlen(Playername) + 1);
	sprintf(TabName[0], "%s", Playername);
	TabName[1] = (char*)tabNomIA[0];
	TabName[2] = (char*)tabNomIA[1];
	TabName[3] = (char*)tabNomIA[2];
}

// The purpose of this function is to randomly draw the player who will start bidding.
// It hasn't parameter input but it returns the player who will start bidding.
// output : Player who will start bidding;
int ChooseRandomlyAPlayerWhoWillStartBidding() {
	int playerwhowillstartbidding = rand() % 4;
	return playerwhowillstartbidding;
}

//The purpose of this function is to manage the bids at the beginning of the game and to determine an trump based on the winner of the bids.
// It takes in entry the first player who will start bidding and the decks of cards of players. But also the number of each IA.
// It returnes an array of CONTRACT that contain the contract and the color of the contract of each player.
CONTRACT* DetermineTrumpColorAndManageBids(int Firstplayerwhostart, CARD* Deckofcardshuman, CARD* DeckofcardsIA1, CARD* DeckofcardsIA2, CARD* DeckofcardsIA3, int IA1number, int IA2number, int IA3number) {
	CONTRACT max = { 0,-1 };
	CONTRACT* contractplayerandcolortrump = (CONTRACT*)malloc(numberofcardsinthedeck * sizeof(CONTRACT));
	printf("Bidding round to determine the CONTRACT and the TRUMP : \n");
	printf("-------------------------------------------------------");
	printf("\n");
	printf("\n");
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
	printf("\n");
	printf("\n");
	return contractplayerandcolortrump;
}

// This function has as goal to determine the winner team in relation to score counter of players.
int DetermineTheWinnerTeam(int* Playerscorecounter, CONTRACT Contract, int Contractteam, int* scoreteam) {
	int winnerteam = -1;
	scoreteam[0] = Playerscorecounter[0] + Playerscorecounter[2];
	scoreteam[1] = Playerscorecounter[1] + Playerscorecounter[3];
	if (Contractteam == 0) {
		if (scoreteam[0] > 82 && scoreteam[0] > Contract.valueContract) {
			winnerteam = 0;
		}
		else {
			scoreteam[1] = scoreteam[1] + Contract.valueContract;
			winnerteam = 1;
		}
	}
	else if (Contractteam == 1) {
		if (scoreteam[1] > 82 && scoreteam[1] > Contract.valueContract) {
			winnerteam = 1;
		}
		else {
			scoreteam[0] = scoreteam[0] + Contract.valueContract;
			winnerteam = 0;
		}
	}
	return winnerteam;
}


// This function has as goal to determined a winner between the player.
// It takes in entry a referencing array of played cards during the turn, the number of played card to browse the array of referencing, and a players score counter (in the form of an array).
// input : a referencing array of played cards
// input : number of played cards during the turn
// input : a player score counter
// output : a boolean which corresponds to the existence of a winner or not
int DeterminingAWinnerAmongThePlayers(CARD* Referencingarrayofplayedcards, int* Playerscorecounter, int FirstPlayer, int Numberofcurrentturn) {
	int i;
	CARD max = { -1,-1,-1 };
	int askedColor = Referencingarrayofplayedcards[FirstPlayer].color;
	int winningplayernumber = -1;
	int winnerspoints = 0;
	for (i = 0; i < numberofplayer; i++) {
		int numJoueurOrdonne = (i + FirstPlayer) % 4;
		winnerspoints += GetPointOfACard(Referencingarrayofplayedcards[numJoueurOrdonne]);
		if ((i == 0)
			|| ((askedColor == Referencingarrayofplayedcards[numJoueurOrdonne].color) && (GetValueOfACard(Referencingarrayofplayedcards[numJoueurOrdonne]) > GetValueOfACard(max)))
			|| ((Referencingarrayofplayedcards[FirstPlayer].trump == 1) && (GetValueOfACard(Referencingarrayofplayedcards[numJoueurOrdonne]) > GetValueOfACard(max)))) {
			max = Referencingarrayofplayedcards[numJoueurOrdonne];
			winningplayernumber = numJoueurOrdonne;
		}
	}
	if (Numberofcurrentturn == 7) {
		printf("Bonus of 10 for the last turn.\n");
		winnerspoints += 10;
	}

	if (winningplayernumber != -1) {
		Playerscorecounter[winningplayernumber] = Playerscorecounter[winningplayernumber] + winnerspoints;
		if (winningplayernumber == 0 || winningplayernumber == 2) {
			printf("Player %s %s, wins. His score is increased by %d, and reaches %d.\n", TabName[winningplayernumber], TabTeamNameAscii[0], winnerspoints, Playerscorecounter[winningplayernumber]);
			printf("\n");
			printf("\n");
		}
		else {
			printf("Player %s %s, wins. His score is increased by %d, and reaches %d.\n", TabName[winningplayernumber], TabTeamNameAscii[1], winnerspoints, Playerscorecounter[winningplayernumber]);
			printf("\n");
			printf("\n");
		}
	}
	else {
		printf("Impossible, there should be a winner.\n");
		printf("\n");
	}
	return winningplayernumber;
}

// This function has as goal to play a turn. It means that the role of this function is to make the human and the three AIs play in a successive way.
// This function allocates memory for the referencing array of the played cards.
// input : deck of cards of the human, the first IA, the second IA, and the third IA.
// input : players score counter
// input : the number of the current turn
int PlayOneRound(CARD* Humandeck, CARD* IA1deck, CARD* IA2deck, CARD* IA3deck, int* Playerscorecounter, int Numberofthecurrentturn, int Firstplayernumber, int Trumpofthegame) {
	printf("					Turn number %d : \n", Numberofthecurrentturn);
	printf("					----------------\n");
	printf("\n");
	printf("Trump of the game : %s\n", TabColor[Trumpofthegame]);
	printf("\n");
	int winneroftheturn = 0;
	CARD* referencingarrayoftheplayedcards = malloc(sizeofreferencingarray * sizeof(CARD));
	InitializedArray(referencingarrayoftheplayedcards, sizeofreferencingarray);
	int numberofeachplayer[4] = { 0,1,2,3 };
	for (int iPlayer = 0; iPlayer < numberofplayer; iPlayer++) {
		int numPlayer = (Firstplayernumber + iPlayer) % numberofplayer;
		if (numPlayer == 0) {
			PlayAHumanPlayer(Humandeck, referencingarrayoftheplayedcards, numberofeachplayer[0], Numberofthecurrentturn, Firstplayernumber);
		}
		else {
			switch (numPlayer) {
			case 1:
				PlayAnIAPlayer(IA1deck, referencingarrayoftheplayedcards, numberofeachplayer[1], Numberofthecurrentturn, Firstplayernumber);
				break;
			case 2:
				PlayAnIAPlayer(IA2deck, referencingarrayoftheplayedcards, numberofeachplayer[2], Numberofthecurrentturn, Firstplayernumber);
				break;
			case 3:
				PlayAnIAPlayer(IA3deck, referencingarrayoftheplayedcards, numberofeachplayer[3], Numberofthecurrentturn, Firstplayernumber);
				break;
			}
		}
		printf("\n");
	}
	winneroftheturn = DeterminingAWinnerAmongThePlayers(referencingarrayoftheplayedcards, Playerscorecounter, Firstplayernumber, Numberofthecurrentturn);
	return winneroftheturn;
}


// The purpose of this function is to play a party, i.e. to play several turns (as many as there are cards in the player's hands).
// There is no input parameters but the function dynamically allocates a  piece of memory to deck of cards of the human and IAs
// The function displays the winner of this party.
void PlayOneGame() {
	char playername[100];
	printf("What is your name ?\n");
	printf("\n");
	scanf("%s", &playername);
	printf("\n"); 
	printf("\n");
	FillName(playername);
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
	printf("There's the team of the part :\n");
	printf("------------------------------");
	printf("\n");
	printf("\n");
	printf("Sun %s  : %s  +  %s", TabTeamNameAscii[0], TabName[humanplayernumber], TabName[IA2playernumber]);
	printf("\n");
	printf("\n");
	printf("Moon %s : %s  +  %s\n", TabTeamNameAscii[1], TabName[IA1playernumber], TabName[IA3playernumber]);
	printf("\n");
	printf("\n");
	CONTRACT* contractplayer;
	contractplayer = DetermineTrumpColorAndManageBids(firstplayerwhobidding, humancards, IA1cards, IA2cards, IA3cards, IA1playernumber, IA2playernumber, IA3playernumber);
	int iMax = 0;
	for (int i = 1; i < numberofplayer; i++) {
		if (contractplayer[i].valueContract > contractplayer[iMax].valueContract) {
			iMax = i;
		}
	}
	int trumpforthepart = contractplayer[iMax].colorContract;
	int firstplayer = iMax;
	int playerwhowin = -1;
	FillTheTrumpGameOfTheStructCard(humancards, trumpforthepart);
	FillTheTrumpGameOfTheStructCard(IA1cards, trumpforthepart);
	FillTheTrumpGameOfTheStructCard(IA2cards, trumpforthepart);
	FillTheTrumpGameOfTheStructCard(IA3cards, trumpforthepart);
	int numberofthecurrentturn = 0;
	for (int i = 0; i < numberofcardperplayer; i++) {
		playerwhowin = PlayOneRound(humancards, IA1cards, IA2cards, IA3cards, playerscorecounter, numberofthecurrentturn, firstplayer, trumpforthepart);
		firstplayer = playerwhowin;
		numberofthecurrentturn++;
	}
	int contractteam;
	if (iMax == 0 || iMax == 2) {
		contractteam = 0;
	}
	else {
		contractteam = 1;
	}
	int scoreteam[2] = { 0 };
	int winnerteam = -1;
	CONTRACT contract = contractplayer[iMax];
	winnerteam = DetermineTheWinnerTeam(playerscorecounter, contract, contractteam, scoreteam);
	printf("Score team Sun %s  :  %d\n", TabTeamNameAscii[0], scoreteam[0]);
	printf("\n");
	printf("Score team Moon %s  :  %d\n", TabTeamNameAscii[1], scoreteam[1]);
	printf("\n");
	printf("THE WINNER TEAM OF THIS GAME IS THE TEAM %s", NameTeam[winnerteam]);
	printf("\n");
	printf("\n");
	WriteTheNameAndPointsOfTheWinnerOnAFile(playername, playerscorecounter[0]);
}

// This function has as goal to display the interface at the beginning of the game.
// The interface will consist of a menu with several possible choices.
// It takes in entry nothing and returns nothing

void DisplayTheInterfaceOfTheGame() {

	int answer;
	printf(" ___      _     _                _         _        \n| _ ) ___| |___| |_ ___   __ ___(_)_ _  __| |_  ___ \n| _ \\/ -_) / _ \\  _/ -_) / _/ _ \\ | ' \\/ _| ' \\/ -_)\n|___/\\___|_\\___/\\__\\___| \\__\\___/_|_||_\\__|_||_\\___|");
	printf("\n");
	printf("\n");
	printf("What do you want to do ?");
	printf("\n");
	printf("1) Play a new game\n");
	printf("2) See the best score of the game\n");
	printf("3) Exit\n");
	scanf("%d", &answer);
	while (answer < 1 && answer>3) {
		printf("Error, try again.\n");
		scanf("%d", &answer);
	}
	printf("\n");

    FILE * file = NULL;
    char string[1000] = "";

	switch (answer) {
	case 1:
		PlayOneGame();
		break;
	case 2:
		file = fopen("Belote_score.txt", "r");

		if (file != NULL)
		{
			while (fgets(string, 1000, file) != NULL)
			{
				printf("%s", string);
			}

			fclose(file);
		}
		else
		{
			printf("Impossible d'ouvrir le fichier test.txt");
		}
		break;
	case 3:
		exit(0);
		break;

	}

}
