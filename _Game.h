#pragma once
#include "_Board.h"
#include "_Common.h"
#include "_Player.h"
#include <conio.h>


class _Game
{
private:
	Player user1;
	Player user2;
	bool _time;
	_Board* _b;// một bàn cờ
	bool _turn;// lượt chơi: true lượt người một & false lượt người thứ hai
	int _x, _y; // Tọa độ hiện hành của nháy chuột
	int _command; // phím gõ từ người dùng
	bool _loop; // Biến quyết định thoát game hay 60hông
	clock_t _t;
	bool _options;

public:
	int getCommand();
	bool isContinue();
	char waitKeyBoard(); // Hàm nhận phím từ người dùng
	char askContinue();
	void startGame(); // Hàm bắt đầu game
	void exitGame(); // Hàm thoát game
	int processFinish();
	bool processCheckBoard();
	bool processCheckBoardCPU();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void ShowInfor();
	void ShowTime();
	Player& GetUser1() { return user1; }
	Player& GetUser2() { return user2; }
	void Turn(bool value) { _turn = value; }
	bool GetTurn() { return _turn; }
	void Init(int, int, int);
	void Undo(int, int);
	int GetX() { return _x; }
	void SetX(int value) { _x = value; }
	int GetY() { return _y; }
	void SetY(int value) { _y = value; }
	void ShowXO();
	_Board* GetBoard() { return _b; }
	void SetLoop(bool value) { _loop = value; }
	bool GetLoop() { return _loop; }
	void SetTime(bool value) { _time = value; }
	bool GetTime() { return _time; }
	double Runtime();
	void InitTime();
	int processFinishTime();
	void SetOptions(bool value) { _options = value; }
	bool GetOptions() { return _options; }
	void ShowWin(int);
	void DrawLineWin(int, int);
	void DrawFireWorks(int, int, int);

public:
	_Game(int, int, int);
	~_Game();
};



_Game::_Game(int pSize, int pLeft, int pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_loop = true;
	_command = -1; // Gán lượt và phím mặc định
	_x = pLeft; _y = pTop;
	user1.SetLose(0);
	user1.SetWin(0);
	user1.SetDraw(0);
	user2.SetLose(0);
	user2.SetWin(0);
	user2.SetDraw(0);
}

_Game::~_Game() { delete _b; }

void _Game::Init(int pSize, int pLeft, int pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_loop = true;
	_command = -1; // Gán lượt và phím mặc định
	_x = pLeft; _y = pTop;
	user1.SetLose(0);
	user1.SetWin(0);
	user1.SetDraw(0);
	user2.SetLose(0);
	user2.SetWin(0);
	user2.SetDraw(0);
	user1.InitStep();
	user2.InitStep();
	_options = true;
}

int _Game::getCommand() { return _command; }

bool _Game::isContinue() { return _loop; }

double _Game::Runtime()
{
	clock_t tmp = clock();
	double res = double(tmp - _t) / CLOCKS_PER_SEC;
	_t = tmp;
	return res;
}

// Trả về số tích tắc đồng hồ đã trôi qua từ khi chương trình được chạy
void _Game::InitTime()
{
	_t = clock();
}

char _Game::waitKeyBoard()
{
	if (_kbhit()) _command = toupper(_getch());
	else _command = NULL;
	return _command;
}

char _Game::askContinue()
{
	return _command;
}

void _Game::startGame()
{
	system("cls");
	//system("Color F1");
	_b->resetData();
	ShowInfor();
	_b->drawBoard(); // Vẽ màn hình game
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
}

void _Game::exitGame()
{
	system("cls");
	//Có thể lưu game trước khi exit
	_loop = false;
}

void _Game::ShowXO()
{
	_command = -1;
	_b->drawBoard();
	ShowInfor();

	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			_Common::gotoXY(j * 4 + _b->getLeft() + 2, i * 2 + _b->getTop() + 1);
			switch (_b->GetXO(i, j))
			{
			case -1:
				_Common::TextColor(ColorCode_Green + default_Background);
				cout << "X";
				_Common::TextColor(default_ColorCode + default_Background);
				break;
			case 1:
				_Common::TextColor(ColorCode_Yellow + default_Background);
				cout << "O";
				_Common::TextColor(default_ColorCode + default_Background);
				break;
			case 0:
				break;
			}
		}
	}
}

