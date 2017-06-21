#include "Header.h"

GameField::GameField()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			ships_[i][j] = 0;

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			temporaryStorage_[i][j] = ' ';
}

void
GameField::generateShips()
{
	int x, y, direction, shipsCount = 0;
	int shipSize[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	while (shipsCount <= 10) {
		while (true) {
			direction = rand() % 2;

			if (direction == 0) {
				x = rand() % 10 + 1;
				y = rand() % (11 - shipSize[shipsCount]) + 1;
			}
			else {
				x = rand() % (11 - shipSize[shipsCount]) + 1;
				y = rand() % 10 + 1;
			}

			if (isThereCollisions(x, y, direction, shipSize[shipsCount]) == 0)
				break;
		}

		placeShip(x, y, direction, shipSize[shipsCount]);
		shipsCount++;
	}
}

void
GameField::placeShip(const int& x, const int& y, const int& dirrection, const int& length)
{
	int xFirstCoefficient = 0, xSecondCoefficient = 0, yFirstCoefficient = 0, ySecondCoefficient = 0;

	//Algorithm for vertical ships
	if (dirrection == 0) {
		for (int i = y; i < y + length; i++) {
			temporaryStorage_[i][x] = 'O';
			ships_[i - 1][x - 1] = 1;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 1;
		xFirstCoefficient = 1;
		xSecondCoefficient = 2;
		
		for (int i = y - yFirstCoefficient; i < y + length + ySecondCoefficient; i++)
			for (int j = x - xFirstCoefficient; j < x + xSecondCoefficient; j++)
				if (temporaryStorage_[i][j] != 'O')
					temporaryStorage_[i][j] = '$';
	}
	//Algorithm for horizontal ships
	else {
		for (int i = x; i < x + length; i++) {
			temporaryStorage_[y][i] = 'O';
			ships_[y - 1][i - 1] = 1;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 2;
		xFirstCoefficient = 1;
		xSecondCoefficient = 1;

		for (int i = y - yFirstCoefficient; i < y + ySecondCoefficient; i++)
			for (int j = x - xFirstCoefficient; j < x + length + xSecondCoefficient; j++)
				if (temporaryStorage_[i][j] != 'O')
					temporaryStorage_[i][j] = '$';
	}
}

bool
GameField::isThereCollisions(const int& x, const int& y, const int& dirrection, const int& length) const
{
	if (dirrection == 0) {
		for (int i = y; i < y + length - 1; i++)
			if (temporaryStorage_[i][x] == '$' || temporaryStorage_[i][x] == 'O')
				return true;

			for (int i = y - 1; i < y + length + 1; i++)	
				for (int j = x - 1; j < x + 2; j++)
					if (temporaryStorage_[i][j] == 'O')
						return true;

		return false;
	}
	else {
		for (int i = x; i < x + length - 1; i++)
				if (temporaryStorage_[i][x] == '$' || temporaryStorage_[i][x] == 'O')
					return true;

		for (int i = y - 1; i < y + 2; i++)
			for (int j = x - 1; j < x + length + 1; j++)
				if (temporaryStorage_[i][j] == 'O')
					return true;

		return false;
	}
}

int
GameField::takeShot(const int& x, const int& y)
{
	if (ships_[y][x] == 0) {
		ships_[y][x] = -1;
		return 0;
	}

	if (ships_[y][x] == 1) {
		ships_[y][x] = 2;

		return 1;
	}

	if (ships_[y][x] == 2 || ships_[y][x] == -1 || x < 0 || x > 9 || y < 0 || y > 9)
		return 2;
}

bool
GameField::didYouLose() const
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (ships_[i][j] == 1)
				return false;

	return true;
}

void
GameField::draw(bool isAllVisible) const
{
	if (isAllVisible)
		cout << "Your sea" << endl;
	else
		cout << "Enemy sea" << endl;

	cout << "  ";
	for (int i = 1; i < 11; i++)
		cout << i;

	cout << endl;

	for (int i = 0; i < 10; i++) {
		if (i + 1 < 10)
			cout << i + 1 << ' ';
		else
			cout << i + 1;

		for (int j = 0; j < 10; j++) {
			switch (ships_[i][j]) {
			case 0 :
				cout << static_cast<char> (178);
				break;
			case -1 :
				cout << static_cast<char> (176);
				break;
			case 1 :
				if (isAllVisible)
					cout << '#';
				else
					cout << static_cast<char> (178);
				break;
			case 2 :
				cout << 'X';
				break;
			}
		}
		cout << endl;
	}
}