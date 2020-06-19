#pragma once

#include "Collider.h"

namespace GameLogic
{
	class CubeCollider : public Collider
	{
	private:
		float width, height, depth;

	public:
		CubeCollider(const float width, const float height, const float depth);
		CubeCollider(const glm::vec3 position, float width, const float height, const float depth);

		virtual CollisionResult checkCollision(Collider& collider) override;

		inline float getWidth() { return this->width; }
		inline float getHeight() { return this->height; }
		inline float getDepth() { return this->depth; }

	private:
		CollisionResult checkCubeCollision(CubeCollider& collider);
	};
}