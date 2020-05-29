#pragma once

#include <glm/glm.hpp>

#include "OpenGL/GameObject.h"

namespace GameLogic
{
	class Kart : public OpenGL::GameObject
	{
	private:
		glm::vec3 color;

	public:
		Kart(const glm::vec3 color);

		virtual void update(float deltatime) override;
	};
}