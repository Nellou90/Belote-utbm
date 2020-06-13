#include "Defs.h"
#include "SerializeScores.h"

// This function has as goal to write on a file.txt the name of the last winner and his score points.
// It takes in entry the name of the player and his point.
// and it returns nothing.
void WriteTheNameAndPointsOfTheWinnerOnAFile(char* Nameofwinnerplayer, int Pointsofplayer) {
	FILE* file = NULL;
	file = fopen("Belote_score.txt", "w");

	if (file != NULL)
	{
		fprintf(file, "||  Name : %s  ||  Score : %d  ||\n", Nameofwinnerplayer, Pointsofplayer);
		fprintf(file, "---------------------------------\n");
		fclose(file);
	}
	else
	{
		printf("Error file Belote_score.txt not founds");
	}
}

