#include "Header.h"

Timer::Timer()
{
	currentSeconds_ = 0;
	seconds_ = 0; 
	minutes_ = 0;
	hours_ = 0;
}

void
Timer::startTimer()
{
	time_t currentTime = time(NULL);
	
	currentSeconds_ = static_cast<int>(currentTime);
}

bool
Timer::isSecondPassed()
{
	time_t currentTime = time(NULL);

	if (static_cast<int>(currentTime) > currentSeconds_) {
		currentSeconds_++;
		seconds_++;
		return true;
	}

	return false;
}

void
Timer::computeTime()
{
	if (seconds_ > 60) {
		minutes_++;
		seconds_ -= 60;
	}
	if (minutes_ > 60) {
		hours_++;
		minutes_ -= 60;
	}
}

void
Timer::draw() const
{
	cout << seconds_ << ':' << minutes_ << ':' << hours_ << endl;
}

void
Timer::stopTimer()
{
	currentSeconds_ = 0;
	seconds_ = 0;
	minutes_ = 0;
	hours_ = 0;
}