#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

void ColorCursor(int x, int y, int color, string message);

void ColorCursor(int x, int y, int color, string message) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, color);
	cout << message << "\n";
}
