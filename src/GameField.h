#pragma once

class GameField
{
public:
			GameField();

	void	generateShips();
	void	placeShip(const int& x, const int& y, const int& dirrection, const int& length);
	int		takeShot(const int& x, const int& y);
	bool	isThereCollisions(const int& x, const int& y, const int& dirrection, const int& length)	const;
	void	draw(bool isAllVisible = 0)																const;
	bool    didYouLose()																			const;
private:
	char	temporaryStorage_[12][12];	//Ships generate field
	int		ships_[10][10];				//Stores ships on sea
};