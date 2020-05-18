#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "gamelogic/collision/CollisionBox.h"
#include "gamelogic/collision/CollisionUtils.h"

/* A single collision object can contain multiple "hitboxes" */
class CollisionObject2D
{
private:
	glm::vec2 position;
	double angle;
	std::vector<CollisionBox> collisionBoxes;
	//double weight;

	/* Returns what the angle would be if it was changed by the amount specified in the parameter 
	This does not change the angle of the collision object */
	//double changedAngle(double angleChange);
	void changeAngle(double angleChange);

protected:
	double getCollisionForce();//TODO

	bool collidesWith(CollisionObject2D collisionObject);

public:
	/* Creates a collision object 
	The positions of the boxes should be absolute
	Keep in mind that the angle starts at 0.0 degrees */
	CollisionObject2D(glm::vec2 position, std::vector<CollisionBox> boxes);

	/*Checks collision between objects and moves them if necessary */
	void collisionCheck(CollisionObject2D collisionObject);//

	//TODO move methods
	/* Rotates the collision object and all of its boxes around the position of the object*/
	void rotate(double angleChange);

	/* Moves the collision object and all of its boxes*/
	void move();//TODO

	void push();//TODO

	glm::vec2 const& getPosition();

	double const& getAngle();

	std::vector<CollisionBox> const& getCollisionBoxes();
};

