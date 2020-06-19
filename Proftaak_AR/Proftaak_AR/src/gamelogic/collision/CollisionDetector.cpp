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
	glm::vec3 closestPointOnSphere = sphereCollider.transform.getWorldPosition() + (glm::normalize(cubePosition - sphereCollider.transform.getWorldPosition()) * sphereCollider.getRadius());
	closestX = closestPointOnSphere.x;
	closestY = closestPointOnSphere.y;
	closestZ = closestPointOnSphere.z;

	//if (cubePosition.x + (cubeCollider.getWidth() / 2) < spherePosition.x)
	//	closestX = cubePosition.x + (cubeCollider.getWidth() / 2);
	//else if (cubePosition.x - (cubeCollider.getWidth() / 2) > spherePosition.x)
	//	closestX = cubePosition.x - (cubeCollider.getWidth() / 2);
	//else
	//	closestX = cubePosition.x;

	//if (cubePosition.y + (cubeCollider.getHeight() / 2) < spherePosition.y)
	//	closestY = cubePosition.y + (cubeCollider.getHeight() / 2);
	//else if (cubePosition.y - (cubeCollider.getHeight() / 2) > spherePosition.y)
	//	closestY = cubePosition.y - (cubeCollider.getHeight() / 2);
	//else
	//	closestY = cubePosition.y;

	//if (cubePosition.z + (cubeCollider.getDepth() / 2) < spherePosition.z)
	//	closestZ = cubePosition.z + (cubeCollider.getDepth() / 2);
	//else if (cubePosition.z - (cubeCollider.getDepth() / 2) > spherePosition.z)
	//	closestZ = cubePosition.z - (cubeCollider.getDepth() / 2);
	//else
	//	closestZ = cubePosition.z;

	if (closestPointOnSphere.x > cubePosition.x + (cubeCollider.getWidth() / 2))
		closestX = cubePosition.x + (cubeCollider.getWidth() / 2);
	else if (closestPointOnSphere.x < cubePosition.x - (cubeCollider.getWidth() / 2))
		closestX = cubePosition.x - (cubeCollider.getWidth() / 2);

	if (closestPointOnSphere.y > cubePosition.y + (cubeCollider.getHeight() / 2))
		closestY = cubePosition.y + (cubeCollider.getHeight() / 2);
	else if (closestPointOnSphere.y < cubePosition.y - (cubeCollider.getHeight() / 2))
		closestY = cubePosition.y - (cubeCollider.getHeight() / 2);

	if (closestPointOnSphere.z > cubePosition.z + (cubeCollider.getDepth() / 2))
		closestZ = cubePosition.z + (cubeCollider.getDepth() / 2);
	else if (closestPointOnSphere.z < cubePosition.z - (cubeCollider.getDepth() / 2))
		closestZ = cubePosition.z - (cubeCollider.getDepth() / 2);

	glm::vec3 closestPointOnCube = glm::vec3(closestX, closestY, closestZ);
	OpenGL::Renderer::drawDebugSphere(glm::vec3(0.0f, 1.0f, 0.0f), closestPointOnCube, 0.05f, *OpenGL::Renderer::window, *OpenGL::Renderer::camera);
	OpenGL::Renderer::drawDebugSphere(glm::vec3(0.0f, 0.0f, 1.0f), closestPointOnSphere, 0.05f, *OpenGL::Renderer::window, *OpenGL::Renderer::camera);
	float distanceToSphereCenter = glm::distance(closestPointOnCube, sphereCollider.transform.getWorldPosition());
	if (distanceToSphereCenter < sphereCollider.getRadius())
	{
		glm::vec3 direction = glm::normalize(sphereCollider.transform.getWorldPosition() - closestPointOnCube);

		return { true, (direction * ((sphereCollider.getRadius() - distanceToSphereCenter) + 0.1f)) };
	}
	return { false, glm::vec3(0.0f) };
}
