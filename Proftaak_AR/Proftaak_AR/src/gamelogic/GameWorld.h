#pragma once
#include <gamelogic\GameObject.h>
#include <vector>
#include <list>

class GameWorld
{
private:
	std::list<GameObject> gameObjects;

public:
	GameWorld();

	/* Updates all gameobjects */
	void update();

	/* Draws all gameobjects */
	void draw();

	/* Adds a gameobject */
	void addGameObject(GameObject gameObject);

	/* Removes a gameobject */
	void removeGameObject(GameObject gameObject);

private:
	/* Private method to check collision during an update */
	void checkCollosion();

	//TODO add list of gameobjects

};