bool _Game::processCheckBoard()
{
	switch (_b->checkBoard(_x, _y, _turn))
	{
	case -1:
		_Common::gotoXY(_x, _y);
		user1.IncreStep();
		_Common::TextColor(ColorCode_Green + default_Background);
		printf("X");
		_Common::TextColor(default_ColorCode + default_Background);
		break;
	case 1:
		_Common::gotoXY(_x, _y);
		user2.IncreStep();
		_Common::TextColor(ColorCode_Yellow + default_Background);
		printf("O");
		_Common::TextColor(default_ColorCode + default_Background);
		break;
	case 0:
		return false; // Khi đánh vào ô đã đánh rồi
	}
	return true;
}

bool _Game::processCheckBoardCPU()
{
	switch (_b->checkBoardCPU(_x, _y, _turn))
	{
	case -1:
		_Common::gotoXY(_x, _y);
		user1.IncreStep();
		_Common::TextColor(ColorCode_Green + default_Background);
		printf("X");
		_Common::TextColor(default_ColorCode + default_Background);
		break;
	case 1:
		_Common::gotoXY(_x, _y);
		user2.IncreStep();
		_Common::TextColor(ColorCode_Yellow + default_Background);
		printf("O");
		_Common::TextColor(default_ColorCode + default_Background);
		break;
	case 0:
		return false; // Khi đánh vào ô đã đánh rồi
	}
	return true;
}

void _Game::Undo(int x, int y)
{
	_Common::TextColor(default_ColorCode + default_Background);
	_Common::gotoXY(x, y);
	switch (_b->Undo(x, y))
	{
	case -1:
		printf(" ");
		user1.DecreStep();
		_turn = !_turn;
		break;
	case 1:
		printf(" ");
		user2.DecreStep();
		_turn = !_turn;
		break;
	case 0:
		printf(" ");
		break;
	}
}

void _Game::DrawLineWin(int x, int y)
{
	int i = 0;
	int count = 0;
	while (x + i < _b->getSize() && _b->GetXO(x, y) == _b->GetXO(x + i, y))
	{
		count++;
		i++;
	}
	if (count >= 5)
	{
		for (int j = 0; j < count; j++)
		{
			_Common::gotoXY(y * 4 + _b->getLeft() + 2, (x + j) * 2 + _b->getTop() + 1);
			cout << ((_b->GetXO(x + j, y) == 1) ? "O" : "X");
		}
		return;
	}


	i = 0; count = 0;
	while (y + i < _b->getSize() && _b->GetXO(x, y) == _b->GetXO(x, y + i))
	{
		count++;
		i++;
	}
	if (count >= 5)
	{
		for (int j = 0; j < count; j++)
		{
			_Common::gotoXY((y + j) * 4 + _b->getLeft() + 2, x * 2 + _b->getTop() + 1);
			cout << ((_b->GetXO(x, y + j) == 1) ? "O" : "X");
		}
		return;
	}

	i = 0; count = 0;
	while (x + i < _b->getSize() && y + i < _b->getSize() && _b->GetXO(x, y) == _b->GetXO(x + i, y + i))
	{
		count++;
		i++;
	}
	if (count >= 5)
	{
		for (int j = 0; j < count; j++)
		{
			_Common::gotoXY((y + j) * 4 + _b->getLeft() + 2, (x + j) * 2 + _b->getTop() + 1);
			cout << ((_b->GetXO(x + j, y + j) == 1) ? "O" : "X");
		}
		return;
	}

	i = 0; count = 0;
	while (x - i >= 0 && y + i < _b->getSize() && _b->GetXO(x, y) == _b->GetXO(x - i, y + i))
	{
		count++;
		i++;
	}
	if (count >= 5)
	{
		for (int j = 0; j < count; j++)
		{
			_Common::gotoXY((y + j) * 4 + _b->getLeft() + 2, (x - j) * 2 + _b->getTop() + 1);
			cout << ((_b->GetXO(x - j, y + j) == 1) ? "O" : "X");
		}
		return;
	}
}

