#pragma once
#include <glm/vec2.hpp>
#include <vector>

class CollisionBox
{
private:
	//TODO make these protected?
	glm::vec2 position;
	double angle;
	double width;
	double height;

protected:
	std::vector<glm::vec2> getPoints();

public:
	CollisionBox(glm::vec2 position, double angle, double width, double height);

	/* Checks if this box collides with another */
	bool collidesWith(CollisionBox collisionBox);

	/* Returns  the positions of the corners of this box */
	glm::vec2 const& getPosition();

	double const& getAngle();

	double const& getWidth();

	double const& getHeight();
};

