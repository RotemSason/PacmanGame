#include "Ghost.h"

int Ghost::getX() {
	return body.getX();
}
int Ghost::getY() {
	return body.getY();
}

void Ghost::changeDirIfTunnel(int row,int col)
{
	if (this->getX() <= 1 && this->getDir() == LEFT)
		this->setDirection(RIGHT);
	else if (this->getX() >= col - 2 && this->getDir() == RIGHT)
		this->setDirection(LEFT);
	else if (this->getY() <= 1 && this->getDir() == UP)
		this->setDirection(DOWN);
	else if (this->getY() >= row - 2 && this->getDir() == DOWN)
		this->setDirection(UP);
}
