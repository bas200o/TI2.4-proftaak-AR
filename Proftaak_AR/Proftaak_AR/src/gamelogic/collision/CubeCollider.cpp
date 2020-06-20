#include "CubeCollider.h"
#include "CollisionDetector.h"

GameLogic::CubeCollider::CubeCollider(const float width, const float height, const float depth)
	: width(width), height(height), depth(depth) {}

GameLogic::CubeCollider::CubeCollider(const glm::vec3 position, float width, const float height, const float depth)
	: width(width), height(height), depth(depth)
{
	this->transform.setLocalPosition(position);
}

GameLogic::Collider::CollisionResult GameLogic::CubeCollider::checkCollision(Collider& collider)
{
	if (CubeCollider* cubeCollider = dynamic_cast<CubeCollider*>(&collider))
		return checkCubeCollision(*cubeCollider);
	else
		return CollisionDetector::checkCollision(*this, collider);
	return { false, glm::vec3(0.0f) };
}

GameLogic::Collider::CollisionResult GameLogic::CubeCollider::checkCubeCollision(CubeCollider& collider)
{
	return { false, glm::vec3(0.0f) };
}
