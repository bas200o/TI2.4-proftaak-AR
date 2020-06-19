#include "CollisionDetector.h"

GameLogic::Collider::CollisionResult GameLogic::CollisionDetector::checkCollision(Collider& colliderA, Collider& colliderB)
{

	return Collider::CollisionResult();
}

GameLogic::Collider::CollisionResult GameLogic::CollisionDetector::checkCubeToSphereCollision(CubeCollider& cubeCollider, SphereCollider& sphereCollider)
{
	float closestX, closestY, closestZ;

	glm::vec3 cubePosition = cubeCollider.transform.getWorldPosition();
	glm::vec3 spherePosition = sphereCollider.transform.getWorldPosition();
	if (cubePosition.x + (cubeCollider.getWidth() / 2) < spherePosition.x)
		closestX = cubePosition.x + (cubeCollider.getWidth() / 2);
	else if (cubePosition.x - (cubeCollider.getWidth() / 2) > spherePosition.x)
		closestX = cubePosition.x - (cubeCollider.getWidth() / 2);
	else
		closestX = cubePosition.x;

	if (cubePosition.y + (cubeCollider.getHeight() / 2) < spherePosition.y)
		closestY = cubePosition.y + (cubeCollider.getHeight() / 2);
	else if (cubePosition.y - (cubeCollider.getHeight() / 2) > spherePosition.y)
		closestY = cubePosition.y - (cubeCollider.getHeight() / 2);
	else
		closestY = cubePosition.y;

	if (cubePosition.z + (cubeCollider.getDepth() / 2) < spherePosition.z)
		closestZ = cubePosition.z + (cubeCollider.getDepth() / 2);
	else if (cubePosition.z - (cubeCollider.getDepth() / 2) > spherePosition.z)
		closestZ = cubePosition.z - (cubeCollider.getDepth() / 2);
	else
		closestZ = cubePosition.z;

	glm::vec3 closestPointOnCube = glm::vec3(closestX, closestY, closestZ);
	float distanceToSphereCenter = glm::distance(closestPointOnCube, sphereCollider.transform.getWorldPosition());
	if (distanceToSphereCenter < sphereCollider.getRadius())
	{
		glm::vec3 direction = glm::normalize(closestPointOnCube - sphereCollider.transform.getWorldPosition());

		return { true, (direction * (sphereCollider.getRadius() - distanceToSphereCenter)) };
	}
	return { false, glm::vec3(0.0f) };
}
