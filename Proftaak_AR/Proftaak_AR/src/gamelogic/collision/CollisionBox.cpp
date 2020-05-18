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
	//TODO test
	//TODO fix warnings
	//TODO move other box accroding to collision direction?
	std::vector<glm::vec2> rectangles[] = { this->getPoints(), collisionBox.getPoints() };

	for (std::vector<glm::vec2> points : rectangles) //for each box
	{
		for (int i1 = 0; i1 < points.size(); i1++) //for each corner
		{
			int   i2 = (i1 + 1) % points.size();
			glm::vec2 p1 = points[i1];
			glm::vec2 p2 = points[i2];

			glm::vec2 normal = glm::vec2(p2.y - p1.y, p1.x - p2.x);

			double minA = std::numeric_limits<double>::max();
			double maxA = std::numeric_limits<double>::min();
			for (glm::vec2 point : this->getPoints()) //this box
			{
				double projected = normal.x * point.x + normal.y * point.y;

				if (projected < minA) {
					minA = projected;
				} if (projected > maxA) {
					maxA = projected;
				}
			}

			double minB = std::numeric_limits<double>::max();
			double maxB = std::numeric_limits<double>::min();
			for (glm::vec2 point : collisionBox.getPoints()) //other box
			{
				double projected = normal.x * point.x + normal.y * point.y;

				if (projected < minB) {
					minB = projected;
				} if (projected > maxB) {
					maxB = projected;
				}
			}
			if (maxA < minB || maxB < minA) {
				return false;
			}
		}

	}

	return false;
}

std::vector<glm::vec2> CollisionBox::getPoints()
{
	glm::vec2 TL = this->position; //top left
	glm::vec2 TR = this->position + glm::vec2(cos(angle), sin(angle)); //top right
	glm::vec2 BL = this->position + glm::vec2(cos(angle + 270.0), sin(angle + 270.0)); //bottom left
	glm::vec2 BR = BL + glm::vec2(cos(angle), sin(angle)); //bottom right
	std::vector<glm::vec2> points = std::vector<glm::vec2>();
	points.push_back(TL);
	points.push_back(TR);
	points.push_back(BL);
	points.push_back(BL);
	return points;
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
