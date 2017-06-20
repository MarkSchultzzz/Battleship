#include "Header.h"

void
Player::drawStatistics() const
{
	cout << "Ships killed: "	<< shipsKilled_ << endl;
	cout << "Ships allive: "	<< shipsAlive_	<< endl;
	cout << "Points: "			<< points_		<< endl;
}