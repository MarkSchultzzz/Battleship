#include "Header.h"

GameManager::GameManager()
{
	players_[0] = new Human;
	players_[1] = new Bot;

	turnShoot_ = false;
	lastX_ = 0;
	lastY_ = 0;
}

void
GameManager::makeTurn()
{
	players_[static_cast<int>(turnShoot_)]->shoot(lastX_, lastY_);
}

void
GameManager::handleTurn(const int& turnResult)
{
	switch (turnResult)
	{
	case 0:
		if (turnShoot_)
			turnShoot_ = false;
		else
			turnShoot_ = true;
		break;
	case 1:
		players_[static_cast<int>(turnShoot_)]->increasePoints();
		break;
	case 2:
		cout << "Error! Incorrect coordinates!";
		_getch();
		break;
	}
}