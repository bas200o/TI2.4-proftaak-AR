#pragma once

#include <vector>
#include <memory>

#include "Renderer/Transform3D.h"
#include "Renderer/RawModel.h"
#include "Renderer/shading/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "windowhandling/Window.h"

namespace OpenGL
{
	class GameObject
	{
	protected:
		struct TMPair
		{
			OpenGL::Transform3D* transform;
			std::weak_ptr<RawModel> model;
		};

	public:
		Transform3D transform;

	protected:
		std::vector<TMPair> models;
		std::weak_ptr<Shader> shader;

	public:
		GameObject();

		void draw(Window& window, Camera& camera);
		virtual void update(float deltatime) = 0;
	};
}