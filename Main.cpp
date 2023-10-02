#include <iostream>
#include "_Common.h"
#include "_Board.h"
#include "_Game.h"
#include <conio.h>
#include <fstream>
#include <ctime>
#include <random>
#include "_Point.h"
using namespace std;

#define BOARD_SIZE 25
#define LEFT 1
#define TOP 1
#define TIME 2 //default 30min 30*60 s

_Game g(BOARD_SIZE, LEFT, TOP);

void NewGame();
void CPUGame();

void Menu(int, bool, bool, bool);
void Options(bool&, bool&, bool&);
bool LoadGame(bool&, bool&, bool&);
void ShowLoadGame(string, string&);
void Save(string, bool, bool);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	_Common::fixConsoleWindow();
	Menu(0, true, true, false);
	return 0;
}

void Menu(int choose, bool options, bool turn, bool time) {
	_Common::Nocursortype();
	system("cls");

	// In ra man hinh hinh chu nhat chua khung chu CARO
	_Common::gotoXY(40, 10);
	for (int i = 40; i <= 170; i++) {
		if (i == 40) putchar(201);
		else if (i == 170) putchar(187);
		else putchar(205);
	}
	for (int i = 11; i <= 25; i++) {
		_Common::gotoXY(40, i); putchar(186);
		_Common::gotoXY(170, i); putchar(186);
	}
	_Common::gotoXY(40, 26);
	for (int i = 40; i <= 170; i++) {
		if (i == 40) putchar(200);
		else if (i == 170) putchar(188);
		else putchar(205);
	}

	_Common::TextColor(ColorCode_Yellow);

	_Common::gotoXY(41, 11);
	cout << "        XXXXXXXXXXXXXXXXXXXX                    000000000                   XXXXXXXXXXXXXXXXX                0000000000";
	_Common::gotoXY(41, 12);
	cout << "      XXXX               XXXX                  00000000000                  XXXXXXXXXXXXXXXXXXXX           00000000000000";
	_Common::gotoXY(41, 13);
	cout << "      XXXX               XXXX                 0000000000000                 XXXX            XXXX          0000        0000";
	_Common::gotoXY(41, 14);  
	cout << "      XXXX                                   0000       0000                XXXX            XXXX          0000        0000";
	_Common::gotoXY(41, 15);
	cout << "      XXXX                                  0000         0000               XXXX            XXXX          0000        0000";
	_Common::gotoXY(41, 16);
	cout << "      XXXX                                 0000           0000              XXXX            XXXX          0000        0000";
	_Common::gotoXY(41, 17); 
	cout << "      XXXX                                000000000000000000000             XXXXXXXXXXXXXXXXXXXX          0000        0000";
	_Common::gotoXY(41, 18);
	cout << "      XXXX                               00000000000000000000000            XXXXXXXXXXXXXXXXX             0000        0000";
	_Common::gotoXY(41, 19);
	cout << "      XXXX                              0000                 0000           XXXX          XXXXX           0000        0000";
	_Common::gotoXY(41, 20);
	cout << "      XXXX               XXXX          0000                   0000          XXXX           XXXXX          0000        0000";
	_Common::gotoXY(41, 21); 
	cout << "      XXXX               XXXX         0000                     0000         XXXX            XXXXX          00000000000000";
	_Common::gotoXY(41, 22);
	cout << "        XXXXXXXXXXXXXXXXXXXX         0000                       0000        XXXX             XXXXX           0000000000";
	_Common::TextColor(ColorCode_Red);
	_Common::gotoXY(41, 25);
	cout << "                                                           BY: TEAM-8-HCMUS";

	_Common::TextColor(ColorCode_DarkYellow);
	bool check = true;
	while (check) {
		_Common::gotoXY(105, 32);
		cout << "NEW GAME";
		_Common::gotoXY(100, 32);
		cout << "     ";
		_Common::gotoXY(105, 34);
		cout << "LOAD GAME";
		_Common::gotoXY(100, 34);
		cout << "     ";
		_Common::gotoXY(105, 36);
		cout << "SETTING";
		_Common::gotoXY(100, 36);
		cout << "     ";
		_Common::gotoXY(105, 38);
		cout << "ABOUT";
		_Common::gotoXY(100, 38);
		cout << "     ";
		_Common::gotoXY(105, 40);
		cout << "HOW TO PLAY";
		_Common::gotoXY(100, 40);
		cout << "     ";
		_Common::gotoXY(105, 42);
		cout << "EXIT GAME";
		_Common::gotoXY(100, 42);
		cout << "     ";
		_Common::TextColor(ColorCode_Red);

		switch (choose)
		{
			case 0: 
				_Common::gotoXY(100, 32);
				cout << ">>>> ";
				_Common::gotoXY(105, 32);
				cout << "NEW GAME";
				break;
			case 1:
				_Common::gotoXY(100, 34);
				cout << ">>>> ";
				_Common::gotoXY(105, 34);
				cout << "LOAD GAME";
				break;
			case 2:
				_Common::gotoXY(100, 36);
				cout << ">>>> ";
				_Common::gotoXY(105, 36);
				cout << "SETTING";
				break;
			case 3:
				_Common::gotoXY(100, 38);
				cout << ">>>> ";
				_Common::gotoXY(105, 38);
				cout << "ABOUT";
				break;
			case 4:
				_Common::gotoXY(100, 40);
				cout << ">>>> ";
				_Common::gotoXY(105, 40);
				cout << "HOW TO PLAY";
				break;
			case 5:
				_Common::gotoXY(100, 42);
				cout << ">>>> ";
				_Common::gotoXY(105, 42);
				cout << "EXIT GAME";
				break;
		}

		_Common::TextColor(ColorCode_DarkYellow);

		char key = -1;
		if (_kbhit()) key = toupper(_getch());
		switch (key)
		{
		case 27:
			choose = 5;
			break;
		case 'A': case 75:
			break;
		case 'W': case 72:
			choose--;
			break;
		case 'S': case 80:
			choose++;
			break;
		case 'D': case 77:
			break;
		case 13: case 32:
			check = false;
			switch (choose)
			{
			case 0:
				_Common::UnNocursortype();
				system("cls");
				g.Init(BOARD_SIZE, LEFT, TOP);
				_Common::setFontSize(30);
				_Common::gotoXY(50, 7);
				cout << "<< NEW GAME >>";
				if (options == true)
				{
					g.Turn(turn);
					_Common::gotoXY(40, 10);
					fflush(stdin);
					cout << "Player 1 : ";
					g.GetUser1().Input();
					_Common::gotoXY(40, 12);
					fflush(stdin);
					cout << "Player 2 : ";
					g.GetUser2().Input();
					_Common::setFontSize(16);
					g.startGame();
					g.SetTime(time);
					g.SetOptions(options);
					NewGame();

				}
				else
				{
					g.Turn(turn);
					_Common::gotoXY(40, 10);
					fflush(stdin);
					cout << "Player 1 : ";
					g.GetUser1().Input();
					g.GetUser2().SetName("CPU");
					_Common::setFontSize(16);
					g.startGame();
					g.SetTime(time);
					g.SetOptions(options);
					CPUGame();
				}
				Menu(0, options, turn, time);
				break;
			case 1:
				//Load Game
				LoadGame(options, turn, time);
				Menu(1, options, turn, time);
				break;
			case 2:
				system("cls");
				_Common::gotoXY(50, 7);
				cout << "<< SETTING >>";
				Options(options, turn, time);
				Menu(2, options, turn, time);
				break;
			case 3:
				system("cls");
				_Common::setFontSize(30);
				_Common::gotoXY(50, 7);
				cout << "<< ABOUT >>";
				_Common::gotoXY(40, 10);
				cout << "DESIGN: TEAM-8 HCMUS";
				_Common::gotoXY(40, 12);
				cout << "MEMBER:";
				_Common::gotoXY(40, 13);
				cout << "1 - TRAN VAN QUY PHUOC - 19127246";
				_Common::gotoXY(40, 14);
				cout << "2 - PHAM HONG QUAN     - 19127250";
				_Common::gotoXY(40, 15);
				cout << "3 - NGUYEN MANH HIEU   - 19127402";
				_Common::gotoXY(40, 16);
				cout << "4 - LUONG KIEM MINH    - 19127471";
				_Common::gotoXY(40, 18);
				cout << "RELEASE : 2020";
				_Common::gotoXY(40, 20);
				cout << "VERSION : CARO 1.0";
				_Common::gotoXY(40, 21);
				system("pause");
				_Common::setFontSize(16);
				Menu(3, options, turn, time);
				
				break;
			case 4:
				system("cls");
				_Common::setFontSize(30);
				_Common::gotoXY(45, 7);
				cout << "<< HOW TO PLAY >>";
				_Common::gotoXY(40, 10);
				cout << "A or LEFT KEY   : Move Left";
				_Common::gotoXY(40, 12);
				cout << "D or RIGHT KEY  : Move Right";
				_Common::gotoXY(40, 14);
				cout << "W or TOP KEY    : Move Top";
				_Common::gotoXY(40, 16);
				cout << "S or BOTTOM KEY : Move Bottom";
				_Common::gotoXY(40, 18);
				cout << "SPACE or ENTER  : Choose";
				_Common::gotoXY(40, 22);
				system("pause");
				_Common::setFontSize(16);
				Menu(4, options, turn, time);
				break;
			case 5:
				system("cls");
				_Common::gotoXY(50, 12);
				cout << "THANKS FOR USED !";
				_Common::gotoXY(50, 14);
				break;
			}
		}
		if (choose < 0) choose = 5;
		if (choose > 5) choose = 0;
		Sleep(50);
	}

}

