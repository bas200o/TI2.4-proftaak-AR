#pragma once

#ifndef KART_H_
#define KART_H_

#include<gamelogic\gameobjects\GameObject.h>

class Kart : GameObject
{
private:
	double speed;
	
public:
	Kart(CollisionBox2D collisionBox);

	/*Inherited via GameObject*/
	virtual void update() override;

};

#endif