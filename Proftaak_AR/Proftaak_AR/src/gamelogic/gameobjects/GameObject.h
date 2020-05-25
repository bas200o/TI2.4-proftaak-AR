#pragma once

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <gamelogic\collision\CollisionBox2D.h>

class GameObject
{
private:
	//TODO Mesh
	//TODO Shader
	//TODO Texture

protected:
	std::vector<CollisionBox2D> collisionBoxes;

public:
	//TODO add mesh, shader and texture in the future
	//GameObject();

	/* Updates this gameobject */
	virtual void update() = 0;

	/* Draws this gameobject */
	void draw();
};

#endif