void NewGame()
{
	double runtime = 0;
	bool init = true;
	bool turn = g.GetTurn();
	bool time = g.GetTime();
	bool options = g.GetOptions();
	g.SetLoop(true);
	int cur = -1;
	int* x = new int[BOARD_SIZE * BOARD_SIZE];
	int* y = new int[BOARD_SIZE * BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		x[i] = -1;
		y[i] = -1;
	}

	if (g.GetTime())
	{
		g.ShowTime();
	}

	while (g.isContinue())
	{
		// Xu ly time
		if (g.GetTime() && !init)
		{
			runtime += g.Runtime();
			if (runtime >= 1)
			{
				if (g.GetTurn())
					g.GetUser1().SetTime(g.GetUser1().GetTime() - runtime * TIME);
				else
					g.GetUser2().SetTime(g.GetUser2().GetTime() - runtime * TIME);
				runtime = 0;
				g.ShowTime();
			}

			int key = g.processFinishTime();
			switch (key)
			{
			case -1: case 1: case 0:
				if (g.askContinue() != 'Y') g.exitGame();
				else
				{
					system("cls");
					g.SetLoop(true);
					g.waitKeyBoard();
					g.GetUser1().InitStep();
					g.GetUser1().ResetTime();
					g.GetUser2().InitStep();
					g.GetUser2().ResetTime();
					g.SetX(LEFT);
					g.SetY(TOP);
					g.startGame();
					g.Turn(turn);
					NewGame();
					g.exitGame();
				}
			}
		}

		g.waitKeyBoard();
		if (g.getCommand() == 27) g.exitGame();
		else
		{
			switch (g.getCommand())
			{
			case 59:
				system("cls");
				g.Init(BOARD_SIZE, LEFT, TOP);
				g.startGame();
				g.GetUser1().ResetTime();
				g.GetUser2().ResetTime();
				g.Turn(turn);
				NewGame();
				break;
			case 60:
				_Common::UnNocursortype();
				Save("loadFile.txt", true, false);
				system("cls");
				g.ShowXO();
				_Common::gotoXY(g.GetX(), g.GetY());
				break;
			case 61:
				//Load File
				if (!LoadGame(options, turn, time))
				{
					_Common::UnNocursortype();
					system("cls");
					g.ShowXO();
					_Common::gotoXY(g.GetX(), g.GetY());
				}
				else g.exitGame();
				break;
			case 62:
				if (cur >= 0 && x[cur] >= 0 && y[cur] >= 0)
				{
					g.Undo(x[cur], y[cur]);
					x[cur] = -1;
					y[cur] = -1;
					cur--;
				}
				g.ShowInfor();
				break;
			case 'A': case 75:
				g.moveLeft();
				break;
			case 'W': case 72:
				g.moveUp();
				break;
			case 'S': case 80:
				g.moveDown();
				break;
			case 'D': case 77:
				g.moveRight();
				break;
			case 13: case 32:

				//Đánh dấu bàn cờ, sau đó kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (g.processCheckBoard())
				{
					cur++;
					x[cur] = g.GetX();
					y[cur] = g.GetY();

					if (g.GetTime() && init)
					{
						g.InitTime();
						init = !init;
					}

					if (g.GetTime() && !init)
					{
						runtime += g.Runtime();
						if (runtime >= 1)
						{
							if (g.GetTurn())
								g.GetUser1().SetTime(g.GetUser1().GetTime() - runtime * TIME);
							else
								g.GetUser2().SetTime(g.GetUser2().GetTime() - runtime * TIME);
							runtime = 0;
							g.ShowTime();
						}
					}

					int key = g.processFinish();
					switch (key)
					{
					case -1: case 1: case 0:
						if (g.askContinue() != 'Y') g.exitGame();
						else
						{
							system("cls");
							g.SetLoop(true);
							g.waitKeyBoard();
							g.GetUser1().InitStep();
							g.GetUser1().ResetTime();
							g.GetUser2().InitStep();
							g.GetUser2().ResetTime();
							g.SetX(LEFT);
							g.SetY(TOP);
							g.startGame();
							g.Turn(turn);
							NewGame();
							g.exitGame();
						}
					}
				}
				g.ShowInfor();
				break;
			}
		}
		//Sleep(50);
	}
}

