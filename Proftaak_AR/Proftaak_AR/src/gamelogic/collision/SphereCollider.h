#pragma once

#include "Collider.h"

namespace GameLogic
{
	class SphereCollider : public Collider
	{
	private:
		float radius;

	public:
		SphereCollider(const float radius);
		SphereCollider(const glm::vec3 position, const float radius);

		virtual CollisionResult checkCollision(Collider& collider) override;

		inline float getRadius() { return this->radius; }

	private:
		CollisionResult checkSphereCollision(SphereCollider& collider);
	};
}