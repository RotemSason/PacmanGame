#include "Game.h"

void Game::printMenu()
{
	clear_screen();
	cout << "* Press 1 to start a new game " << endl << "* Press 2 to load file " << endl << "* Press 8 to present instrucitons and keys" << endl << "* Press 9 to exit" << endl;
}

void Game::menuChoice(int argc, char** argv)
{
	int lvl, choice, key;
	vector<pos> ghosts;
	string mode;
	pos legend;
	hideCursor();

	if (!(argc >= 2 && strcmp(argv[1], "-load") == 0))  //if its load then skip menu
		cin >> choice;
	else
		choice = 1;
	while (choice != 9)
	{
		if (choice == 1)
		{
			winBoard = true;
			score = 0;
			scoreToWin = 0;
			char str1[] = ".";
			explore(str1);
			clear_screen();
			if (files.size() == 0)
			{
				cout << "No files found!" << endl;
				cout << "Press any key to continue";
				winBoard = false;
				_getch(); _getch(); /* twice to ensure he waits for the players choice  */
				printMenu();
			}
			if (argc >= 3 && strcmp(argv[2], "[silent]") != 0){
				cout << "Invalid cmd input"<<endl; winBoard = false;
			}
			else if (argc >= 2 && strcmp(argv[1], "-load") == 0)
			{
				clear_screen();
				bool silentMode = (argc == 3 && strcmp(argv[2], "[silent]") == 0);
				for (int i = 0; i < files.size(); i++)
				{
					if (winBoard && init(legend, i)) // valid board
						runLoad(legend, i, silentMode);
					else
					{
						cout << "Press any key to continue";
						winBoard = false;
						_getch(); _getch(); /* twice to ensure he waits for the players choice  */
						printMenu();
					}
				}
			}
			else if(argc==1 || (argc>=2 && strcmp(argv[1] ,"-save")==0))
			{
				clear_screen();
				cout << "choose level:" << endl << "1. Best " << endl << "2. Good " << endl << "3. Novice" << endl;
				cin >> lvl;
				level = lvl;
				life = 3;
				clear_screen();
				for (int i = 0; i < files.size(); i++)
				{
					if (winBoard && init(legend, i)) // valid board
						run(legend, i,argc);
					else
					{
						cout << "Press any key to continue";
						winBoard = false;
						_getch(); _getch(); /* twice to ensure he waits for the players choice  */
						printMenu();
					}
				}
			}
			else
				cout << "Invalid cmd input" << endl; winBoard = false;
			if (winBoard)
				cout << "Congratulations! you won!" << endl;
			cout << "Press any key to continue";
			_getch(); _getch(); /* twice to ensure he waits for the players choice  */
			printMenu();
		}
		if (choice == 2)
		{
			string fileName;
			clear_screen();
			cout << "Enter file name. include .screen" << endl;
			cin >> fileName;
			if (FILE* file = fopen(fileName.c_str(), "r"))
			{
				files.insert(files.begin(), fileName);
				fclose(file);
				clear_screen();
				cout << "choose level:" << endl << "1. Best " << endl << "2. Good " << endl << "3. Novice" << endl;
				cin >> lvl;
				level = lvl;
				life = 3;
				clear_screen();
				init(legend, 0);
				run(legend, 0,argc);
				files.clear();
			}
			else
				cout << "No files found!" << endl;

			cout << "Press any key to continue";
			_getch(); _getch(); /* twice to ensure he waits for the players choice  */
			printMenu();
		}
		if (choice == 8)
		{
			cout << "The player controls Pac - Man, who must eat all the dots inside an enclosed maze while avoiding 2 Dollar ghosts. Player has 3 lifes." << endl << "Keys: " << endl << "1. Movement - W: up, A: left, D: right, X: down. S: stay." << endl << "2. ESCAPE: Pause " << endl << "Press 1 to return to menu ";
			cin >> key;
			if (key == 1)
				printMenu();
		}
		cin >> choice;
	}
}

