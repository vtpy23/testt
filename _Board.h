#pragma once
#include "_Point.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "_Common.h"
#include <random>
#include <time.h>

using namespace std;

struct Move
{
	int row, col;
};

class _Board {
	int _size;
	int _left, _top;
	_Point** _pArr;
public:
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int testBoard(int&, int&);
	int Undo(int, int);
	int GetXO(int, int);
	void Init(int, int, int);
	int checkBoardCPU(int&, int&, bool);
	void CPU(int&, int&);
	void Minimax(int&, int&);



private:

	long long TC_Dong(int, int);
	long long TC_Cot(int, int);
	long long TC_CheoXuoi(int, int);
	long long TC_CheoNguoc(int, int);

	long long PT_Dong(int, int);
	long long PT_Cot(int, int);
	long long PT_CheoXuoi(int, int);
	long long PT_CheoNguoc(int, int);

	//Mimimax
	bool isMovesLeft();
	int evaluate();
	int minimax(int depth, bool isMax);
	Move findBestMove();


public:
	_Board();
	_Board(int, int, int);
	~_Board();
};

long long attack[7] = { 0, 9, 54, 162, 1458, 13112, 118008 };
long long defense[7] = { 0, 3, 27, 99, 729, 6561, 59049 };

int _Board::getSize() {
	return _size;
}

int _Board::getLeft() { 
	return _left; 
}

int _Board::getTop() { 
	return _top; 
}

int _Board::getXAt(int i, int j) { 
	return _pArr[i][j].getX(); 
}

int _Board::getYAt(int i, int j) { 
	return _pArr[i][j].getY(); 
}

_Board::_Board()
{
	_size = 0;
	_left = 0;
	_top = 0;
	_pArr = NULL;
}

_Board::_Board(int pSize, int pX, int pY)
{
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point * [pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}

_Board::~_Board()
{

	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}

void _Board::resetData()
{
	if (_size == 0) return; // Phải gọi constructor trước khi resetData
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_pArr[i][j].setX(4 * j + _left + 2); // Trùng với hoành độ màn hình bàn cờ
			_pArr[i][j].setY(2 * i + _top + 1); // Trùng với tung độ màn hình bàn cờ
			_pArr[i][j].setCheck(0);
		}
	}
}

