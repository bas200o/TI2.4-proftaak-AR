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
		for (TMPair tmPair : this->models)
			if(!tmPair.model.expired())
				Renderer::draw3D(*tmPair.transform, *tmPair.model.lock(), *this->shader.lock(), window, camera);
	}
}
