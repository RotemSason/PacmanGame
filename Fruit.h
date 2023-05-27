#pragma once
#include "GameObject.h"
#include <ctime>

class Fruit : public GameObject {
public:

	void setFigure() override {	srand((unsigned int)time(NULL)); figure = (rand()%5)+'5'; };
	char getFigure() {
		return figure;
	}
	char dirToFile(int dir);
};