#pragma once

#include "CubeCollider.h"
#include "SphereCollider.h"

namespace GameLogic
{
	class CollisionDetector
	{
	public:
		static Collider::CollisionResult checkCollision(Collider& colliderA, Collider& colliderB);

	private:
		static Collider::CollisionResult checkCubeToSphereCollision(CubeCollider& cubeCollider, SphereCollider& sphereCollider);
	};
}