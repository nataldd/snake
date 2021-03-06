// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream> 
#include <conio.h> 
#include <Windows.h> //Чтобы замедлить игру 
using namespace std;

bool lose, win;
const int width = 20;
const int height = 20;
int x, y, fx, fy, sc;
enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;

void setup() {
	lose = false;
	win = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fx = rand() % width;
	fy = rand() % height;
	sc = 0;
}

void draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else if (i == fy && j == fx)
				cout << "F";
			else
				cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Your score is: " << sc;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			lose = true;
			break;
		};
	}
}

void logic() {
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) КОД ИЗ УРОКА 
	// lose = true; КОД ИЗ УРОКА 
	if (x > width - 2)
		x = 0;
	if (x < 0)
		x = width - 2;
	if (y > height - 1)
		y = 0;
	if (y < 0)
		y = height - 1; //Змейка появляется с противоположной стороны при столкновении со стеной 
	if (x == fx && y == fy) {
		sc += 10;
		fx = rand() % width;
		fy = rand() % height;
	}
	if (sc == 600) { //Игрок выигрывает по достижению 600 очков 
		win = true;
	}
}

int main() {
	setup();
	while (!lose && !win) {
		input();
		logic();
		draw();
		Sleep(250); //Задержка в мс 
	}
	if (win) {
		cout << "\nYOU WON\n"; //Экран победы 
	}
	else {
		cout << "\nYou loose\n"; //Экран проигрыша 
	}
	cin >> lose; //Проект не закроется сразу 
}
