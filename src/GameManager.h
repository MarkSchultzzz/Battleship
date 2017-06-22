#ifndef __GameManager_h__
#define __GameManager_h__

class GameManager
{
public:
				GameManager();
				~GameManager();

	int			getLastX();
	int			getLastY();
	bool		getTurnShoot();
	void		setHumanKilledShips(const int& count);
	void		setHumanAliveShips(const int& count);

	void		makeTurn();
	void		handleTurn(const int& turnResult);
	void		drawHumanStatictics() const;
private:
	Player*		players_[2];

	bool		turnShoot_;
	int			lastX_;
	int			lastY_;
};

#endif