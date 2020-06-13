#include "Defs.h"
const int numberofplayer = 4;
const int numberofcardsinthedeck = 32;
const int numberofcardperplayer = 8;
const int sizeofreferencingarray = 4;
const int numberofcolor = 4;

// This is the constant value of cards
const char* TabCardName[] = { "7", "8", "9", "10", "J", "Q", "K", "A" };
const char* TabTeamNameAscii[] = { SUN, MOON };
const int TabValues[] = { 0, 1, 2, 6, 3, 4, 5, 7 };
const char* NameTeam[] = { "Sun", "Moon" };
const int PointNormal[] = { 0,0,0,10,2,3,4,11 };
const int PointTrump[] = { 0,0,14,10,20,3,4,11 };
// This is the constant color of cards
const char* TabColor[] = { CLUB, SPADE, HEART, DIAMOND };
const char* tabNomIA[] = { "George", "Audrey", "John" };