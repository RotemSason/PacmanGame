#include "Pacman.h"

void Pacman::move(char Gameboard[80][25], int row, int col)
{
	body.draw('  ');
	body.move(getDir(), Gameboard, row, col);
	body.draw('@');
}
int Pacman:: getDirection(char key) const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i])
		{
			return i;
		}
	}
	for (int i = 5; i < 10; i++)
	{
		if (key == arrowKeys[i])
		{
			return (i - 5);  // to return the same value as small letters
		}
	}

	return -1;
}

void Pacman::updateScore(bool arr[80][25], int& score, int Xlegend, int Ylegend)
{
	body.updateScore(arr, score,Xlegend,Ylegend);
} 