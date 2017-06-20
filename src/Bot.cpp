#include "Header.h"

Bot::Bot()
{
	lastHitX_ = 0;
	lastHitY_ = 0;
}

void
Bot::shoot(int& x, int& y)
{
	x = rand() % 10 + 1;
	y = rand() % 10 + 1;
}