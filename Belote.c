#include "Defs.h"
#include "GameOperations.h"

int main(){
	FixTheRandomSeed();
#if defined(_WIN32) || defined(__MSDOS__)
	SetConsoleOutputCP(65001);
#endif
	DisplayTheInterfaceOfTheGame();
}










