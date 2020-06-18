#include "GameObject.h"

#include <iostream>

OpenGL::GameObject::GameObject()
{
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	this->shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Lighting.glsl"));
}

void OpenGL::GameObject::draw(Window& window, Camera& camera)
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
				Renderer::draw3D(*tmPair.transform, *tmPair.model.lock(), *this->shader.lock(), window, camera);

			// Unbind textures
			for (int i = 0; i < tmPair.textures.size(); i++)
				if (!tmPair.textures[i].expired())
					tmPair.textures[i].lock()->unbind();
		}
	}

	//if (!this->shader.expired())
	//{
	//	setRequiredUniforms();

	//	// Bind textures
	//	for (int i = 0; i < this->textures.size(); i++)
	//		if (!this->textures[i].expired())
	//			this->textures[i].lock()->bind(i);

	//	for (TMPair tmPair : this->models)
	//		if(!tmPair.model.expired())
	//			Renderer::draw3D(*tmPair.transform, *tmPair.model.lock(), *this->shader.lock(), window, camera);

	//	// Unbind textures
	//	for (int i = 0; i < this->textures.size(); i++)
	//		if (!this->textures[i].expired())
	//			this->textures[i].lock()->unbind();
	//}
}