void Game::runLoad(pos& legend, int gameRound, bool silentMode)
{
	string stepsFileName, resultFileName;
	int Pdir, pointOfTime = 0,ghostCount=0;
	bool fruitOnBoard = false, arr[80][25];
	pos fruitPos;
	bool test = true;

	initToFalse(arr, row, col);
	updateLife(life, legend);
	stepsFileName = files[gameRound];
	resultFileName = files[gameRound];
	int fileNameSize = files[gameRound].size();
	stepsFileName[fileNameSize - 1] = '\0';
	stepsFileName[fileNameSize - 2] = 's';
	stepsFileName[fileNameSize - 3] = 'p';
	stepsFileName[fileNameSize - 4] = 'e';
	stepsFileName[fileNameSize - 5] = 't';
	resultFileName[fileNameSize - 6] = 'r';
	resultFileName[fileNameSize - 5] = 'e';
	resultFileName[fileNameSize - 4] = 's';
	resultFileName[fileNameSize - 3] = 'u';
	resultFileName[fileNameSize - 2] = 'l';
	resultFileName[fileNameSize - 1] = 't';
	ifstream myfile(stepsFileName);
	ifstream resultFile(resultFileName);
	int dieArr[4], count = 0;
	if (myfile.is_open())
	{
		char ch;
		string line;
		int i = 0;
		getline(myfile, line);
		while (i<line.size())
		{
			//myfile.get(ch);
			ch = line[i];
			p.updateScore(arr, score, legend.x, legend.y);

			if (ch <= 'X' && ch >= 'A')
			{
				Pdir = p.getDirection(ch);
				p.setDirection(Pdir);
				p.move(Gameboard, row, col);
				pointOfTime++;
				Sleep(20);
			}
			else if (ch <= '5' && ch >= '0')
			{
				if (ghostCount == ghosts.size())
					ghostCount = 0;
				ghostArr[ghostCount].setDirection(ch - '0');
				if (arr[ghostArr[ghostCount].getX()][ghostArr[ghostCount].getY()] == false) //if the ghost is stepping on a bread
				{
					if ((ghostArr[ghostCount].getX() <= 1 && ghostArr[ghostCount].getDir() == LEFT) || (ghostArr[ghostCount].getX() >= col - 1 && ghostArr[ghostCount].getDir() == RIGHT) || (ghostArr[ghostCount].getY() <= 1 && ghostArr[ghostCount].getDir() == UP) || (ghostArr[ghostCount].getY() >= row - 1 && ghostArr[ghostCount].getDir() == DOWN)) // ghost wants to enter a tunnel
						ghostArr[ghostCount].setDirection(5);
					else
						ghostArr[ghostCount].move(false, Gameboard, row, col);
				}
				else
				{
					if ((ghostArr[ghostCount].getX() <= 1 && ghostArr[ghostCount].getDir() == LEFT) || (ghostArr[ghostCount].getX() >= col - 1 && ghostArr[ghostCount].getDir() == RIGHT) || (ghostArr[ghostCount].getY() <= 1 && ghostArr[ghostCount].getDir() == UP) || (ghostArr[ghostCount].getY() >= row - 1 && ghostArr[ghostCount].getDir() == DOWN))
						ghostArr[ghostCount].setDirection(5);
					else ghostArr[ghostCount].move(true, Gameboard, row, col);
				}
				ghostCount++;
			}
			else if (ch == '+' || ch == '-')
			{
				if (!fruitOnBoard)
				{
					fruitOnBoard = true;
					int j=1,k = 1;
					int x=0, y=0;
					while (line[i + j]!=',')
					{
						x = x*10 + line[i + j]-'0';
						j++;
					}
					while (line[i + j+ k] != ',')
					{
						y =y * 10 + line[i +j+ k] - '0';
						k++;
					}
					f.objectToStart(x, y);
					gotoxy(40, 12);
					i+=j+k-2;		 // -2 to reduce the ',' we counted
				}
				else
					fruitDisapear(arr, fruitOnBoard);

			}
			else if (ch <= 'x' && ch >= 'a')
			{
				if(ch == 'w')
					f.setDirection(UP);
				else if (ch == 'a')
					f.setDirection(LEFT);
				if (ch == 'd')
					f.setDirection(RIGHT);
				else if (ch == 'x')
					f.setDirection(DOWN);

				if (arr[f.getX()][f.getY()] == false) //if the fruit is stepping on a bread
					f.move(false, Gameboard, row, col);
				else
					f.move(true, Gameboard, row, col);
			}

			if (hitAGhost(arr, pacStartPoint, ghosts, legend))
			{
				if (silentMode)
				{
					char temp;
					resultFile.seekg(15,ios_base::cur);
					resultFile.get(temp);
					dieArr[2 - life] = 0;
					while (temp != ',')
					{
						dieArr[2 - life] = dieArr[2 - life] * 10 + temp-'0';
						resultFile.get(temp);
						
						
					}
					if (pointOfTime-1 != dieArr[2 - life])
					{
						cout << pointOfTime-1;
						test = false;
					}
					gotoxy(50, 15);
				}
			}
		//	if (ghostHitAFruit(arr))
				
			pacHitAFruit();
			i++;
		}
	}

	myfile.close();
	int Gsize = ghosts.size();
	for (int i = 0; i < Gsize; i++)
		ghosts.pop_back();

	clear_screen();
	if (life == 0)
	{
		winBoard = false;
		cout << "GAME OVER" << endl;
	}
	else if(silentMode)
	{
		char temp;
		string line;
		resultFile.seekg(2,ios_base::cur);

		getline(resultFile,line);
		dieArr[3] = 0;
		for (int i = 25; i < line.size(); i++)
		{
			dieArr[3] = dieArr[3] * 10 + line[i] - '0';
		}
		if (pointOfTime != dieArr[3])
		{
			gotoxy(7,7);
//			cout << "real point " <<pointOfTime;
			test = false;
		}
	}
	if (silentMode)
	{
		if (test)
			cout << "test passed!" << endl;
		else cout << "test failed" << endl;
		cout << count << endl;
		
/*		cout << dieArr[0] << endl;
		cout << dieArr[1] << endl;
		cout << dieArr[2] << endl;*/
		Sleep(2000);
		clear_screen();
	}
	resultFile.close();
}

