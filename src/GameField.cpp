#include "Header.h"

GameField::GameField()
{
	areShipsOnMap = true;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			ships_[i][j] = 0;

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			tomporaryStorage_[i][j] = 178;
}

void
GameField::generateShips()
{
	int x, y, dirrection, count;

	//Generating Four-blocks ship
	dirrection = rand() % 2;

	if (dirrection == 0) {
		x = rand() % 10 + 1;
		y = rand() % 7 + 1;

		placeShip(x, y, dirrection, 4);
	}
	else {
		x = rand() % 7 + 1;
		y = rand() % 10 + 1;

		placeShip(x, y, dirrection, 4);
	}

	//Generating Three-blocks ships
	count = 2;

	while (count > 0)
	{
		while (true)
		{
			dirrection = rand() % 2;

			if (dirrection == 0) {
				x = rand() % 10 + 1;
				y = rand() % 8 + 1;
			}
			else {
				x = rand() % 8 + 1;
				y = rand() % 10 + 1;
			}

			if (!isThereCollisions(x, y, dirrection, 3))
				break;
		}

		placeShip(x, y, dirrection, 3);

		count--;
	}

	//Generating Two-blocks ships
	count = 3;

	while (count > 0) {
		while (true) {
			dirrection = rand() % 2;

			if (dirrection == 0) {
				x = rand() % 10 + 1;
				y = rand() % 9 + 1;
			}
			else {
				x = rand() % 9 + 1;
				y = rand() % 10 + 1;
			}

			if (!isThereCollisions(x, y, dirrection, 2))
				break;
		}
		placeShip(x, y, dirrection, 2);

		count--;
	}

	//Generating One-block ships
	count = 4;

	while (count > 0) {
		while (true) {
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;

			if (!isThereCollisions(x, y, 0, 1))
				break;
		}
		placeShip(x, y, 0, 1);

		count--;
	}
}

void
GameField::placeShip(const int& x, const int& y, const int& dirrection, const int& length)
{
	int xFirstCoefficient = 0, xSecondCoefficient = 0, yFirstCoefficient = 0, ySecondCoefficient = 0;

	//Algorithm for vertical ships
	if (dirrection == 0) {
		for (int i = y; i < y + length; i++)
		{
			tomporaryStorage_[i][x] = 'O';
			ships_[i - 1][x - 1] = 1;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 1;
		xFirstCoefficient = 1;
		xSecondCoefficient = 2;
		
		for (int i = y - yFirstCoefficient; i < y + length + ySecondCoefficient; i++)
		{
			for (int j = x - xFirstCoefficient; j < x + xSecondCoefficient; j++)
			{
				if (tomporaryStorage_[i][j] != 'O')
					tomporaryStorage_[i][j] = '$';
			}
		}
	}
	//Algorithm for horizontal ships
	else {
		for (int i = x; i < x + length; i++)
		{
			tomporaryStorage_[y][i] = 'O';
			ships_[y - 1][i - 1] = 1;
		}

		yFirstCoefficient = 1;
		ySecondCoefficient = 2;
		xFirstCoefficient = 1;
		xSecondCoefficient = 1;

		for (int i = y - yFirstCoefficient; i < y + ySecondCoefficient; i++)
			for (int j = x - xFirstCoefficient; j < x + length + xSecondCoefficient; j++)
				if (tomporaryStorage_[i][j] != 'O')
					tomporaryStorage_[i][j] = '$';
	}
}

void
GameField::clearGameField()
{
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			tomporaryStorage_[i][j] = 178;
}

bool
GameField::isThereCollisions(const int& x, const int& y, const int& dirrection, const int& length) const
{
	if (dirrection == 0) {
		for (int i = y; i < y + length - 1; i++)
			if (tomporaryStorage_[i][x] == '$' || tomporaryStorage_[i][x] == 'O')
				return true;

			for (int i = y - 1; i < y + length + 1; i++)	
				for (int j = x - 1; j < x + 2; j++)
					if (tomporaryStorage_[i][j] == 'O')
						return true;

		return false;
	}
	else {
		for (int i = x; i < x + length - 1; i++)
				if (tomporaryStorage_[i][x] == '$' || tomporaryStorage_[i][x] == 'O')
					return true;

		for (int i = y - 1; i < y + 2; i++)
			for (int j = x - 1; j < x + length + 1; j++)
				if (tomporaryStorage_[i][j] == 'O')
					return true;

		return false;
	}
}

int
GameField::generateValue(const int& minValue, const int& maxValue) const
{
	return rand() % maxValue + minValue;
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

	for (int i = 0; i < 10; i++)
	{
		if (i + 1 < 10)
			cout << i + 1 << ' ';
		else
			cout << i + 1;


		for (int j = 0; j < 10; j++)
		{
			switch (ships_[i][j]) {
			case 0:
				cout << static_cast<char> (178);
				//cout << 0;
				break;
			case -1:
				cout << static_cast<char> (176);
				//cout << '-';
				break;
			case 1:
				if (isAllVisible)
					cout << '#';
				else
					cout << static_cast<char> (178);

				//cout << 1;
				break;
			case 2:
				cout << 'X';
				//cout << 2;
				break;
			}
		}
		cout << endl;
	}
}