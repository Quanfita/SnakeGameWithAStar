#include "Board.h"
#include "Snake.h"
#include "AI.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

void play();			//玩家模式
void ai_play();			//AI模式
void Sign();			//开始界面
void show_about();		//显示关于

int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc;
	rc.Left = 5;
	rc.Top = 5;
	rc.Right = 84;
	rc.Bottom = 34;
	//此时窗口的宽度为50，高度为20
	SetConsoleWindowInfo(hOut, TRUE, &rc);
	Sign();
	//play();
	//ai_play();
	return 0;
}

void Sign()
{
	std::cout << "********************************" << std::endl;
	std::cout << "**                            **" << std::endl;
	std::cout << "**            SNAKE           **" << std::endl;
	std::cout << "**                            **" << std::endl;
	std::cout << "********************************" << std::endl;
	std::cout << std::endl;
	std::cout << " 1. Player" << std::endl;
	std::cout << " 2. AI Player" << std::endl;
	std::cout << " 3. About" << std::endl;
	std::cout << " 4. Exit" << std::endl;
	COORD coord;
	coord.X = 0;
	coord.Y = 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	char c;
	while ((c = _getch()) != 'q') {
		if (c == 'w') {
			if(coord.Y > 6)coord.Y--;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
		else if (c == 's') {
			if(coord.Y < 9)coord.Y++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
		else if (c == '\r') {
			int sign = coord.Y - 6;
			switch (sign)
			{
			case 0:
				system("cls");
				play();
				break;
			case 1:
				system("cls");
				ai_play();
				break;
			case 2:
				system("cls");
				show_about();
				break;
			case 3:
				return;
				break;
			default:
				break;
			}
			system("cls");
			Sign();
			return;
		}
	}
}

void show_about()
{
	std::fstream myfile("Reference.txt", std::ios::in | std::ios::out);
	std::string line;
	if (myfile.fail()) {
		std::cerr << "Error open file!" << std::endl;
		return;
	}
	while (std::getline(myfile, line)) {
		std::cout << line << std::endl;
	}
	system("pause>nul");
}

void ai_play()
{
	Board b;
	Snake s(b);
	AI a(b, s);
	char op;
	while (!a.in_advanced()) {
		Point dict;
		if (a.calc_path() 
			&& a.scout_move()) {
			dict = a.get_dict();
			while (dict != Zero) {
				if (_kbhit()) {
					op = _getch();
					if (op == 'q') {
						return;
					}
					else if(op == ' ')
					{
						system("pause>nul");
					}
				}
				while (!s.move(dict))
					;
				dict = a.get_dict();
			}
		}
		else {
			dict = a.wander();
			while (!s.move(dict))
				;
		}
	}
	while (true) {
		Point dict = a.wander();
		while (!s.move(dict))
			;
	}
}

void play()
{
	Board b;
	Snake s(b);
	char op;
	Point dict = Right;
	_getch();
	while (true) {
		if (_kbhit()) {
			op = _getch();
			switch (op)
			{
			case 'w':
				if (dict == Down) {
					break;
				}
				dict = Up;
				break;
			case 's':
				if (dict == Up) {
					break;
				}
				dict = Down;
				break;
			case 'a':
				if (dict == Right) {
					break;
				}
				dict = Left;
				break;
			case 'd':
				if (dict == Left) {
					break;
				}
				dict = Right;
				break;
			case ' ':
				system("pause>nul");
				break;
			case 'q':
				return;
				break;
			default:
				break;
			}
		}
		s.move(dict);
	}
}