bool Game::init(pos& legend, int gameRound)
{
	int countG = 0, countP = 0,  firstWall;
	string line;
	bool isFirstWall = false;
	if(!readFile(legend, gameRound))
		return false;
	printboard(legend);
	remainLife(legend);
	p.setArrowKeys();
	p.setFigure();
	for (int i = 0; i < ghosts.size(); i++)
	{
		ghostArr[i].setFigure();
		ghostArr[i].startingPoint(ghosts[i].x, ghosts[i].y);
	}
	p.pacmanToStart(pacStartPoint.x, pacStartPoint.y);
	p.setDirection(4);
	f.setFigure();
	return true;
}
void Game::printboard(pos& legend) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j >= legend.x && j < (legend.x) + 17 && i >= legend.y && i < (legend.y) + 3) // part of the legend 
			{
				//scoreToWin--; // food on legend
				cout << ' ';
			}
			else if ((j == col - 1 || i == row - 1 || i == 0 || j == 0) && (Gameboard[j][i] == '.' || Gameboard[j][i] == '@' || Gameboard[j][i] == '$'))
			{
				scoreToWin--; // food on wall
				cout << ' ';
			}
			else if (Gameboard[j][i] == '%')
			{
				cout << ' ';
			}
			else
				cout << Gameboard[j][i];

		}
		cout << endl;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Gameboard[j][i] != '%' && Gameboard[j][i] != '#' && Gameboard[j][i] != '\0')
				scoreToWin++;
		}
	}
}
void Game::run(pos legend, int gameRound, int argc)
{
	bool arr[80][25], fruitOnBoard = true;
	char stepKey='S',key = 0;
	int Pdir, ghostStep = 5;
	string steps;
	ofstream stepsFile, resultFile;
	if (argc > 1)
	{
		string stepsFileName = files[gameRound];
		int fileNameSize = files[gameRound].size();
		stepsFileName[fileNameSize - 1] = '\0';
		stepsFileName[fileNameSize - 2] = 's';
		stepsFileName[fileNameSize - 3] = 'p';
		stepsFileName[fileNameSize - 4] = 'e';
		stepsFileName[fileNameSize - 5] = 't';
		stepsFile.open(stepsFileName);
		string resultFileName = files[gameRound];
		resultFileName[fileNameSize - 6] = 'r';
		resultFileName[fileNameSize - 5] = 'e';
		resultFileName[fileNameSize - 4] = 's';
		resultFileName[fileNameSize - 3] = 'u';
		resultFileName[fileNameSize - 2] = 'l';
		resultFileName[fileNameSize - 1] = 't';
		resultFile.open(resultFileName);
	}

	pos fruitPos = setPos();
	steps = '+';
	steps += to_string(fruitPos.x);
	steps += ',';
	steps += to_string(fruitPos.y);
	steps += ',';
	f.objectToStart(fruitPos.x, fruitPos.y);
	initToFalse(arr, row, col);
	updateLife(life, legend);
	do {
		if (_kbhit())
		{
			key = _getch();
			if ((Pdir = p.getDirection(key)) != -1)
			{
				p.setDirection(Pdir);
				if (key > 'z')
					stepKey = key;
				else
					stepKey = (char)(key - 32); // convert small letter to capital letter
				gotoxy(60, 10);
			}
		}
		if (key == ESC)
			pause(key, legend);

		p.updateScore(arr, score, legend.x, legend.y);
		//stepsFile << stepKey;
		steps += stepKey;

		if (hitAGhost(arr, pacStartPoint, ghosts, legend))
		{
			stepKey = 'S';
			resultFile << "Pacman died at " << ghostStep - 5 << ",";
		}

		p.move(Gameboard, row, col);
	
		if (pacHitAFruit())
		{
			steps += '-';
			fruitDisapear(arr, fruitOnBoard);
		}
		if (ghostHitAFruit(arr))
		{
			steps += '-';
			fruitDisapear(arr, fruitOnBoard);
		}

		if (hitAGhost(arr, pacStartPoint, ghosts, legend))
		{
			stepKey = 'S';
			resultFile << "Pacman died at " << ghostStep - 5 << ",";
		}

		if (ghostStep % 2 == 0) // every two iterations ghosts will move
		{
			moveGhost(ghostStep, arr, steps);
		}

		if (hitAGhost(arr, pacStartPoint, ghosts, legend))
		{
			stepKey = 'S';
			resultFile << "Pacman died at " << ghostStep - 5 << ",";
		}

		if (ghostStep % 4 == 0) // the fruit moves every 4 iterations
		{
			if (fruitOnBoard)
			{
				if (!(f.getX() <= 1 && f.getDir() == LEFT) && !(f.getX() >= col - 1 && f.getDir() == RIGHT) && !(f.getY() <= 1 && f.getDir() == UP) && !(f.getY() >= row - 1 && f.getDir() == DOWN)) // fruit wont enter a tunnel
				{
					f.setDirection((rand() % 4));
					steps += f.dirToFile(f.getDir());
					if (arr[f.getX()][f.getY()] == false) //if the fruit is stepping on a bread
						f.move(false, Gameboard, row, col);
					else
						f.move(true, Gameboard, row, col);
				}
			}
			if (ghostStep % 80 == 0 && fruitOnBoard)
			{
				steps += '-';
				fruitDisapear(arr, fruitOnBoard);
			}
			if (ghostStep % 100 == 0 && !fruitOnBoard) // fruit return to board
			{
				steps += '+';
				fruitPos = setPos();
				steps += to_string(fruitPos.x);
				steps += ',';
				steps += to_string(fruitPos.y);
				steps += ',';
				f.objectToStart(fruitPos.x, fruitPos.y);
				fruitOnBoard = true;
			}
		}
		if (fruitOnBoard &&  ghostHitAFruit(arr))
		{
			steps += '-';
			fruitDisapear(arr, fruitOnBoard);
		}
		if (fruitOnBoard && pacHitAFruit())
		{
			steps += '-';
			fruitDisapear(arr, fruitOnBoard);
		}
		if (argc > 1)
		{
			stepsFile << steps;
			gotoxy(81, 15);cout << steps;
		}
		steps = "";

		gotoxy(50, 13);
		ghostStep++;
		Sleep(200);

	} while (life > 0 && score < scoreToWin);
		int Gsize = ghosts.size();
		for (int i = 0; i < Gsize; i++)
			ghosts.pop_back();

		clear_screen();
		if (life == 0)
		{
			if (argc > 1)
			{
				resultFile.close();
				stepsFile.close();
			}
			winBoard = false;
			cout << "GAME OVER" << endl;
		}
		else if (argc > 1)
		{
			resultFile << endl << "Pacman finished screen at" << ghostStep - 5;
			resultFile.close();
			stepsFile.close();
		}
	
}
bool Game::pacHitAFruit()
{
	if (f.getX() == p.getX() && f.getY() == p.getY())
	{
		score += f.getFigure() - '0';
		scoreToWin += f.getFigure() - '0';
		return true;
	}
	return false;
}
void Game::fruitDisapear(bool arr[80][25], bool& fruitOnBoard)
{
	gotoxy(f.getX(), f.getY());
	if (arr[f.getX()][f.getY()] == false)
		cout << '.';
	else
		cout << ' ';
	f.objectToStart(-1, -1);
	f.setDirection(5);
	fruitOnBoard = false;
}