int _Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
			{
				if (pTurn) _pArr[i][j].setCheck(-1);// Nếu lượt hiện hành là true: c = -1
				else _pArr[i][j].setCheck(1);// Nếu lượt hiện hành là false: c = 1
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

void _Board::Init(int i, int j, int value)
{
	if (_size == 0) return; // Phải gọi constructor trước khi resetData

	_pArr[i][j].setX(4 * j + _left + 2); // Trùng với hoành độ màn hình bàn cờ
	_pArr[i][j].setY(2 * i + _top + 1); // Trùng với tung độ màn hình bàn cờ
	_pArr[i][j].setCheck(value);
}

void _Board::drawBoard()
{
	_Common::TextColor(ColorCode_DarkYellow);
	if (_pArr == NULL) return; // phải gọi constructor trước

	_Common::gotoXY(0, 0);
	for (int i = 0; i <= _left + 4 * _size + 1; i++)
	{
		if (i == 0) putchar(201);
		else if (i == _left + 4 * _size + 1) putchar(187);
		else putchar(205);

	}
	for (int i = 1; i <= _top + 2 * _size; i++)
	{
		_Common::gotoXY(0, i); putchar(186);
		_Common::gotoXY(_left + 4 * _size + 1, i); putchar(186);
	}
	_Common::gotoXY(0, _top + 2 * _size + 1);
	for (int i = 0; i <= _left + 4 * _size + 1; i++)
	{
		if (i == 0) putchar(200);
		else if (i == _left + 4 * _size + 1) putchar(188);
		else putchar(205);

	}
	for (int i = 0; i <= _size; i++)
	{
		for (int j = 0; j <= _size; j++)
		{
			_Common::gotoXY(_left + 4 * i, _top + 2 * j);
			cout << ".";
		}
	}

	// thiet ke giao dien
	_Common::TextColor(ColorCode_Green);
	_Common::gotoXY(_left + 4 * _size + 15, 1);
	cout << "XXX     XXX     OOOOOOO         XXXXXXX       OOO       XX         XX  OOOOOOOOOO";
	_Common::gotoXY(_left + 4 * _size + 15, 2);
	cout << " XXX   XXX     OOO   OOO       XX     XX     0OOOO      XX XX   XX XX  00";
	_Common::gotoXY(_left + 4 * _size + 15, 3);
	cout << "  XXX XXX      OOO   OOO   X   XX           OO   OO     XX  XX XX  XX  00";
	_Common::gotoXY(_left + 4 * _size + 15, 4);
	cout << "   XXXXX       OOO   OOO  O O  XX    XXXX  OOOOOOOO0    XX   XXX   XX  0000000000";
	_Common::gotoXY(_left + 4 * _size + 15, 5);
	cout << "  XXX XXX      OOO   OOO   X   XX     XX  00       OO   XX         XX  00";
	_Common::gotoXY(_left + 4 * _size + 15, 6);
	cout << " XXX   XXX     OOO   OOO       XX     XX OO         OO  XX         XX  00";
	_Common::gotoXY(_left + 4 * _size + 15, 7);
	cout << "XXX     XXX     OOOOOOO         XXXXXXX 00           OO XX         XX  0000000000";
	
	_Common::TextColor(ColorCode_Red);
	_Common::gotoXY(_left + 4 * _size + 37, 11);
	cout << "F1 : New Game";
	_Common::gotoXY(_left + 4 * _size + 37, 13);
	cout << "F2 : Save Game";
	_Common::gotoXY(_left + 4 * _size + 57, 11);
	cout << "F3 : Load Game";
	_Common::gotoXY(_left + 4 * _size + 57, 13);
	cout << "F4 : Undo Step";
	_Common::gotoXY(_left + 4 * _size + 46, 15);
	cout << "ESC: Return Menu!";

	_Common::TextColor(ColorCode_Red);
	_Common::gotoXY(_left + 4 * _size + 10, 0);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(201);
		else if (i == _left + 4 * _size + 100) putchar(187);
		else putchar(205);
	}
	for (int i = 1; i <= 8; i++)
	{
		_Common::gotoXY(_left + 4 * _size + 10, i); putchar(186);
		_Common::gotoXY(_left + 4 * _size + 100, i); putchar(186);
	}
	_Common::gotoXY(_left + 4 * _size + 10, 8);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(200);
		else if (i == _left + 4 * _size + 100) putchar(188);
		else putchar(205);
	}

	_Common::TextColor(ColorCode_Blue);
	_Common::gotoXY(_left + 4 * _size + 10, 10);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(201);
		else if (i == _left + 4 * _size + 100) putchar(187);
		else putchar(205);
	}
	for (int i = 11; i <= 16; i++)
	{
		_Common::gotoXY(_left + 4 * _size + 10, i); putchar(186);
		_Common::gotoXY(_left + 4 * _size + 100, i); putchar(186);
	}
	_Common::gotoXY(_left + 4 * _size + 10, 17);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(200);
		else if (i == _left + 4 * _size + 100) putchar(188);
		else putchar(205);
	}

	_Common::TextColor(ColorCode_DarkGreen);
	_Common::gotoXY(_left + 4 * _size + 10, 18);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(201);
		else if (i == _left + 4 * _size + 100) putchar(187);
		else putchar(205);
	}
	for (int i = 19; i <= 33; i++)
	{
		_Common::gotoXY(_left + 4 * _size + 10, i); putchar(186);
		_Common::gotoXY(_left + 4 * _size + 100, i); putchar(186);
	}
	_Common::gotoXY(_left + 4 * _size + 10, 33);
	for (int i = _left + 4 * _size + 10; i <= _left + 4 * _size + 100; i++)
	{
		if (i == _left + 4 * _size + 10) putchar(200);
		else if (i == _left + 4 * _size + 100) putchar(188);
		else putchar(205);
	}

	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY());// di chuyển vào ô đầu
}


// Lấy giá trị tại ô [x,y]
int _Board::GetXO(int x, int y)
{
	return _pArr[x][y].getCheck();
}

// Cho phép người chơi đi lại
int _Board::Undo(int pX, int pY)
{
	int res;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() != 0)
			{
				res = _pArr[i][j].getCheck();
				_pArr[i][j].setCheck(0);
				return res;
			}
		}
	}
	return 0;
}