void _Game::DrawFireWorks(int key, int x, int y)
{
	switch (key)
	{
	case 0:
		_Common::gotoXY(x, y + 10);
		cout << "|";
		break;
	case 1:
		_Common::gotoXY(x, y + 10);
		cout << " ";
		_Common::gotoXY(x, y + 9);
		cout << "|";
		break;
	case 2:
		_Common::gotoXY(x, y + 9);
		cout << " ";
		_Common::gotoXY(x, y + 8);
		cout << "|";
		break;
	case 3:
		_Common::gotoXY(x, y + 8);
		cout << " ";
		_Common::gotoXY(x, y + 7);
		cout << "|";
		break;
	case 4:
		_Common::gotoXY(x, y + 7);
		cout << " ";
		_Common::gotoXY(x, y + 6);
		cout << "|";
		break;
	case 5:
		_Common::gotoXY(x, y + 6);
		cout << " ";
		_Common::gotoXY(x, y + 5);
		cout << "|";
		break;
	case 6:
		_Common::gotoXY(x, y + 5);
		cout << " ";
		_Common::gotoXY(x, y + 4);
		cout << "|";
		break;
	case 7:
		_Common::gotoXY(x, y + 4);
		cout << " ";
		_Common::gotoXY(x, y + 3);
		cout << "|";
		break;
	case 8:
		_Common::gotoXY(x, y + 3);
		cout << " ";
		_Common::gotoXY(x, y + 2);
		cout << "|";
		break;
	case 9:
		_Common::gotoXY(x, y + 0);
		cout << " ";
		_Common::gotoXY(x, y + 1);
		cout << "|";
		break;
	case 10:
		_Common::gotoXY(x - 6, y - 3);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 1);
		cout << "         	  ";
		_Common::gotoXY(x - 6, y);
		cout << "      *      ";
		_Common::gotoXY(x - 6, y + 1);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 3);
		cout << "             ";
		break;
	case 11:
		_Common::gotoXY(x - 6, y - 3);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 1);
		cout << "      *  	 ";
		_Common::gotoXY(x - 6, y);
		cout << "    * * *    ";
		_Common::gotoXY(x - 6, y + 1);
		cout << "      *      ";
		_Common::gotoXY(x - 6, y + 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 3);
		cout << "             ";
		break;
	case 12:
		_Common::gotoXY(x - 6, y - 3);
		cout << "      *      ";
		_Common::gotoXY(x - 6, y - 2);
		cout << "  *   *   *  ";
		_Common::gotoXY(x - 6, y - 1);
		cout << "    *   *	 ";
		_Common::gotoXY(x - 6, y);
		cout << "* *       * *";
		_Common::gotoXY(x - 6, y + 1);
		cout << "    *   *    ";
		_Common::gotoXY(x - 6, y + 2);
		cout << "  *   *   *  ";
		_Common::gotoXY(x - 6, y + 3);
		cout << "      *      ";
		break;
	case 13:
		_Common::gotoXY(x - 6, y - 3);
		cout << "      *      ";
		_Common::gotoXY(x - 6, y - 2);
		cout << "  *       *  ";
		_Common::gotoXY(x - 6, y - 1);
		cout << "             ";
		_Common::gotoXY(x - 6, y);
		cout << "*           *";
		_Common::gotoXY(x - 6, y + 1);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 2);
		cout << "  *       *  ";
		_Common::gotoXY(x - 6, y + 3);
		cout << "      *      ";
		break;
	case 14:
		_Common::gotoXY(x - 6, y - 3);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y - 1);
		cout << "             ";
		_Common::gotoXY(x - 6, y);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 1);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 2);
		cout << "             ";
		_Common::gotoXY(x - 6, y + 3);
		cout << "             ";
		break;
	}
}

