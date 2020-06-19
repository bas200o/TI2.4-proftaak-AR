#include "GameObject.h"

#include <iostream>

GameLogic::GameObject::GameObject()
{
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	this->shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Lighting.glsl"));
}

void GameLogic::GameObject::draw(OpenGL::Window& window, OpenGL::Camera& camera)
{
	if (!this->shader.expired())
	{
		for (TMTPair tmPair : this->models)
		{
			setRequiredUniforms(tmPair);

			// Bind textures
			for (int i = 0; i < tmPair.textures.size(); i++)
				if (!tmPair.textures[i].expired())
					tmPair.textures[i].lock()->bind(i);

			if (!tmPair.model.expired())
				OpenGL::Renderer::draw3D(*tmPair.transform, *tmPair.model.lock(), *this->shader.lock(), window, camera);

			// Unbind textures
			for (int i = 0; i < tmPair.textures.size(); i++)
				if (!tmPair.textures[i].expired())
					tmPair.textures[i].lock()->unbind();
		}
	}
}

void GameLogic::GameObject::checkCollision(Collider& collider)
{
	for (std::shared_ptr<Collider> col : this->colliders)
	{
		Collider::CollisionResult result = col->checkCollision(collider);
		if (result.isColliding)
		{
			onCollision();
			this->transform.translateBy(result.correctionDisplacement);
		}
	}
}