bool Game::hitAGhost(bool arr[80][25], pos pacStartPoint, vector<pos> ghosts,pos legend)
{
	for (int i = 0; i < ghosts.size(); i++)
	{
		if (ghostArr[i].getX() == p.getX() && ghostArr[i].getY() == p.getY())
		{
			Sleep(1000);
			p.objectToStart(pacStartPoint.x, pacStartPoint.y);
			p.setDirection(4); // make pacman stay after death
			for (int j = 0; j < ghosts.size(); j++)
			{
				if (arr[ghostArr[j].getX()][ghostArr[j].getY()] == false) // check if the ghosts are on a bread before returning him
				{
					gotoxy(ghostArr[j].getX(), ghostArr[j].getY());
					cout << '.';
				}
				else {
					gotoxy(ghostArr[j].getX(), ghostArr[j].getY());
					cout << ' ';
				}
				ghostArr[j].objectToStart(ghosts[j].x, ghosts[j].y); //return all ghosts to starting position
			}
			life--;
			updateLife(life, legend);
			return true;
		}
	}
	return false;
}
bool Game::isWall(const int x, const int y)
{
	if (Gameboard[x][y] == '#')
	{
		return true;
	}
	return false;
}

void Game::moveGhost(const int ghostStep, bool arr[80][25], string& steps)
{
	int dir, v = 25;
	pos source, dest;
	vector<pos> adj[80][25];
	bool samePos = false;
	// array of vectors is used to store the graph
	// in the form of an adjacency list
	if (level == 1 || level == 2)
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (!isWall(i, j)) {
					if (!isWall(i, j + 1))
						add_edge(adj, { i,j }, { i,j + 1 });
					if (!isWall(i + 1, j))
						add_edge(adj, { i,j }, { i + 1,j });
					if (j != 0 && !isWall(i, j - 1))
						add_edge(adj, { i,j }, { i,j - 1 });
					if (i != 0 && !isWall(i - 1, j))
						add_edge(adj, { i,j }, { i - 1,j });
				}
			}
		}
		if (level == 1)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				samePos = false;
				source = { ghostArr[i].getX(), ghostArr[i].getY() }, dest = { p.getX(),p.getY() };
				int gDir = setGhostDir(adj, source, dest, v);
				for (int j = 0; j < ghosts.size(); j++)
				{
					if (j != i && !samePos)
						if (ghostArr[i].getX() == ghostArr[j].getX() && ghostArr[i].getY() == ghostArr[j].getY()) // ghosts on the same pos
						{
							ghostArr[i].setDirection(5 - gDir);
							ghostArr[j].setDirection(gDir);
							samePos = true;
						}
				}
				if (!samePos)
					ghostArr[i].setDirection(gDir);
			}
		}
		if (level == 2)
		{
			if (ghostStep % 40 == 0) {  // every 2 itteration the ghosts move
				for (int i = 0; i < ghosts.size(); i++)
				{
					dir = rand() % 4;
					ghostArr[i].changeDirIfTunnel(row, col);
				}
			}
			if ((ghostStep % 40) >= 10) {
				for (int i = 0; i < ghosts.size(); i++)
				{
					source = { ghostArr[i].getX(), ghostArr[i].getY() }, dest = { p.getX(),p.getY() };
					ghostArr[i].setDirection(setGhostDir(adj, source, dest, v));
				}
			}
		}
	}
	if (level == 3)
	{
		for (int i = 0; i < ghosts.size(); i++) {
			ghostArr[i].changeDirIfTunnel(row, col);
		}
		if (ghostStep % 40 == 6) {
			for (int i = 0; i < ghosts.size(); i++) {
				dir = rand() % 4;
				ghostArr[i].setDirection(dir);
			}
		}
	}
	for (int i = 0; i < ghosts.size(); i++)
	{

		if (arr[ghostArr[i].getX()][ghostArr[i].getY()] == false) //if the ghost is stepping on a bread
		{
			if ((ghostArr[i].getX() <= 1 && ghostArr[i].getDir() == LEFT) || (ghostArr[i].getX() >= col - 1 && ghostArr[i].getDir() == RIGHT) || (ghostArr[i].getY() <= 1 && ghostArr[i].getDir() == UP) || (ghostArr[i].getY() >= row - 1 && ghostArr[i].getDir() == DOWN)) // ghost wants to enter a tunnel
				ghostArr[i].setDirection(5);
			else
			{
				steps += to_string(ghostArr[i].getDir());
				ghostArr[i].move(false, Gameboard, row, col);
			}
		}
		else
		{
			if ((ghostArr[i].getX() <= 1 && ghostArr[i].getDir() == LEFT) || (ghostArr[i].getX() >= col - 1 && ghostArr[i].getDir() == RIGHT) || (ghostArr[i].getY() <= 1 && ghostArr[i].getDir() == UP) || (ghostArr[i].getY() >= row - 1 && ghostArr[i].getDir() == DOWN))
				ghostArr[i].setDirection(5);
			else 
			{
				steps += to_string(ghostArr[i].getDir());
				ghostArr[i].move(true, Gameboard, row, col);
			}
		}
	}
}


