#include "CollisionObject2D.h"

CollisionObject2D::CollisionObject2D(glm::vec2 position, double angle, std::vector<CollisionBox> boxes)
{
	this->position = position;
	this->angle = angle;
	this->collisionBoxes = boxes;
}

bool CollisionObject2D::collidesWith(CollisionObject2D collisionObject)
{
	for (CollisionBox box1 : this->collisionBoxes) 
	{
		for (CollisionBox box2 : collisionObject.getCollisionBoxes())
		{
			if (box1.collidesWith(box2)) {
				return true;
			}
		}
	}
	return false;
}

glm::vec2 const& CollisionObject2D::getPosition()
{
	return this->position;
}

double const& CollisionObject2D::getAngle()
{
	return this->angle;
}

std::vector<CollisionBox> const& CollisionObject2D::getCollisionBoxes()
{
	return this->collisionBoxes;
}
