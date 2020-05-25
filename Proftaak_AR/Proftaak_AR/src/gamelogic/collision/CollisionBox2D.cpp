#include "CollisionBox2D.h"

//public:
CollisionBox2D::CollisionBox2D(glm::vec2 center, double angle, double width, double height)
{
	this->center = center;
	this->angle = collutil::degreesToRadians(angle);
	this->width = width;
	this->height = height;
	this->corners = this->calculateCorners();
}

bool CollisionBox2D::collidesWith(CollisionBox2D collisionBox)
{
	std::array<glm::vec2, 4> corners[] = { this->getCorners(), collisionBox.getCorners() };

	for (std::array<glm::vec2, 4> points : corners) //for each box (group of points)
	{
		for (int i1 = 0; i1 < points.size(); i1++) //for each corner
		{
			int   i2 = (i1 + 1) % points.size();
			glm::vec2 p1 = points[i1];
			glm::vec2 p2 = points[i2];

			glm::vec2 normal = glm::vec2(p2.y - p1.y, p1.x - p2.x);

			double minA = std::numeric_limits<double>::max();
			double maxA = std::numeric_limits<double>::min();
			for (glm::vec2 point : this->getCorners()) //this box
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
			for (glm::vec2 point : collisionBox.getCorners()) //other box
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
	return true;
}

void CollisionBox2D::push(double distance, double degreesOffset)
{
	this->center += glm::vec2(cos(collutil::degreesToRadians(this->angle + degreesOffset)) * distance,
		sin(collutil::degreesToRadians(this->angle + degreesOffset)) * distance);
	this->corners = this->calculateCorners();
}

void CollisionBox2D::rotate(double degreesChange)
{
	this->angle = collutil::radiansToDegrees(collutil::wrapChangedDegrees(collutil::radiansToDegrees(this->angle), degreesChange));
	this->corners = this->calculateCorners();
}

void CollisionBox2D::setCenter(glm::vec2 center)
{
	this->center = center;
	this->corners = this->calculateCorners();
}

void CollisionBox2D::setAngle(double degrees)
{
	this->angle = collutil::degreesToRadians(degrees);
	this->corners = this->calculateCorners();
}

std::array<glm::vec2, 4> CollisionBox2D::getCorners()
{
	return this->corners;
}

//private:
std::array<glm::vec2, 4> CollisionBox2D::calculateCorners()
{
	glm::vec2 TL = glm::vec2(this->center.x - ((this->width / 2) * cos(this->angle)) - ((this->height / 2) * sin(this->angle)),
		this->center.y - ((this->width / 2) * sin(this->angle)) + ((this->height / 2) * cos(this->angle)));//top left

	glm::vec2 TR = glm::vec2(this->center.x + ((this->width / 2) * cos(this->angle)) - ((this->height / 2) * sin(this->angle)),
		this->center.y + ((this->width / 2) * sin(this->angle)) + ((this->height / 2) * cos(this->angle)));//top right

	glm::vec2 BL = glm::vec2(this->center.x - ((this->width / 2) * cos(this->angle)) + ((this->height / 2) * sin(this->angle)),
		this->center.y - ((this->width / 2) * sin(this->angle)) - ((this->height / 2) * cos(this->angle)));//bottom left

	glm::vec2 BR = glm::vec2(this->center.x + ((this->width / 2) * cos(this->angle)) + ((this->height / 2) * sin(this->angle)),
		this->center.y + ((this->width / 2) * sin(this->angle)) - ((this->height / 2) * cos(this->angle)));//bottom right
	return std::array<glm::vec2, 4> {TL, TR, BL, BR};
}