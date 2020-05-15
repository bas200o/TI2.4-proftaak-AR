#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "gamelogic/collision/CollisionBox.h"

/* A single collision object can contain multiple "hitboxes" */
class CollisionObject2D
{
private:
	glm::vec2 position;
	double angle;
	std::vector<CollisionBox> collisionBoxes;

public:

	CollisionObject2D(glm::vec2 position, double angle, std::vector<CollisionBox> boxes);

	bool collidesWith(CollisionObject2D collisionObject);

	//TODO move methods

	glm::vec2 const& getPosition();

	double const& getAngle();

	std::vector<CollisionBox> const& getCollisionBoxes();
};