void CPUGame()
{
	double runtime = 0;
	bool init = true;
	bool turn = g.GetTurn();
	bool time = g.GetTime();
	bool options = g.GetOptions();
	g.SetLoop(true);
	int cur = -1;
	int* x = new int[BOARD_SIZE * BOARD_SIZE];
	int* y = new int[BOARD_SIZE * BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		x[i] = -1;
		y[i] = -1;
	}

	if (g.GetTime())
	{
		g.ShowTime();
	}

	while (g.isContinue())
	{
		// Xu ly time
		if (g.GetTime() && !init)
		{
			runtime += g.Runtime();
			if (runtime >= 1)
			{
				if (g.GetTurn())
					g.GetUser1().SetTime(g.GetUser1().GetTime() - runtime * TIME);
				else
					g.GetUser2().SetTime(g.GetUser2().GetTime() - runtime * TIME);
				runtime = 0;
				g.ShowTime();
			}

			int key = g.processFinishTime();
			switch (key)
			{
			case -1: case 1: case 0:
				if (g.askContinue() != 'Y') g.exitGame();
				else
				{
					system("cls");
					//g.Init(BOARD_SIZE, LEFT, TOP);
					g.SetLoop(true);
					g.waitKeyBoard();
					g.GetUser1().InitStep();
					g.GetUser1().ResetTime();
					g.GetUser2().InitStep();
					g.GetUser2().ResetTime();
					g.SetX(LEFT);
					g.SetY(TOP);
					g.startGame();
					g.Turn(turn);
					CPUGame();
					g.exitGame();
				}
			}
		}
		if (g.GetTurn())
		{
			g.waitKeyBoard();
			if (g.getCommand() == 27) g.exitGame();
			else
			{
				switch (g.getCommand())
				{
				case 59:
					system("cls");
					g.Init(BOARD_SIZE, LEFT, TOP);
					g.startGame();
					g.GetUser1().ResetTime();
					g.GetUser2().ResetTime();
					g.Turn(turn);
					CPUGame();
					break;
				case 60:
					_Common::UnNocursortype();
					Save("loadFile.txt", true, false);
					system("cls");
					g.ShowXO();
					_Common::gotoXY(g.GetX(), g.GetY());
					break;
				case 61:
					//Load File
					
					if (!LoadGame(options, turn, time))
					{
						_Common::UnNocursortype();
						system("cls");
						g.ShowXO();
						_Common::gotoXY(g.GetX(), g.GetY());
					}
					else g.exitGame();
					
					break;

				case 62: //Undo
					if (cur >= 0 && x[cur] >= 0 && y[cur] >= 0)
					{
						g.Undo(x[cur], y[cur]);
						x[cur] = -1;
						y[cur] = -1;
						cur--;
					}

					if (cur >= 0 && x[cur] >= 0 && y[cur] >= 0)
					{
						g.Undo(x[cur], y[cur]);
						x[cur] = -1;
						y[cur] = -1;
						cur--;
					}

					g.ShowInfor();
					break;
				case 'A': case 75:
					g.moveLeft();
					break;
				case 'W': case 72:
					g.moveUp();
					break;
				case 'S': case 80:
					g.moveDown();
					break;
				case 'D': case 77:
					g.moveRight();
					break;
				case 13: case 32:

					//Đánh dấu bàn cờ, sau đó kiểm tra và xử lý thắng/thua/hòa/tiếp tục
					if (g.processCheckBoardCPU())
					{
						cur++;
						x[cur] = g.GetX();
						y[cur] = g.GetY();

						if (g.GetTime() && init)
						{
							g.InitTime();
							init = !init;
						}

						if (g.GetTime() && !init)
						{
							runtime += g.Runtime();
							if (runtime >= 1)
							{
								if (g.GetTurn())
									g.GetUser1().SetTime(g.GetUser1().GetTime() - runtime * TIME);
								else
									g.GetUser2().SetTime(g.GetUser2().GetTime() - runtime * TIME);
								runtime = 0;
								g.ShowTime();
							}
						}

						int key = g.processFinish();
						switch (key)
						{
						case -1: case 1: case 0:
							if (g.askContinue() != 'Y') g.exitGame();
							else
							{
								system("cls");
								//g.Init(BOARD_SIZE, LEFT, TOP);
								g.SetLoop(true);
								g.waitKeyBoard();
								g.GetUser1().InitStep();
								g.GetUser1().ResetTime();
								g.GetUser2().InitStep();
								g.GetUser2().ResetTime();
								g.SetX(LEFT);
								g.SetY(TOP);
								g.startGame();
								g.Turn(turn);
								CPUGame();
								g.exitGame();
							}
						}
					}
					g.ShowInfor();
					break;
				}

			}
		}
		else
		{
			//Đánh dấu bàn cờ, sau đó kiểm tra và xử lý thắng/thua/hòa/tiếp tục
			if (g.processCheckBoardCPU())
			{
				cur++;
				x[cur] = g.GetX();
				y[cur] = g.GetY();

				if (g.GetTime() && init)
				{
					g.InitTime();
					init = !init;
				}

				if (g.GetTime() && !init)
				{
					runtime += g.Runtime();
					if (runtime >= 1)
					{
						if (g.GetTurn())
							g.GetUser1().SetTime(g.GetUser1().GetTime() - runtime * TIME);
						else
							g.GetUser2().SetTime(g.GetUser2().GetTime() - runtime * TIME);
						runtime = 0;
						g.ShowTime();
					}
				}

				int key = g.processFinish();
				switch (key)
				{
				case -1: case 1: case 0:
					if (g.askContinue() != 'Y') g.exitGame();
					else
					{
						system("cls");
						//g.Init(BOARD_SIZE, LEFT, TOP);
						g.SetLoop(true);
						g.waitKeyBoard();
						g.GetUser1().InitStep();
						g.GetUser1().ResetTime();
						g.GetUser2().InitStep();
						g.GetUser2().ResetTime();
						g.SetX(LEFT);
						g.SetY(TOP);
						g.startGame();
						g.Turn(turn);
						CPUGame();
						g.exitGame();
					}
				}
			}
			g.ShowInfor();
		}
		//Sleep(50);
	}
}

