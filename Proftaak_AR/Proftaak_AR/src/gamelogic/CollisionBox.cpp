#include "CollisionBox.h"

CollisionBox::CollisionBox(glm::vec2 position, double angle, double width, double height)
{
	this->position = position;
	this->angle = angle;
	this->width = width;
	this->height = height;
}

bool CollisionBox::collidesWith(CollisionBox collisionBox)
{
	return false;
}

glm::vec2 const& CollisionBox::getPosition()
{
	return this->position;
}

double const& CollisionBox::getAngle()
{
	return this->angle;
}

double const& CollisionBox::getWidth()
{
	return this->width;
}

double const& CollisionBox::getHeight()
{
	return this->height;
}
