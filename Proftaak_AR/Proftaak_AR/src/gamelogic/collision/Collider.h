#pragma once

#include <glm/glm.hpp>

#include "OpenGL/Renderer/Transform3D.h"
//#include "CollisionDetector.h"

namespace GameLogic
{
	class Collider
	{
	public:
		struct CollisionResult
		{
			bool isColliding;
			glm::vec3 correctionDisplacement;
		};

	public:
		OpenGL::Transform3D transform;

		virtual CollisionResult checkCollision(Collider& collider) = 0;
	};
}