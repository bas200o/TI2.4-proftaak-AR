#pragma once

#ifndef TRACK_H_
#define TRACK_H_
#include<gamelogic\gameobjects\GameObject.h>

class Track : GameObject
{
public:
	Track(std::vector<CollisionBox2D> collisionBoxes);

	// Inherited via GameObject
	virtual void update() override;
};

#endif