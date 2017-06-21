#include "Header.h"

void
Bot::shoot(int& x, int& y)
{
	x = rand() % 10 + 1;
	y = rand() % 10 + 1;
}