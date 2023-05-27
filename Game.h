#ifndef _THESNAKESGAME_H_
#include "Pacman.h"
#include "Ghost.h"
#include "io_utils.h"
#include <fstream>
#include <vector>
#include <string>
#include "point.h"
#include "dirent.h"
#include "Fruit.h"


class Game {
	enum { ESC = 27 };
	Pacman p;
	Ghost ghostArr[4];
	Fruit f;
	char Gameboard[80][25];
	vector<string> files;
	int row, col, level, life = 3, score = 0, scoreToWin = 0;
	pos pacStartPoint;
	vector <pos>ghosts;
	bool winBoard = true;

public:

	void printMenu();
	void menuChoice(int argc, char** argv);
	bool init(pos& legend, int gameRound);
	void run(pos legend, int gameRound, int argc);
	void remainLife(pos legend) const;
	void updateLife(int life, pos legend) const;
	void pause(char& key, pos legend);
	bool hitAGhost(bool arr[80][25], pos pacStartPoint, vector<pos> ghosts, pos legend);
	void moveGhost(const int ghostStep, bool arr[80][25], string& steps);
	void add_edge(vector<pos> adj[80][25], pos src, pos dest);
	int setGhostDir(vector<pos> adj[80][25], pos s, pos dest, int v);
	bool BFS(vector<pos> adj[80][25], pos src, pos dest, int v, pos pred[80][25], int dist[80][25]);
	bool isWall(const int x, const int y);
	void explore(char* dir_name);
	bool gameFile(string path);
	bool ghostHitAFruit(bool arr[80][25]);
	bool pacHitAFruit();
	pos setPos();
	void fruitDisapear(bool arr[80][25], bool& fruitOnBoard);
	void initToFalse(bool arr[80][25], const int row, const int col);
	bool readFile(pos& legend, int gameRound);
	void printboard(pos& legend);
	void runLoad(pos& legend, int gameRound, bool silentMode);
};

#endif