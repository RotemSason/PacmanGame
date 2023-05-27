#pragma once
#include "point.h"
#include "GameObject.h"

class Ghost: public GameObject {
	enum { SIZE = 1 };
public: 
	void setFigure() override { figure = '$'; };
	void startingPoint(int _x, int _y) {
		body.objectStartingPoint(_x, _y);
	}

	int getX();
	int getY();
	void changeDirIfTunnel(int row, int col);
};
enum { UP, DOWN, LEFT, RIGHT };
