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
	//TODO
	//figure out the location of the corners
	glm::vec2 TL1 = this->position; //top left
	glm::vec2 TR1 = this->position + glm::vec2(cos(angle), sin(angle)); //top right
	glm::vec2 BL1 = this->position + glm::vec2(cos(angle + 270.0), sin(angle + 270.0)); //bottom left
	glm::vec2 BR1 = BL1 + glm::vec2(cos(angle), sin(angle)); //bottom right

	glm::vec2 TL2 = collisionBox.getPosition(); //top left
	glm::vec2 TR2 = collisionBox.getPosition() + glm::vec2(cos(angle), sin(angle)); //top right
	glm::vec2 BL2 = collisionBox.getPosition() + glm::vec2(cos(angle + 270.0), sin(angle + 270.0)); //bottom left
	glm::vec2 BR2 = BL2 + glm::vec2(cos(angle), sin(angle)); //bottom right

	for (int i = 0; i < 2; i++)
	{
		
	}

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
