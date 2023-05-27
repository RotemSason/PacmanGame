#include "Fruit.h"

char Fruit:: dirToFile(int dir)
{
	if (dir == 0)
		return 'w';
	if (dir == 1)
		return 'x';
	if (dir == 2)
		return 'a';
	if (dir == 3)
		return  'd';
	if (dir == 4)
		return 's';
	return -1;
}