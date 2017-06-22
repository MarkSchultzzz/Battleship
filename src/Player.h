#ifndef __Player_h__
#define __Player_h__

class Player
{
public:
	void			drawStatistics() const;
	void			setKilledShips(const int& count);
	void			setAliveShips(const int& count);
	void			increasePoints();
	virtual void	shoot(int& x, int& y) = 0;
protected:
	int				shipsKilled_;
	int				shipsAlive_;
	int				points_;
};

#endif 