void Options(bool& options, bool& turn, bool& time)
{
	bool check = true;
	int choose = 0;
	_Common::setFontSize(30);
	while (check)
	{
		_Common::gotoXY(40, 10);
		cout << "Mode\t\t: Player Vs " << ((options) ? "Player  " : "Computer");
		_Common::gotoXY(40, 12);
		cout << "First Player\t: Player " << ((turn) ? "1" : "2");
		_Common::gotoXY(40, 14);
		cout << "Go to back";


		_Common::TextColor(ColorCode_DarkYellow);

		switch (choose)
		{
		case 0:
			_Common::gotoXY(40, 10);
			cout << "Mode";
			break;
		case 1:
			_Common::gotoXY(40, 12);
			cout << "First Player";
			break;
		case 2:
			_Common::gotoXY(40, 14);
			cout << "Go to back";
			break;
		}

		_Common::TextColor(default_ColorCode);
		char key = -1;
		if (_kbhit()) key = toupper(_getch());
		switch (key)
		{
		case 27:
			choose = 2;
			break;
		case 'A': case 75: case 'D': case 77: case 13: case 32:
			if (choose == 0) options = !options;
			if (choose == 1) turn = !turn;
			if (choose == 2) check = false;
			break;
		case 'W': case 72:
			choose--;
			break;
		case 'S': case 80:
			choose++;
			break;
		}
		if (choose < 0) choose = 2;
		if (choose > 2) choose = 0;
		Sleep(50);
	}
	_Common::setFontSize(16);
}

