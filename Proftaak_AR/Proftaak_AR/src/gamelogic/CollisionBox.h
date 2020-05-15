#pragma once
#include <glm/vec2.hpp>

class CollisionBox
{
private:
	glm::vec2 position;
	double angle;
	double width;
	double height;

public:
	CollisionBox(glm::vec2 position, double angle, double width, double height);

	bool collidesWith(CollisionBox collisionBox);

	glm::vec2 const& getPosition();

	double const& getAngle();

	double const& getWidth();

	double const& getHeight();
};

