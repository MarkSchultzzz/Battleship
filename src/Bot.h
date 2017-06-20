#pragma once

class Bot : public Player
{
public:
			Bot();

	void	shoot(int& x, int& y);
private:
	int lastHitX_;
	int lastHitY_;
};