#pragma once
#include "point.h"

class GameObject {
	enum { SIZE = 1 };
	int direction;
	
protected:Point body; char figure;

public:
	virtual void setFigure() = 0;

	void objectToStart(int x, int y) {
		body.objectStartingPoint(x, y);
	}
	int getX()
	{
		return body.getX();
	}
	int getY()
	{
		return body.getY();
	}
	int getDir() {
		return direction;
	}
	void setDirection(int dir) {
		direction = dir;
	}
	void move(bool isEaten, char gameBoard[80][25], int row, int col)
	{
		if (isEaten == true)
			body.draw(' ');
		else 
			body.draw('.');

		body.move(direction, gameBoard, row, col);
		body.draw(figure);
	}

};