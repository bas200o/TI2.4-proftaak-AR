#pragma once

#include <vector>

#include "Renderer/Transform3D.h"
#include "Renderer/RawModel.h"
#include "Renderer/shading/Shader.h"
#include "Renderer/Renderer.h"
#include "windowhandling/Window.h"

namespace OpenGL
{
	class GameObject
	{
	public:
		Transform3D transform;

	private:
		std::vector<RawModel> models;
		Shader shader;

	public:
		GameObject();

		void draw(Window& window);
		virtual void update(float deltatime) = 0;
	};
}