void Game::pause(char& key, pos legend) {
	key = ' '; // init key to enter the while loop
	gotoxy((legend.x) + 1, legend.y); // TO CHANGE
	cout << "GAME PAUSED";
	while (key != ESC)
	{
		key = _getch();
	}
	gotoxy((legend.x) + 1, legend.y);
	cout << "            "; // Erase the "game paused" sign
	key = ' '; // change key from ESC so the function wont be called again
}
void Game::updateLife(int life, pos legend) const
{
	gotoxy((legend.x) + 1, (legend.y) + 1);
	cout << life;
}

void Game::remainLife(pos legend) const
{
	gotoxy((legend.x) + 3, (legend.y) + 1);
	cout << " Lifes Remain";
	gotoxy((legend.x) + 1, (legend.y) + 2);
	cout << "Score:";
}

bool Game::ghostHitAFruit(bool arr[80][25])
{
	for (int i = 0; i < ghosts.size(); i++)
	{
		if (ghostArr[i].getX() == f.getX() && ghostArr[i].getY() == f.getY())
		{
			gotoxy(f.getX(), f.getY());
			if (arr[f.getX()][f.getY()] == false)
				cout << '.';
			else
				cout << ' ';
			f.objectToStart(-1, -1);
			return true;
		}
	}
	return false;
}

