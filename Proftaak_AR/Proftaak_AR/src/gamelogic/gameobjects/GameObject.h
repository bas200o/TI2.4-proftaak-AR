#pragma once

class GameObject
{
private:
	//TODO Mesh
	//TODO Shader
	//TODO Texture

protected:
	//CollisionObject2D collisionObject;

public:
	//TODO add mesh, shader and texture in the future
	GameObject();

	/* Updates this gameobject */
	void update();

	/* Draws this gameobject */
	void draw();
};