bool LoadGame(bool& options, bool& turn, bool& time)
{
	string fileLoad = "";
	_Common::setFontSize(30);
	ShowLoadGame("loadFile.txt", fileLoad);
	_Common::setFontSize(16);
	if (fileLoad == "") return false;
	fstream f(fileLoad, ios::in | ios::out);
	if (!f.is_open())
	{
		_Common::gotoXY(45, 10);
		cout << "Don't open file to Load Game! Error!" << endl;
		return false;
	}
	int x, y, step, W, L, D, value, loop, time1, time2;
	string name;

	f >> options >> turn >> time >> x >> y >> loop;
	g.SetTime(time); g.SetOptions(options);
	f.seekg(2, ios::cur);

	getline(f, name); g.GetUser1().SetName(name);
	f >> step >> W >> L >> D >> time1;
	f.seekg(2, ios::cur);
	g.GetUser1().SetStep(step); g.GetUser1().SetWin(W); g.GetUser1().SetLose(L); g.GetUser1().SetDraw(D); g.GetUser1().SetTime(time1);

	getline(f, name); g.GetUser2().SetName(name);
	f >> step >> W >> L >> D >> time2;
	f.seekg(2, ios::cur);
	g.GetUser2().SetStep(step); g.GetUser2().SetWin(W); g.GetUser2().SetLose(L); g.GetUser2().SetDraw(D); g.GetUser2().SetTime(time2);



	for (int i = 0; i < g.GetBoard()->getSize(); i++)
	{
		for (int j = 0; j < g.GetBoard()->getSize(); j++)
		{
			f >> value;
			g.GetBoard()->Init(i, j, value);
		}
	}

	g.SetX(x);
	g.SetY(y);
	g.SetLoop(loop);
	g.Turn(turn);

	_Common::UnNocursortype();
	system("cls");
	g.ShowXO();
	_Common::gotoXY(g.GetX(), g.GetY());
	if (options) NewGame();
	else
	{
		CPUGame();
	}

	f.close();
	return true;
}

