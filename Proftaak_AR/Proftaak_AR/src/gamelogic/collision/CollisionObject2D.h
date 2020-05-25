#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "gamelogic/collision/CollisionBox.h"
#include "gamelogic/collision/CollisionUtils.h"

class CollisionObject2D
{
public:
	virtual bool collidesWith(CollisionObject2D collisionObject); //make protected after testing

	/*Checks collision between objects and moves them if necessary */
	//void collisionCheck(CollisionObject2D collisionObject);//TODO

	/* Rotates the collision object and all of its boxes around the position of the object*/
	virtual void rotate(double angleChange);

	/* Moves the collision object and all of its boxes*/
	//void move();//TODO

	/* Pushes this object in the direction it's facing, changed by the angle offset */
	virtual void push(double distance, double angleOffset);
};

