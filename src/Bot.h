#ifndef __Bot_h__
#define __Bot_h__

class Bot : public Player
{
public:
	void	shoot(int& x, int& y);
private:
	int		lastHitX_;
	int		lastHitY_;
};

#endif