void ShowLoadGame(string filename, string& loadfile)
{
	_Common::Nocursortype();
	system("cls");
	_Common::gotoXY(50, 7);
	cout << "<< LOAD GAME >>";
	fstream f(filename, ios::in | ios::out);
	if (!f.is_open())
	{
		_Common::gotoXY(45, 10);
		cout << "Don't open file Load Game! Error!" << endl;
		return;
	}
	int n; f >> n;
	f.seekg(2, ios::cur);

	string* a = new string[n];

	for (int i = 0; i < n; i++)
	{
		getline(f, a[i]);
	}
	bool check = true;
	int choose = 0;

	while (check)
	{
		for (int i = 0; i < n; i++)
		{
			_Common::gotoXY(50, 10 + i * 2);
			cout << a[i];
		}

		_Common::gotoXY(50, 10 + n * 2 + 2);
		cout << "Go to back";

		_Common::TextColor(ColorCode_DarkYellow);

		for (int i = 0; i <= n; i++)
		{
			if (choose == i && i != n)
			{
				_Common::gotoXY(50, 10 + i * 2);
				cout << a[i];
				break;
			}

			if (choose == n)
			{
				_Common::gotoXY(50, 10 + n * 2 + 2);
				cout << "Go to back";
				break;
			}

		}

		_Common::TextColor(default_ColorCode);

		char key = -1;
		if (_kbhit()) key = toupper(_getch());
		switch (key)
		{
		case 27:
			choose = n;
			break;
		case 13: case 32:
			//xu ly
			if (choose == n) return;
			else
			{
				loadfile = a[choose];
				return;
			}
			break;
		case 'W': case 72:
			choose--;
			break;
		case 'S': case 80:
			choose++;
			break;
		}
		if (choose < 0) choose = n;
		if (choose > n) choose = 0;
		Sleep(50);

	}
	delete[] a;
	f.close();
}

