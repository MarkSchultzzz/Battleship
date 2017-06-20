#include "Header.h"

void main()
{
	srand(time(NULL));

	GameManager gameManager;
	GameField gameMap[2]; //0 - humanMap | 1 - botMap

	gameMap[0].generateShips();
	gameMap[1].generateShips();

	while (true) {
		gameMap[0].draw(1);
		gameMap[1].draw();

		gameManager.makeTurn();

		switch(gameMap[!static_cast<int>(gameManager.getTurnShoot())].takeShot(gameManager.getLastX() - 1, gameManager.getLastY() - 1)) {
		case 0:
			gameManager.handleTurn(0);
			break;
		case 1:
			gameManager.handleTurn(1);
			break;
		case 2:
			gameManager.handleTurn(2);
			break;
		}
		system("cls");
	}
}