void _Game::ShowWin(int win)
{
	char key = -1;
	int count = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int step = 0;
	string name = "";

	_Common::Nocursortype();

	for (int i = 0; i < 50; i++)
	{
		_Common::gotoXY(110, i);
		for (int j = 0; j < 100; j++) cout << " ";
	}

	while (key == -1)
	{
		_Common::Nocursortype();

		_Common::TextColor(rand() % 15 + 1);
		DrawLineWin(_x, _y);
		_Common::TextColor(default_ColorCode);
		int x = 150, y = 19;
		//FireWorks
		if (step >= 0)
		{
			_Common::TextColor(rand() % 15 + 1);
			DrawFireWorks(count % 15, x, y);
			x = 185; y = 35;
			DrawFireWorks(count4 % 15, x, y);
			x = 195; y = 36;
			DrawFireWorks(count4 % 15, x, y);
			_Common::TextColor(default_ColorCode);
			count++;
		}

		if (step >= 5)
		{
			_Common::TextColor(rand() % 15 + 1);
			x = 170; y = 19;
			DrawFireWorks(count1 % 15, x, y);
			x = 160; y = 21;
			DrawFireWorks(count1 % 15, x, y);
			x = 145; y = 32;
			DrawFireWorks(count4 % 15, x, y);
			x = 115; y = 38;
			DrawFireWorks(count4 % 15, x, y);
			_Common::TextColor(default_ColorCode);
			count1++;
		}

		if (step >= 8)
		{
			_Common::TextColor(rand() % 15 + 1);
			x = 130; y = 19;
			DrawFireWorks(count2 % 15, x, y);
			_Common::TextColor(rand() % 15 + 1);
			x = 160; y = 22;
			DrawFireWorks(count2 % 15, x, y);
			x = 135; y = 35;
			DrawFireWorks(count4 % 15, x, y);
			x = 125; y = 40;
			DrawFireWorks(count4 % 15, x, y);
			_Common::TextColor(default_ColorCode);
			count2++;
		}
		if (step >= 11)
		{
			_Common::TextColor(rand() % 15 + 1);
			x = 120; y = 19;
			DrawFireWorks(count3 % 15, x, y);
			x = 180; y = 23;
			DrawFireWorks(count3 % 15, x, y);
			x = 150; y = 24;
			DrawFireWorks(count3 % 15, x, y);
			x = 155; y = 25;
			DrawFireWorks(count3 % 15, x, y);
			x = 140; y = 26;
			DrawFireWorks(count1 % 15, x, y);
			_Common::TextColor(default_ColorCode);
			count3++;
		}

		if (step >= 14)
		{
			_Common::TextColor(rand() % 15 + 1);
			x = 110; y = 19;
			DrawFireWorks(count4 % 15, x, y);
			x = 150; y = 27;
			DrawFireWorks(count4 % 15, x, y);
			x = 155; y = 28;
			DrawFireWorks(count4 % 15, x, y);
			x = 140; y = 29;
			DrawFireWorks(count4 % 15, x, y);
			x = 125; y = 31;
			DrawFireWorks(count4 % 15, x, y);
			x = 185; y = 37;
			DrawFireWorks(count4 % 15, x, y);
			_Common::TextColor(default_ColorCode);
			count4++;
		}

		step++;
		_Common::TextColor(rand() % 15 + 1);
		_Common::gotoXY(125, 3);
		for (int i = 0; i <= 50; i++)
		{
			if (i == 0) putchar(201);
			else if (i == 50) putchar(187);
			else putchar(205);
		}

		for (int i = 1; i <= 10; i++)
		{
			_Common::gotoXY(125, i + 3); putchar(186);
			_Common::gotoXY(175, i + 3); putchar(186);
		}

		_Common::gotoXY(125, 13);
		for (int i = 0; i <= 50; i++)
		{
			if (i == 0) putchar(200);
			else if (i == 50) putchar(188);
			else putchar(205);
		}
		_Common::TextColor(default_ColorCode);
		if (win == -1) name = user1.GetName();
		else if (win == 1) name = user2.GetName();
		else
		{
			_Common::gotoXY(131, 5);
			cout << " " << user1.GetName() << " AND " << user2.GetName() << " DRAW ! ";
			_Common::gotoXY(131, 7);
			cout << "Yes [ Press 'Y'       ]   : New Game";
			_Common::gotoXY(131, 9);
			cout << "No  [ N/press any key ]   : Back to Menu";
			_Common::gotoXY(131, 11);
			cout << "You Choose: ";

			if (_kbhit())
			{
				key = getchar();
				cin.ignore();
				_command = toupper(key);
			}
			return;
		}
		_Common::gotoXY(131, 5);
		cout << " CONGRATULATION " << name << " IS THE WINNER ! ";
		_Common::gotoXY(131, 7);
		cout << "Yes [ Press 'Y'       ]   : New Game";
		_Common::gotoXY(131, 9);
		cout << "No  [ N/press any key ]   : Back to Menu";
		_Common::gotoXY(131, 11);
		cout << "You Choose: ";

		_Common::UnNocursortype();

		if (_kbhit())
		{
			key = getchar();
			cin.ignore();
			_command = toupper(key);
		}
		Sleep(100);
	}
}