int _Board::testBoard(int& pX, int& pY)
{
	// Xu ly hoa
	// Khi tất cả các ô trong bàn cờ đều có giá trị là -1 hoặc 1 => Hết ô (check = true)
	// Nếu vẫn còn ô chứa giá trị là 0 => false và tiếp tục đánh
	// Neu danh het tat ca cac o cua ban co => HOA
	bool check = true;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getCheck() == 0)
			{
				check = false;
				break;
			}
		}
	}
	if (check) return 0;

	//Xu ly thang/thua
	int x, y = 0;

	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
			{
				x = i;
				y = j;
				break;
			}
		}
	}

	//res dùng để lưu điểm để kiểm tra xem người chơi đã có đủ 5 nút liên tiếp hay chưa
	int res = 0;

	// đặt điểm bắt đầu kiểm tra
	// nêu điểm nằm ở viền trên thì bắt đầu tại giá trị 0
	// nếu điểm không nằm ở viền thì bắt đầu tại điểm lùi về sau điểm nhận vào 4 điểm
	int xStart = (x - 4 > 0) ? x - 4 : 0;
	int yStart = (y - 4 > 0) ? y - 4 : 0;

	// đặt điểm kết thúc kiểm tra
	// nêu điểm nằm ở viền trên thì bắt đầu tại giá trị _size - 1
	int xEnd = (x + 4 >= _size) ? _size - 1 : x + 4;
	int yEnd = (y + 4 >= _size) ? _size - 1 : y + 4;

	int x1, x2, y1, y2;

	for (int i = xStart; i <= x; i++)
	{
		if (i + 4 < _size)
		{
			// tính tổng trên cột
			res = _pArr[i][y].getCheck() + _pArr[i + 1][y].getCheck() + _pArr[i + 2][y].getCheck()
				+ _pArr[i + 3][y].getCheck() + _pArr[i + 4][y].getCheck();

			// lưu giá trị x y của điểm nằm sau điểm đang kiểm tra
			x1 = i - 1 >= 0 ? i - 1 : xStart;
			y1 = y;
			// lưu giá trị x y của điểm nằm trước cách điểm đang kiểm tra 5 ô
			x2 = i + 5 >= _size ? x + 4 : i + 5;
			y2 = y;
		}

		if (res == 5 && (_pArr[x1][y1].getCheck() != -1 || _pArr[x2][y2].getCheck() != -1))
		{
			pX = i;
			pY = y;
			return 1;
		}
		if (res == -5 && (_pArr[x1][y1].getCheck() != 1 || _pArr[x2][y2].getCheck() != 1))
		{
			pX = i;
			pY = y;
			return -1;
		}
	}

	for (int i = yStart; i <= y; i++)
	{
		if (i + 4 < _size)
		{
			// tính tổng trên dòng
			res = _pArr[x][i].getCheck() + _pArr[x][i + 1].getCheck() + _pArr[x][i + 2].getCheck()
				+ _pArr[x][i + 3].getCheck() + _pArr[x][i + 4].getCheck();

			x1 = x;
			y1 = i - 1 >= 0 ? i - 1 : yStart;

			x2 = x;
			y2 = i + 5 >= _size ? y + 4 : i + 5;
		}

		if (res == 5 && (_pArr[x1][y1].getCheck() != -1 || _pArr[x2][y2].getCheck() != -1))
		{
			pX = x;
			pY = i;
			return 1;
		}
		if (res == -5 && (_pArr[x1][y1].getCheck() != 1 || _pArr[x2][y2].getCheck() != 1))
		{
			pX = x;
			pY = i;
			return -1;
		}
	}

	for (int i = xStart; i <= x; i++)
	{
		for (int j = yStart; j <= y; j++)
		{
			if (i - j == x - y && i + 4 < _size && j + 4 < _size)
			{
				// tính tổng trên đường chéo chính
				res = _pArr[i][j].getCheck() + _pArr[i + 1][j + 1].getCheck() + _pArr[i + 2][j + 2].getCheck()
					+ _pArr[i + 3][j + 3].getCheck() + _pArr[i + 4][j + 4].getCheck();
				x1 = i - 1;
				y1 = j - 1;
				if (x1 < 0 || y1 < 0)
				{
					x1 = i;
					y1 = j;
				}
				x2 = i + 5;
				y2 = j + 5;
				if (x2 >= _size || y2 >= _size)
				{
					y2 = j;
					x2 = i;
				}
			}

			if (res == 5 && (_pArr[x1][y1].getCheck() != -1 || _pArr[x2][y2].getCheck() != -1))
			{
				pX = i;
				pY = j;
				return 1;
			}
			if (res == -5 && (_pArr[x1][y1].getCheck() != 1 || _pArr[x2][y2].getCheck() != 1))
			{
				pX = i;
				pY = j;
				return -1;
			}
		}
	}

	for (int i = xEnd; i >= x; i--)
	{
		for (int j = yStart; j <= y; j++)
		{
			if (i + j == x + y && j + 4 < _size && i - 4 >= 0)
			{
				// tính tổng trên đường chéo phụ
				res = _pArr[i][j].getCheck() + _pArr[i - 1][j + 1].getCheck() + _pArr[i - 2][j + 2].getCheck()
					+ _pArr[i - 3][j + 3].getCheck() + _pArr[i - 4][j + 4].getCheck();
				x1 = i + 1;
				y1 = j - 1;
				if (x1 >= _size || y1 < 0)
				{
					x1 = i;
					y1 = i;
				}
				x2 = i - 5;
				y2 = j + 5;
				if (x2<0 || y2>_size)
				{
					x2 = i;
					y2 = j;
				}
			}
			if (res == 5 && (_pArr[x1][y1].getCheck() != -1 || _pArr[x2][y2].getCheck() != -1))
			{
				pX = i;
				pY = j;
				return 1;
			}
			if (res == -5 && (_pArr[x1][y1].getCheck() != 1 || _pArr[x2][y2].getCheck() != 1))
			{
				pX = i;
				pY = j;
				return -1;
			}
		}
	}

	return 2; // Trả mặc định là tiep tuc
}


