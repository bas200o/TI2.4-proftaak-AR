#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "gamelogic/collision/CollisionUtils.h"

class CollisionBox
{
private:
	double width;
	double height;

protected:
	/* Returns the positions of the corners of this box */
	std::vector<glm::vec2> getPoints();

public:
	glm::vec2 position;
	double angle;

	CollisionBox(glm::vec2 position, double angle, double width, double height);

	/* Checks if this box collides with another */
	bool collidesWith(CollisionBox collisionBox);

	glm::vec2 const& getPosition();

	double const& getAngle();
};

