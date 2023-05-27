#include "point.h"

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}
int Point::getX()const
{
	return x;
}
int Point::getY() const
{
	return y;
}

bool Point::isWall(const int x, const int y, char board[80][25])
{
	if (board[x][y] == '#')
	{
		return true;
	}
	return false;
}

void Point::updateScore(bool arr[80][25], int &score,int Xlegend,int Ylegend)
{

	if (arr[x][y] == false)
	{
		arr[x][y] = true;
		score++;
	}
	gotoxy(Xlegend+7, Ylegend+2); // print score
	cout << score;
}

void Point::move(const int dir, char Gameboard[80][25],int row,int col) {
	
	switch (dir) {
	case 0: // UP
		--y;
		if (y < 1)
		{
			if (y==-1||((Gameboard[x][y] != '#') && Gameboard[x][row-1] != '#'))
				y = row - 1;
			else
				y++;
		}
		if (isWall(x, y, Gameboard))
			y++;

		break;
	case 1: // DOWN
		++y;
		if (y>=row){
			if ((Gameboard[x][y]!='#') && Gameboard[x][0] != '#')
				y=0;
			else
				y=row-1;
		}
		if (isWall(x,y, Gameboard))
			y--;
		break;
	case 2: // LEFT
		--x;
		if (x < 1) {
			if ((Gameboard[x][y]!='#') && Gameboard[col-1][y] != '#')
				x =col-1;
			else
				x=1;
		}
		if (isWall(x, y, Gameboard))
			x++;
		break;
	case 3: // RIGHT
		++x;
		if (x >= col) {
			if ((Gameboard[x][y]!='#') && Gameboard[0][y] != '#')
				x = 0;
			else
				x = col-1;
		}
		if (isWall(x, y, Gameboard))
			x--;
		break;
	case 4: // STAY

		break;
	}
}



