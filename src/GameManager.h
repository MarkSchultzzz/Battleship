#pragma once

class GameManager
{
public:
				GameManager();

	int			getLastX()		{ return lastX_; }
	int			getLastY()		{ return lastY_; }
	bool		getTurnShoot()	{ return turnShoot_; }

	void		makeTurn();
	void		handleTurn(const int& turnResult);
	void		drawHumanStatictics() const;
private:
	Player*		players_[2];

	bool		turnShoot_;
	int			lastX_;
	int			lastY_;
};