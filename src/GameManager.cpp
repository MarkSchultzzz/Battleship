#include "Header.h"

GameManager::GameManager()
{
	players_[0] = new Human;
	players_[1] = new Bot;

	turnShoot_ = false;
	lastX_ = 0;
	lastY_ = 0;
}

GameManager::~GameManager()
{
	for (int i = 0; i < 2; i++)
		delete players_[i];
}

int
GameManager::getLastX()
{
	return lastX_;
}

int
GameManager::getLastY()
{
	return lastY_;
}

bool
GameManager::getTurnShoot()
{
	return turnShoot_;
}

void
GameManager::setHumanAliveShips(const int& count)
{
	if (count >= 0)
		players_[0]->setAliveShips(count);
}

void
GameManager::setHumanKilledShips(const int& count)
{
	if (count >= 0)
		players_[0]->setKilledShips(count);
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
	case 0 :
		if (turnShoot_ == true)
			turnShoot_ = false;
		else
			turnShoot_ = true;
		break;
	case 1 :
		players_[static_cast<int>(turnShoot_)]->increasePoints();
		break;
	case 2 :
		if (turnShoot_ == false) {
			cout << "Incorrect coordinates! Press any button";
			_getch();
		}
		break;
	}
}

void
GameManager::drawHumanStatictics() const
{
	players_[0]->drawStatistics();
}