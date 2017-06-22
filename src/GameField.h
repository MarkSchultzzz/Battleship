#ifndef __GameField_h__
#define __GameField_h__

class GameField
{
public:
						GameField();

	void				generateShips();
	void				placeShip(const int& x, const int& y, const int& direction, const int& length);
	int					takeShot(const int& x, const int& y);
	int					getAliveShips()																			const;
	bool				isThereCollisions(const int& x, const int& y, const int& direction, const int& length)	const;
	void				draw(bool isAllVisible = 0)																const;
	bool				didYouLose()																			const;
private:
	static const int	FIELD_SIZE = 10;
	int					temporaryField_[FIELD_SIZE + 2][FIELD_SIZE + 2];		//Ships generator field
	int					gameField_[FIELD_SIZE][FIELD_SIZE];						//Stores ships on sea
};

#endif