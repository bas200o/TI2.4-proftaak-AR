#pragma once

#include <string>
#include <sstream>

#include <cmath>

namespace GameLogic
{
	class Timer
	{
	public:
		unsigned int hours;
		unsigned int minutes;
		unsigned int seconds;

		float secondsCounter;

		Timer(unsigned int hours, unsigned int minutes, unsigned int seconds);
		Timer();

		void reset();
		void addSeconds(const float seconds);
		std::string getString();
	};
}