void Save(string filename, bool options, bool time)
{
	fstream f(filename, ios::in | ios::out);
	if (!f.is_open())
	{
		_Common::gotoXY(45, 10);
		cout << "Don't open file to Save! Error!" << endl;
		return;
	}
	int n; f >> n;
	f.seekg(2, ios::cur);

	string* a = new string[n + 1];

	for (int i = 0; i < n; i++)
	{
		getline(f, a[i]);
	}
	string name;
	system("cls");
	_Common::gotoXY(55, 10);
	cout << "Save Game";

	_Common::gotoXY(40, 13);
	cout << "Enter the File name : ";
	cin >> name;
	name.append(".txt");
	bool check = true;
	bool tmp = true;
	while (check)
	{
		//kiem tra
		char key = -1;
		for (int i = 0; i < n; i++)
		{
			if (a[i].compare(name) == 0)
			{
				_Common::gotoXY(40, 15);
				cout << "File is Exist. Do you want Replace it ?";
				_Common::gotoXY(40, 17);
				cout << "Yes[Y]  or  No[N/press any key]";
				_Common::gotoXY(45, 19);
				cout << "You Choice: ";
				key = toupper(_getch());
				if (key == 'Y') tmp = false;
				break;
			}
		}
		if (key != 'Y' && key != -1) check = true;
		else check = false;
	}

	if (tmp)
	{
		a[n] = name;
		n = n + 1;
	}
	f.close();

	fstream fsave(filename, ios::out);

	if (!fsave.is_open())
	{
		_Common::gotoXY(45, 10);
		cout << "Don't open file to Save! Error!" << endl;
		return;
	}

	fsave << n << endl;
	for (int i = 0; i < n; i++)
	{
		fsave << a[i] << endl;
	}
	fsave.close();

	fstream fload(name, ios::out);

	if (!fload.is_open())
	{
		_Common::gotoXY(45, 10);
		cout << "Don't open file to Save! Error!" << endl;
		return;
	}

	fload << g.GetOptions() << " " << g.GetTurn() << " " << g.GetTime() << " " << g.GetX() << " " << g.GetY() << " " << g.GetLoop() << endl;
	fload << g.GetUser1().GetName() << endl;
	fload << g.GetUser1().GetStep() << " " << g.GetUser1().GetWin() << " " << g.GetUser1().GetLose() << " " << g.GetUser1().GetDraw() << " " << g.GetUser1().GetTime() << endl;

	fload << g.GetUser2().GetName() << endl;
	fload << g.GetUser2().GetStep() << " " << g.GetUser2().GetWin() << " " << g.GetUser2().GetLose() << " " << g.GetUser2().GetDraw() << " " << g.GetUser2().GetTime() << endl;


	for (int i = 0; i < g.GetBoard()->getSize(); i++)
	{
		for (int j = 0; j < g.GetBoard()->getSize(); j++)
		{
			fload << g.GetBoard()->GetXO(i, j) << " ";
		}
	}

	fload.close();

	delete[] a;
}
