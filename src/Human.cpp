#include "Header.h"

Human::Human()
{
	shipsKilled_ = 0;
	shipsAlive_ = 10;
	points_ = 0;
}

void
Human::shoot(int& x, int& y)
{
	cout << "Enter X coordinate (1-10): ";
	cin >> x;
	cout << "Enter Y coordinate (1-10): ";
	cin >> y;
}

void
Human::callPause() const
{
	
}