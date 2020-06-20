#include "Timer.h"

GameLogic::Timer::Timer(unsigned int hours, unsigned int minutes, unsigned int seconds)
	: hours(hours), minutes(minutes), seconds(seconds), secondsCounter(0.0f) {}

GameLogic::Timer::Timer()
	: hours(0), minutes(0), seconds(0), secondsCounter(0.0f) {}

void GameLogic::Timer::reset()
{
	this->hours = 0;
	this->minutes = 0;
	this->seconds = 0;
	this->secondsCounter = 0.0f;
}

void GameLogic::Timer::addSeconds(const float seconds)
{
	this->secondsCounter += seconds;
	if (this->secondsCounter >= 1.0f)
	{
		float secondsCounterModulo = fmod(this->secondsCounter, 1.0f);
		unsigned int secondsAmmount = (this->secondsCounter - secondsCounterModulo);
		this->seconds += secondsAmmount;
		this->secondsCounter = secondsCounterModulo;
		if (this->seconds >= 60)
		{
			unsigned int secondsModulo = (this->seconds % 60);
			unsigned int minutesAmmount = ((secondsAmmount - secondsModulo) / 60);
			this->minutes += minutesAmmount + 1;
			this->seconds = secondsModulo;
			if (this->minutes >= 60)
			{
				unsigned int minutesModulo = (this->minutes % 60);
				unsigned int hoursAmmount = ((minutesAmmount - (minutesAmmount % 60)) / 60);
				this->hours += hoursAmmount + 1;
				this->minutes = minutesModulo;
				if (this->hours >= 24)
				{
					unsigned int hoursModulo = (this->hours % 24);
					this->hours = hoursModulo;
				}
			}
		}
	}
}

std::string GameLogic::Timer::getString()
{
	std::stringstream stringStream;
	stringStream << std::to_string(this->hours) << ":" << std::to_string(this->minutes) << ":" << std::to_string(this->seconds);
	return stringStream.str();
}