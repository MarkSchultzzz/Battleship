#include "Header.h"

void main()
{
	srand(time(NULL));
	HANDLE handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GameManager gameManager; //0 - human | 1 - bot
	GameField gameMap[2]; //0 - humanMap | 1 - botMap
	Timer gameTimer, pauseTimer;

	int keyPressed = 0;
	bool turnDone = false;

	gameMap[0].generateShips();
	gameMap[1].generateShips();

	gameTimer.startTimer();

	while (true) {
		gameMap[0].draw(1);
		gameMap[1].draw();

		gameManager.setHumanAliveShips(gameMap[0].getAliveShips());
		gameManager.setHumanKilledShips(10 - gameMap[1].getAliveShips());

		ConsoleHelper::setCursor(handleStdOut, 0, 25);

		gameTimer.draw();
		gameManager.drawHumanStatictics();

		if (gameManager.getTurnShoot() == false) {
			ConsoleHelper::setCursor(handleStdOut, 0, 30);

			cout << "Enter - shoot\nP - pause\n";

			while (true) {
				if ((keyPressed = _kbhit()) != 0) {
					keyPressed = _getch();
					break;
				}

				if (gameTimer.isSecondPassed() == true) {
					gameTimer.computeTime();

					ConsoleHelper::setCursor(handleStdOut, 0, 25);

					gameTimer.draw();
				}
			}
			switch (keyPressed) {
			case 13 :
				ConsoleHelper::setCursor(handleStdOut, 0, 33);

				gameManager.makeTurn();

				turnDone = true;
				break;
			case 'P' :
			case 'p' :
				pauseTimer.startTimer();

				ConsoleHelper::setCursor(handleStdOut, 15, 5);

				cout << "Game on pause. Press any button to continue";

				while (true) {
					if ((keyPressed = _kbhit()) != 0) {
						break;
					}

					if (pauseTimer.isSecondPassed() == true) {
						pauseTimer.computeTime();

						ConsoleHelper::setCursor(handleStdOut, 15, 6);

						pauseTimer.draw();
					}
				}

				pauseTimer.stopTimer();

				break;
			}
		}
		else {
			gameManager.makeTurn();
			turnDone = true;
		}

		if (turnDone == true) {
			switch (gameMap[!static_cast<int>(gameManager.getTurnShoot())].takeShot(gameManager.getLastX() - 1, gameManager.getLastY() - 1)) {
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
		}
		
		for (int i = 0; i < 2; i++) {
			if (gameMap[i].didYouLose() == true) {
				system("cls");

				gameMap[0].draw(1);
				gameMap[1].draw(1);

				ConsoleHelper::setCursor(handleStdOut, 15, 6);

				i > 0 ? cout << "Humanity won this war! Well played, comrade" : cout << "Machine won! Try again";

				_getch();
				exit(0);
			}
				
		}

		if (gameTimer.isSecondPassed() == true)
			gameTimer.computeTime();

		system("cls");

		turnDone = false;
	}

}