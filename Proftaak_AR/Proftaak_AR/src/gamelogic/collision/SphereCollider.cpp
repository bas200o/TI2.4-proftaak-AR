#include "SphereCollider.h"
#include "CollisionDetector.h"

GameLogic::SphereCollider::SphereCollider(const float radius)
	: radius(radius)
{

}

GameLogic::SphereCollider::SphereCollider(const glm::vec3 position, const float radius)
	: radius(radius)
{
	this->transform.setLocalPosition(position);
}

GameLogic::Collider::CollisionResult GameLogic::SphereCollider::checkCollision(Collider& collider)
{
	if (SphereCollider * sphereCollider = dynamic_cast<SphereCollider*>(&collider))
		return checkSphereCollision(*sphereCollider);
	else
		return CollisionDetector::checkCollision(*this, collider);
	return { false, glm::vec3(0.0f) };;
}

GameLogic::Collider::CollisionResult GameLogic::SphereCollider::checkSphereCollision(SphereCollider& collider)
{
	float distanceBetweenCenters = glm::distance(this->transform.getWorldPosition(), collider.transform.getWorldPosition());
	if (distanceBetweenCenters < (this->radius + collider.radius))
	{
		glm::vec3 displacement = (glm::normalize(this->transform.getWorldPosition() - collider.transform.getWorldPosition()) * (((this->radius + collider.radius) - distanceBetweenCenters) + 0.1f));
		return { true, glm::vec3(displacement.x, displacement.y, displacement.z) };
	}
	return { false, glm::vec3(0.0f) };
}