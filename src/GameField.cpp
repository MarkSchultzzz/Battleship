#include "Header.h"

GameField::GameField()
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			gameField_[i][j] = 0;

	for (int i = 0; i < FIELD_SIZE + 2; i++)
		for (int j = 0; j < FIELD_SIZE + 2; j++)
			temporaryField_[i][j] = 0;
}

void
GameField::generateShips()
{
	const int SHIP_COUNT = 10;
	int x, y, direction, shipsCount = 0;
	int shipSize[SHIP_COUNT] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	while (shipsCount <= SHIP_COUNT) {
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
GameField::placeShip(const int& x, const int& y, const int& direction, const int& length)
{
	int xFirstCoefficient = 0, xSecondCoefficient = 0, yFirstCoefficient = 0, ySecondCoefficient = 0;

	//Algorithm for vertical ships
	if (direction == 0) {
		for (int i = y; i < y + length; i++) {
			temporaryField_[i][x] = 1;
			gameField_[i - 1][x - 1] = length;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 1;
		xFirstCoefficient = 1;
		xSecondCoefficient = 2;
		
		for (int i = y - yFirstCoefficient; i < y + length + ySecondCoefficient; i++)
			for (int j = x - xFirstCoefficient; j < x + xSecondCoefficient; j++)
				if (temporaryField_[i][j] != 1)
					temporaryField_[i][j] = 2;
	}
	//Algorithm for horizontal ships
	else {
		for (int i = x; i < x + length; i++) {
			temporaryField_[y][i] = 1;
			gameField_[y - 1][i - 1] = length;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 2;
		xFirstCoefficient = 1;
		xSecondCoefficient = 1;

		for (int i = y - yFirstCoefficient; i < y + ySecondCoefficient; i++)
			for (int j = x - xFirstCoefficient; j < x + length + xSecondCoefficient; j++)
				if (temporaryField_[i][j] != 1)
					temporaryField_[i][j] = 2;
	}
}

bool
GameField::isThereCollisions(const int& x, const int& y, const int& direction, const int& length) const
{
	if (direction == 0) {
		for (int i = y; i < y + length - 1; i++)
			if (temporaryField_[i][x] == 2 || temporaryField_[i][x] == 1)
				return true;

			for (int i = y - 1; i < y + length + 1; i++)	
				for (int j = x - 1; j < x + 2; j++)
					if (temporaryField_[i][j] == 1)
						return true;

		return false;
	}
	else {
		for (int i = x; i < x + length - 1; i++)
				if (temporaryField_[i][x] == 2 || temporaryField_[i][x] == 1)
					return true;

		for (int i = y - 1; i < y + 2; i++)
			for (int j = x - 1; j < x + length + 1; j++)
				if (temporaryField_[i][j] == 1)
					return true;

		return false;
	}
}

int
GameField::takeShot(const int& x, const int& y)
{
	if (gameField_[y][x] == 0) {
		gameField_[y][x] = -1;
		return 0;
	}

	if (gameField_[y][x] == 1 || gameField_[y][x] == 2 || gameField_[y][x] == 3 || gameField_[y][x] == 4) {
		gameField_[y][x] = 5;

		return 1;
	}

	if (gameField_[y][x] == 5 || gameField_[y][x] == -1 || x < 0 || x > 9 || y < 0 || y > 9)
		return 2;
}

int
GameField::getAliveShips() const
{
	int counter = 0;
	int shipsCopy[FIELD_SIZE][FIELD_SIZE];

	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			shipsCopy[i][j] = gameField_[i][j];

	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			if (shipsCopy[i][j] == 1)
				counter++;

			if (shipsCopy[i][j] == 2 || shipsCopy[i][j] == 3 || shipsCopy[i][j] == 4) {
				int iterations = 0;

				if (shipsCopy[i + 1][j] == 0 || 
					shipsCopy[i + 1][j] == -1) { //direction horizontal
					iterations = shipsCopy[i][j] - 1;
					while (iterations > 0) {
						shipsCopy[i][j + iterations--] = 0;
					}
				}
				if (shipsCopy[i][j + 1] == 0 || 
					shipsCopy[i][j + 1] == -1) { //direction vertical
					iterations = shipsCopy[i][j] - 1;
					while (iterations > 0) {
						shipsCopy[i + iterations--][j] = 0;
					}
				}
				counter++;
			}
		}
	}

	return counter;
}

bool
GameField::didYouLose() const
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (gameField_[i][j] == 1 || gameField_[i][j] == 2 || gameField_[i][j] == 3 || gameField_[i][j] == 4)
				return false;

	return true;
}

void
GameField::draw(bool isAllVisible) const
{
	if (isAllVisible == true)
		cout << "Your sea" << endl;
	else
		cout << "Enemy sea" << endl;

	cout << "  ";
	for (int i = 1; i < 11; i++)
		cout << i;

	cout << endl;

	for (int i = 0; i < FIELD_SIZE; i++) {
		if (i + 1 < 10)
			cout << i + 1 << ' ';
		else
			cout << i + 1;

		for (int j = 0; j < FIELD_SIZE; j++) {
			switch (gameField_[i][j]) {
			case 0 :
				cout << static_cast<char> (178);
				break;
			case -1 :
				cout << static_cast<char> (176);
				break;
			case 1 :
			case 2 :
			case 3 :
			case 4 :
				if (isAllVisible == true)
					cout << '#';
				else
					cout << static_cast<char> (178);
				break;
			case 5 :
				cout << 'X';
				break;
			}
		}
		cout << endl;
	}
}