int _Game::processFinish()
{
	char key = ' ';
	int pWhoWin = _b->testBoard(_x, _y);

	if (user1.GetTime() <= 0) pWhoWin = 1;
	if (user2.GetTime() <= 0) pWhoWin = -1;

	switch (pWhoWin)
	{
	case -1:
		user1.IncreWin();
		user2.IncreLose();
		ShowWin(-1);
		break;
	case 1:
		user2.IncreWin();
		user1.IncreLose();
		ShowWin(1);
		break;
	case 0:
		user1.IncreDraw();
		user2.IncreDraw();
		ShowWin(0);
		break;
	case 2:
		_turn = !_turn; // Đổi lượt nếu không có gì xảy ra
	}
	_Common::gotoXY(_x, _y);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}

int _Game::processFinishTime()
{
	char key = ' ';
	int pWhoWin = 2;

	if (user1.GetTime() <= 0) pWhoWin = 1;
	if (user2.GetTime() <= 0) pWhoWin = -1;

	switch (pWhoWin)
	{
	case -1:
		user1.IncreWin();
		user2.IncreLose();
		ShowWin(-1);
		break;
	case 1:
		user2.IncreWin();
		user1.IncreLose();
		ShowWin(1);
		break;
	case 0:
		user1.IncreDraw();
		user2.IncreDraw();
		ShowWin(0);

		break;
	case 2:
		break;
	}
	_Common::gotoXY(_x, _y);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}

void _Game::ShowInfor()
{
	_Common::TextColor(ColorCode_DarkYellow);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 48, 19);
	cout << "<< INFORMATION >>";
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 21);
	cout << "Player 1: " << user1.GetName() << "\t Step: " << user1.GetStep() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 22);
	cout << "WIN : " << user1.GetWin() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 23);
	cout << "LOSE: "  << user1.GetLose() << endl; 
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 24);
	cout << "DRAW: "  << user1.GetDraw() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 28);
	cout << "Player 2: " << user2.GetName() << "\t Step: " << user2.GetStep() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 29);
	cout << "WIN : " << user2.GetWin() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 30);
	cout << "LOSE: " << user2.GetLose() << endl;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 35, 31);
	cout << "DRAW: " << user2.GetDraw() << endl;
	_Common::gotoXY(_x, _y);
}

void _Game::ShowTime()
{
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 20, 25);
	cout << "Time\t: ";
	for (int i = 0; i < user1.GetTime() / 60; i++) putchar(219);
	for (int i = user1.GetTime() / 60; i < 30; i++) putchar(' ');

	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 20, 32);
	cout << "Time\t: ";
	for (int i = 0; i < user2.GetTime() / 60; i++) putchar(219);
	for (int i = user2.GetTime() / 60; i < 30; i++) putchar(' ');

	_Common::gotoXY(_x, _y);
}

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_x += 4;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0))
	{
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}