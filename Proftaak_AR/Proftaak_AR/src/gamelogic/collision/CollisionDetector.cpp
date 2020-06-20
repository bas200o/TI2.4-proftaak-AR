#include "CollisionDetector.h"
#include "OpenGL/Renderer/Renderer.h"

GameLogic::Collider::CollisionResult GameLogic::CollisionDetector::checkCollision(Collider& colliderA, Collider& colliderB)
{
	if (CubeCollider * cubeCollider = dynamic_cast<CubeCollider*>(&colliderA))
		if(SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(&colliderB))
			return checkCubeToSphereCollision(*cubeCollider, *sphereCollider);
	if (SphereCollider * sphereCollider = dynamic_cast<SphereCollider*>(&colliderA))
		if (CubeCollider * cubeCollider = dynamic_cast<CubeCollider*>(&colliderB))
			return checkCubeToSphereCollision(*cubeCollider, *sphereCollider);
	return { false, glm::vec3(0.0f) };
}

GameLogic::Collider::CollisionResult GameLogic::CollisionDetector::checkCubeToSphereCollision(CubeCollider& cubeCollider, SphereCollider& sphereCollider)
{
	float closestX, closestY, closestZ;

	glm::vec3 cubePosition = cubeCollider.transform.getWorldPosition();
	glm::vec3 spherePosition = sphereCollider.transform.getWorldPosition();
	closestX = spherePosition.x;
	closestY = spherePosition.y;
	closestZ = spherePosition.z;

	if (spherePosition.x > cubePosition.x + (cubeCollider.getWidth() / 2))
		closestX = cubePosition.x + (cubeCollider.getWidth() / 2);
	else if(spherePosition.x < cubePosition.x - (cubeCollider.getWidth() / 2))
		closestX = cubePosition.x - (cubeCollider.getWidth() / 2);

	if (spherePosition.y > cubePosition.y + (cubeCollider.getHeight() / 2))
		closestY = cubePosition.y + (cubeCollider.getHeight() / 2);
	else if (spherePosition.y < cubePosition.y - (cubeCollider.getHeight() / 2))
		closestY = cubePosition.y - (cubeCollider.getHeight() / 2);

	if (spherePosition.z > cubePosition.z + (cubeCollider.getDepth() / 2))
		closestZ = cubePosition.z + (cubeCollider.getDepth() / 2);
	else if (spherePosition.z < cubePosition.z - (cubeCollider.getDepth() / 2))
		closestZ = cubePosition.z - (cubeCollider.getDepth() / 2);

	glm::vec3 closestPointOnCube = glm::vec3(closestX, closestY, closestZ);
	glm::vec3 closestPointOnSphere = sphereCollider.transform.getWorldPosition() + (glm::normalize(closestPointOnCube - sphereCollider.transform.getWorldPosition()) * sphereCollider.getRadius());
	float distanceToSphereCenter = glm::distance(closestPointOnCube, sphereCollider.transform.getWorldPosition());
	if (distanceToSphereCenter < sphereCollider.getRadius())
	{
		glm::vec3 direction = glm::normalize(sphereCollider.transform.getWorldPosition() - closestPointOnCube);

		return { true, (direction * ((sphereCollider.getRadius() - distanceToSphereCenter) + 0.1f)) };
	}
	return { false, glm::vec3(0.0f) };
}
