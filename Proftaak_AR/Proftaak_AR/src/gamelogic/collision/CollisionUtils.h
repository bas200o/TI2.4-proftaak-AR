#pragma once
#include <corecrt_math_defines.h>

namespace collutil {

	/* Takes an angle and the amount it should be changed by to return the changed angle 
	This method wraps the changed angle around if it gets too large or small */
	static double wrapChangedAngle(double currentAngle, double angleChange)
	{
		currentAngle += angleChange;
		//the range of the angle shouldn't matter except for preventing overflows
		while (currentAngle > 720) {
			currentAngle -= 360.0;
		}
		while (currentAngle < 0.0) {
			currentAngle += 360.0;
		}
		return currentAngle;
	}

	/* TODO */
	static glm::vec2 pushInDirection(glm::vec2 position, double angle, double angleOffset)
	{

	}

	static double degreesToRadians(double degrees) {
		return degrees * M_PI / 180.0;
	}

	static glm::vec2 rotatedPoint(glm::vec2 point, glm::vec2 origin, double angle) {
		return glm::vec2(cos(angle * point.x - origin.x) - sin(angle * (point.y - origin.y)),
			sin(angle) * (point.x - origin.x) - cos(angle) * (point.y - origin.y));
	}
	//box.position = glm::vec2(cos(this->angle) * (box.position.x - this->position.x) - sin(this->angle) * (box.position.y - this->position.y),
		//sin(this->angle) * (box.position.x - this->position.x) - cos(this->angle) * (box.position.y - this->position.y));
}