bool Game::readFile(pos& legend, int gameRound)
{
	int countG = 0, countP = 0, legendCount=0, width, firstWall;
	string line;
	bool isFirstWall = false;

	ifstream myfile(files[gameRound]);

	if (myfile.is_open())
	{
		getline(myfile, line); //reading the first line
		width = line.length();

		if (width > 80)
			width = 80;
		for (int i = 0; i < width; i++)
		{
			Gameboard[i][0] = line[i];
			switch (line[i]){
			
			case '#':
				//	if (line[i] == '#')
				firstWall = i;
				break;
			case '@':
				pacStartPoint.x = i;
				pacStartPoint.y = 0;
				countP++;
				break;
			case ' ':
				Gameboard[i][0] = '.';
				break;
			case '%':
				Gameboard[i][0] = '%';
				break;
			case '&': 
				legend = { i,0 };
				Gameboard[i][0] = ' ';
				firstWall = 3;
				if (width < i + 17)
				{
					width = i + 17;
					i = width - 1;
				}
				legendCount++;
				break;
			default: 
				cout << "Invalid character!";
				return false;
				break;
			}
		}
		int _row = 1;

		while (!myfile.eof())
		{
			getline(myfile, line);
			int len = line.length();
			for (int i = 0; i < width; i++)
			{
				if (i >= len)
					Gameboard[i][_row] = '.';
				else
				{
					Gameboard[i][_row] = line[i];
					switch (line[i]) {

					case '#':
						break;
					case '@':
						countP++;
						pacStartPoint.x = i;
						pacStartPoint.y = _row;
						break;
					case ' ':
						Gameboard[i][_row] = '.';
						break;
					case '%':
						Gameboard[i][_row] = '%';
						break;
					case '&':
						legendCount++;
						legend = { i,_row };
						break;
					case '$': 
						countG++;
						ghosts.push_back({ i,_row });
						break;
					default:
						cout << "Invalid character at line "<< _row <<endl;
						return false;
					}
				}
			}
			_row++;
		}

		if (legendCount != 1)
		{
			cout << "There are " << legendCount << " &'s " << endl;
			return false;
		}
		if (countP != 1)
		{
			cout << "There are " << countP << " Pacman's " << endl;
			return false;
		}
		if (countG > 4)
		{
			cout << "Too many ghosts!" << endl;
			return false;
		}
		if (legend.y == _row - 1) //if legend is in last line
		{
			_row += 2;
		}
		for (int k = 0; k < 17; k++)
		{
			for (int l = 0; l < 3; l++)
			{
				Gameboard[legend.x + k][legend.y + l] = '#';
			}
		}
		col = width;
		row = _row;
		myfile.close();
	}
	return true;
}

