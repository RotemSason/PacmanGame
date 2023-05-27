#ifndef _POINT_H_
#define _POINT_H_


#include <iostream>
#include "io_utils.h"


using namespace std;

struct pos {
	int x, y;
	bool operator<(const pos& o) const {
		return x < o.x || (x == o.x && y < o.y);
	}
	bool operator==(const pos& o) const {
		if (o.x == this->x && o.y == this->y)
			return true;
		return false;
	}
};
class Point {

	int x, y;
public:
	void draw(char ch);
	void move(const int direction,char board[80][25],int row,int col);
	bool isWall(const int x, const int y, char board[80][25]);
	void updateScore(bool arr[80][25], int& score, int Xlegend, int Ylegend);

	void objectStartingPoint(int _x, int _y) {
		x = _x; y = _y;
	}
	int getX() const;
	int getY() const;
};



#endif