//Chơi cùng máy
void _Board::CPU(int& x, int& y)
{
	long long max = 0;
	long long markAttack = 0;
	long long markDefense = 0;

	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getCheck() == 0)
			{
				markAttack = TC_CheoNguoc(i, j) + TC_CheoXuoi(i, j) + TC_Cot(i, j) + TC_Dong(i, j);

				markDefense = PT_CheoNguoc(i, j) + PT_CheoXuoi(i, j) + PT_Cot(i, j) + PT_Dong(i, j);

				int tmp = (markAttack > markDefense) ? markAttack : markDefense;

				if (max < tmp)
				{
					max = tmp;
					x = i;
					y = j;
				}
			}

		}
	}
}

int _Board::checkBoardCPU(int& pX, int& pY, bool pTurn)
{
	if (pTurn)
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
				{
					_pArr[i][j].setCheck(-1);// Nếu lượt hiện hành là true: c = -1
					return _pArr[i][j].getCheck();
				}
			}
		}
	}
	else
	{

		int x = rand() % 4 + 4;
		int y = rand() % 4 + 4;

		CPU(x, y);

		//Minimax(x, y);


		_pArr[x][y].setCheck(1);
		pX = y * 4 + getLeft() + 2;
		pY = x * 2 + getTop() + 1;
		return _pArr[x][y].getCheck();
	}
	return 0;
}


//Attack

long long _Board::TC_Cot(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; (i < 6) && (x + i < _size); i++)
	{
		if (_pArr[x + i][y].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x + i][y].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; (i < 6) && (x - i >= 0); i++)
	{
		if (_pArr[x - i][y].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x - i][y].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (player == 2) return 0;

	total -= defense[player + 1];

	total += attack[computer];
	return total;
}

