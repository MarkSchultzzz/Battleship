#pragma once

class Player
{
public:
	void			drawStatistics() const;
	void			increaseShipsKilled()		{ shipsKilled_++; }
	void			reduceShipsAlive()			{ shipsAlive_--; }
	void			increasePoints()			{ points_ += 5; }
	virtual void	shoot(int& x, int& y) = 0;
protected:
	int				shipsKilled_;
	int				shipsAlive_;
	int				points_;
};