void Game::initToFalse(bool arr[80][25], const int row, const int col)
{
	for (int i = 1; i < col - 1; i++)
	{
		for (int j = 1; j < row - 1; j++)
		{
			if (Gameboard[i][j] != '%' && Gameboard[i][j] != '\0')
				arr[i][j] = false;

		}
	}
}

pos Game::setPos()
{
	pos p;
	p.x = rand() % (col - 2);
	p.y = rand() % (row - 2);
	while (isWall(p.x, p.y) || Gameboard[p.x][p.y] == '\0')
	{
		p.x = rand() % (col - 2);
		p.y = rand() % (row - 2);
	}
	return p;
}

bool Game::gameFile(string path)
{
	int size = path.size();
	if (size < 6)
		return false;
	char endName[7] = {};

	for (int i = 0; i < 6; i++)
	{
		endName[5 - i] = *(path.rbegin() + i);

	}
	endName[6] = '\0';
	if (strcmp(endName, "screen") == 0)
		return true;
	return false;
}

void Game::explore(char* dir_name)
{
	string str;
	DIR* dir;

	struct dirent* entry;
	struct stat info;
	dir = opendir(dir_name);

	if (!dir) {

		cout << "Directory was not found\n" << endl;
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			string path = string(dir_name + 1) + string(entry->d_name);

			string* path1 = &path;

			if (gameFile(path))
			{
				str = *(path1);
				files.push_back(str);
			}
			int size = path.size();

			char* _path = new char[size];

			for (int i = 0; i < size; i++)
			{
				_path[i] = path[i];
			}
			stat(_path, &info);

			if (S_ISDIR(info.st_mode))
				explore(_path);
		}
	}
	closedir(dir);
}