long long _Board::TC_Dong(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size; i++)
	{
		if (_pArr[x][y + i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x][y + i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0; i++)
	{
		if (_pArr[x][y - i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x][y - i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (player == 2) return 0;

	total -= defense[player + 1];
	total += attack[computer];
	return total;
}

long long _Board::TC_CheoNguoc(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size && x - i >= 0; i++)
	{
		if (_pArr[x - i][y + i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x - i][y + i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0 && x + i < _size; i++)
	{
		if (_pArr[x + i][y - i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x + i][y - i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (player == 2) return 0;

	total -= defense[player + 1];
	total += attack[computer];

	return total;
}

long long _Board::TC_CheoXuoi(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size && x + i < _size; i++)
	{
		if (_pArr[x + i][y + i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x + i][y + i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0 && x - i >= 0; i++)
	{
		if (_pArr[x - i][y - i].getCheck() == 1)
		{
			computer++;
		}
		else if (_pArr[x - i][y - i].getCheck() == -1)
		{
			player++;
			break;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (player == 2) return 0;

	total -= defense[player + 1];
	total += attack[computer];
	return total;
}

//Defense

long long _Board::PT_Cot(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && x + i < _size; i++)
	{
		if (_pArr[x + i][y].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x + i][y].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && x - i >= 0; i++)
	{
		if (_pArr[x - i][y].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x - i][y].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (computer == 2) return 0;

	total += defense[player];

	if (player > 0)
		total -= attack[computer] * 2;

	return total;
}

long long _Board::PT_Dong(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size; i++)
	{
		if (_pArr[x][y + i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x][y + i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0; i++)
	{
		if (_pArr[x][y - i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x][y - i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (computer == 2) return 0;

	total += defense[player];

	if (player > 0)
		total -= attack[computer] * 2;
	return total;
}

long long _Board::PT_CheoNguoc(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size && x - i >= 0; i++)
	{
		if (_pArr[x - i][y + i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x - i][y + i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0 && x + i < _size; i++)
	{
		if (_pArr[x + i][y - i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x + i][y - i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (computer == 2) return 0;

	total += defense[player];

	if (player > 0)
		total -= attack[computer] * 2;
	return total;
}

long long _Board::PT_CheoXuoi(int x, int y)
{
	long long total = 0;

	long long player = 0;
	long long computer = 0;

	for (int i = 1; i < 6 && y + i < _size && x + i < _size; i++)
	{
		if (_pArr[x + i][y + i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x + i][y + i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}


	for (int i = 1; i < 6 && y - i >= 0 && x - i >= 0; i++)
	{
		if (_pArr[x - i][y - i].getCheck() == 1)
		{
			computer++;
			break;
		}
		else if (_pArr[x - i][y - i].getCheck() == -1)
		{
			player++;
		}
		else
		{
			//Xu ly nhieu o trong;
			break;
		}
	}

	if (computer == 2) return 0;

	total += defense[player];

	if (player > 0)
		total -= attack[computer] * 2;
	return total;
}

//MiniMax
void _Board::Minimax(int& x, int& y)
{
	Move bestMove = findBestMove();

	x = bestMove.col;
	y = bestMove.row;
}

bool _Board::isMovesLeft()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			if (_pArr[i][j].getCheck() == 0)
				return true;
	return false;
}

int _Board::evaluate()
{
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			if (testBoard(i, j) != 0) return testBoard(i, j);
		}
	}
	return 0;
}

int _Board::minimax(int depth, bool isMax)
{
	int player = -1, opponent = 1;
	int score = evaluate(); // xu ly thang thua;

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 1)
	{
		score = 10;
		return score;
	}

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -1)
	{
		score = -10;
		return score;
	}

	// If there are no more moves and no winner then 
	// it is a tie 
	if (isMovesLeft() == false)
		return 0;

	// If this maximizer's move 
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				// Check if cell is empty 
				if (_pArr[i][j].getCheck() == 0)
				{
					// Make the move 
					_pArr[i][j].setCheck(player);

					// Call minimax recursively and choose 
					// the maximum value 
					best = max(best,
						minimax(depth + 1, !isMax));

					// Undo the move 
					_pArr[i][j].setCheck(0);
				}
			}
		}
		return best;
	}

	// If this minimizer's move 
	else
	{
		int best = 1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (_pArr[i][j].getCheck() == 0)
				{
					// Make the move 
					_pArr[i][j].setCheck(opponent);

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best,
						minimax(depth + 1, !isMax));

					// Undo the move 
					_pArr[i][j].setCheck(0);
				}
			}
		}
		return best;
	}
}

Move _Board::findBestMove()
{
	int player = -1, opponent = 1;
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;


	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{

			if (_pArr[i][j].getCheck() == 0)
			{
				// Make the move 
				_pArr[i][j].setCheck(player);

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(0, false);

				// Undo the move 
				_pArr[i][j].setCheck(0);

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}