#pragma once

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

}