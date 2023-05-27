#ifndef _PACMAN_H_
#pragma warning(disable: 4996)
#include "GameObject.h"
#include <cstring>

class Pacman : public GameObject {
	char arrowKeys[10];
	int score = 0;
public:
	void setFigure() override { figure = '@'; };
	void move(char Gameboard[80][25], int row, int col);
	void setArrowKeys() { // "The Game keys which are allowed"
		arrowKeys[0] = 'w';
		arrowKeys[1] = 'x';
		arrowKeys[2] = 'a';
		arrowKeys[3] = 'd';
		arrowKeys[4] = 's';
		arrowKeys[5] = 'W';
		arrowKeys[6] = 'X';
		arrowKeys[7] = 'A';
		arrowKeys[8] = 'D';
		arrowKeys[9] = 'S';
	}

	void pacmanToStart(int x,int y) {
		body.objectStartingPoint(x,y);
	}
	void updateScore(bool arr[80][25], int& score, int Xlegend, int Ylegend);

	int getDirection(char key) const;

};

#endif