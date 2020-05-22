#include "CollisionObject2D.h"

CollisionObject2D::CollisionObject2D(glm::vec2 position, std::vector<CollisionBox> boxes)
{
	this->position = position;
	this->angle = 0.0;
	this->collisionBoxes = boxes;

	for (CollisionBox &box : this->collisionBoxes) 
	{
		box.position.x += this->position.x;
		box.position.y += this->position.y;
	}
}

bool CollisionObject2D::collidesWith(CollisionObject2D collisionObject)
{
	for (CollisionBox &box1 : this->collisionBoxes)
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

void CollisionObject2D::rotate(double angleChange)
{
	this->angle = collutil::wrapChangedAngle(this->angle, angleChange);
	//Rotate all boxes around object position
	for (CollisionBox &box : this->collisionBoxes) 
	{
		box.angle = collutil::wrapChangedAngle(box.angle, angleChange);
		box.position = glm::vec2(cos(this->angle) * (box.position.x - this->position.x) - sin(this->angle) * (box.position.y - this->position.y), 
			sin(this->angle) * (box.position.x - this->position.x) - cos(this->angle) * (box.position.y - this->position.y));
	}
}

void CollisionObject2D::push(double distance, double angleOffset)
{
	this->position = glm::vec2(	this->position.x + cos(this->angle) * distance,
								this->position.y + sin(this->angle) * distance);
	for (CollisionBox &box : this->collisionBoxes) {
		box.push(distance, angleOffset);
	}
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
