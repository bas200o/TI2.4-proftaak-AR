#include "GameObject.h"

GameObject::GameObject(CollisionObject2D collisionObject) : collisionObject(collisionObject)
{
	this->collisionObject = collisionObject;
}

void GameObject::update()
{
}

void GameObject::draw()
{
}
