#pragma once

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include <vector>
#include <algorithm>
#include <memory>

#include "gameobjects/GameObject.h"

namespace GameLogic
{
	class GameWorld
	{
	private:
		std::vector<std::shared_ptr<GameObject>> gameObjects;

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
		void checkCollision();
	};
}

#endif