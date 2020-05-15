#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "gamelogic/CollisionBox.h"

/* A single collision object can contain multiple "hitboxes" */
class CollisionObject2D
{
private:
	glm::vec2 position;
	double angle;
	std::vector<CollisionBox> collisionBoxes;

public:

	CollisionObject2D(glm::vec2 position, double angle, std::vector<CollisionBox> boxes);

	/* Moves the collision object into a specified direction
	This does not change the angle of the collision object itself */
	//void move(double distance, double direction);

	/* Moves the collision object according to its current angle while applying an offset to the direction
	This does not change the angle of the collision object itself */
	//void moveWithOffset(double distance, double directionOffset);

	glm::vec2 const& getPosition();

	double const& getAngle();

	std::vector<CollisionBox> const& getCollisionBoxes();
};

