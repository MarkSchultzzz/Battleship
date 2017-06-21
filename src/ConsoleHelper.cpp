#include "Header.h"

void
ConsoleHelper::setCursor(const HANDLE& handleStdOut, const int& x, const int& y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(handleStdOut, coord);
}