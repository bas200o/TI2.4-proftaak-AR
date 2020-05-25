#pragma once

#ifndef COLLISIONBOX2D_H_
#define COLLISIONBOX2D_H_

#include <glm/vec2.hpp>
#include <array>
#include <vector>
#include "CollisionUtils.h"

/*A movable collision box*/
class CollisionBox2D
{
private:
	double width;
	double height;
	std::array<glm::vec2, 4> corners;

	/*Calculates where the corners of the box should be
	This method is used to recalculate te positions of the corners after the box is moved*/
	std::array<glm::vec2, 4> calculateCorners();

public:
	glm::vec2 center;
	double angle;

	/*Constructor for a CollisionBox2D
	The angle should be provided in degrees*/
	CollisionBox2D(glm::vec2 center, double angle, double width, double height);

	/*Checks if this box collides with another*/
	bool collidesWith(CollisionBox2D collisionBox);

	/*Pushes this box in the direction it's facing, changed by the angle offset in degrees
	This method does not change the angle of the box*/
	void push(double distance, double degreesOffset);

	void rotate(double degreesChange);

	void setCenter(glm::vec2 center);

	void setAngle(double degrees);

	/*Returns the current positions of the corners of the box*/
	std::array<glm::vec2, 4> getCorners();
};

/*Notes:
The angle used inside the class should always be in radians, but the angle defined in the method parameters should be in degrees
*/

#endif