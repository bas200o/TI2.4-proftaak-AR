#pragma once

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_


#include <gamelogic\gameobjects\GameObject.h>
#include <vector>

class GameWorld
{
private:
	std::vector<GameObject*> gameObjects; //vector?

public:
	GameWorld();

	/* Updates all gameobjects */
	void update();

	/* Draws all gameobjects */
	void draw();

	/* Adds a gameobject */
	void addGameObject(GameObject* gameObject);

	/* Removes a gameobject */
	void removeGameObject(GameObject* gameObject);

private:
	/* Private method to check collision during an update */
	void checkCollosion();

};

#endif