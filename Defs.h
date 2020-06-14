#ifndef DEFS
#define DEFS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h.>
#if defined(_WIN32) || defined(__MSDOS__)
#include<windows.h>
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#define SUN     "\xE2\x98\x80"
#define MOON    "\xE2\x98\xBE"
#else
#define SPADE   "Spade" //\xE2\x99\xA0"
#define CLUB    "Club"  //\xE2\x99\xA3"
#define HEART   "Heart" // \xE2\x99\xA5"
#define DIAMOND "Diamond" //\xE2\x99\xA6"
#endif
#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4996)

extern const int numberofplayer;
extern const int numberofcardsinthedeck;
extern const int numberofcardperplayer;
extern const int sizeofreferencingarray;
extern const int numberofcolor;

// This is the constant value of cards
extern const char* TabCardName[];
extern const char* TabTeamNameAscii[];
extern const int TabValues[];
extern const char* NameTeam[];
extern const int PointNormal[];
extern const int PointTrump[];
// This is the constant color of cards
extern const char* TabColor[];
extern const char* tabNomIA[];

// The struct CONTRACT integrates in it-self the value of the contract and the color of the contract
typedef struct _CONTRACT_ {
	int valueContract;
	int colorContract;
} CONTRACT;

// The struct CARD integrates in it-self the value and the color of a card and if the card is an atout or not
typedef struct _CARD_ {
	int index;
	int color;
	int trump;
} CARD;

extern char** TabName;
#endif
