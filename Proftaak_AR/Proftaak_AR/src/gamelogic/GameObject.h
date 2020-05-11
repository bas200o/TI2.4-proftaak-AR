#pragma once
#include <gamelogic\CollisionObject2D.h>

class GameObject
{
private:
	//TODO Mesh
	//TODO Shader
	//TODO Texture
	CollisionObject2D collisionObject;

public:
	//TODO add mesh, shader and texture in the future
	GameObject(CollisionObject2D collisionObject);

	/* Updates this gameobject */
	void update();

	/* Draws this gameobject */
	void draw();
};

