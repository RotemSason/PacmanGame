#include <windows.h>
#include <iostream>
using namespace std;
#include "Game.h"
#include "point.h"


int main(int argc, char** argv)
{
	Game game;

	if (!(argc >= 2 && strcmp(argv[1], "-load") == 0)) //if its load then skip menu
	{
		game.printMenu();
	}
    game.menuChoice(argc, argv); 
}