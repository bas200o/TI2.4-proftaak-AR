#include "GameWorld.h"

GameWorld::GameWorld()
{
	this->gameObjects = std::vector<GameObject*>();
}

void GameWorld::update()
{
}

void GameWorld::draw()
{
}

void GameWorld::addGameObject(GameObject* gameObject)
{
	this->gameObjects.push_back(gameObject);
}

void GameWorld::removeGameObject(GameObject* gameObject)
{
	//this->gameObjects.remove(gameObject);
}

void GameWorld::checkCollosion()
{
}
