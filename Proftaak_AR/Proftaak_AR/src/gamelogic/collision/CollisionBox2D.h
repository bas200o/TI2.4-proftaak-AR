#pragma once
#include <glm/vec2.hpp>
#include <array>

class CollisionBox2D
{
private:
	double width;
	double height;

protected:
	

public:
	glm::vec2 center;
	double angle;

	/* give angle in degrees */
	CollisionBox2D(glm::vec2 center, double angle, double width, double height);

	/* Checks if this box collides with another */
	bool collidesWith(CollisionBox2D collisionBox);

	/* Pushes this box in the direction it's facing, changed by the angle offset in degrees */
	void push(double distance, double angleOffset);

	std::array<glm::vec2, 4> calculateCorners();//TODO MAKE PROTECTED AFTER TESTING
};