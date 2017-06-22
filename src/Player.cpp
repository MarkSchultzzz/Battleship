#include "Header.h"

void
Player::increasePoints()
{
	points_++;
}

void
Player::setAliveShips(const int& count)
{
	if (count >= 0)
		shipsAlive_ = count;
}

void
Player::setKilledShips(const int& count)
{
	if (count >= 0)
		shipsKilled_ = count;
}

void
Player::drawStatistics() const
{
	cout << "Ships killed: "	<< shipsKilled_ << endl;
	cout << "Ships allive: "	<< shipsAlive_	<< endl;
	cout << "Points: "			<< points_		<< endl;
}