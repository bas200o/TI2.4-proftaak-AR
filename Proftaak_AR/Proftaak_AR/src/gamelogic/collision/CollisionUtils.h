#pragma once

#ifndef COLLISIONUTILS_H_
#define COLLISIONUTILS_H_

#include <corecrt_math_defines.h>

namespace collutil {

	/* Takes an angle in degrees and the amount it should be changed by to return the changed angle in degrees
	This method wraps the changed angle around if it gets too large or small */
	static double wrapChangedDegrees(double currentDegrees, double degreesChange)
	{
		currentDegrees += degreesChange;
		//the range of the angle shouldn't matter except for preventing overflows
		while (currentDegrees > 720.0) {
			currentDegrees -= 360.0;
		}
		while (currentDegrees < 0.0) {
			currentDegrees += 360.0;
		}
		return currentDegrees;
	}

	static double degreesToRadians(double degrees) {
		return degrees * M_PI / 180.0;
	}

	static double radiansToDegrees(double radians) {
		return radians * 180.0 / M_PI;
	}

	//TODO create collision detection testing method
}

#endif