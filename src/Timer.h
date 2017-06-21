#pragma once


class Timer
{
public:
			Timer();

	void	startTimer();
	void	stopTimer();
	bool	isSecondPassed();
	void	computeTime();
	void	draw()				const;
private:
	int		currentSeconds_;
	int		seconds_;
	int		minutes_;
	int		hours_;
};