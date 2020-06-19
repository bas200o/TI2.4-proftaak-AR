#pragma once

#include <vector>
#include <memory>

#include "OpenGL/Renderer/Transform3D.h"
#include "OpenGL/Renderer/RawModel.h"
#include "OpenGL/Renderer/shading/Shader.h"
#include "OpenGL/Renderer/shading/Texture2D.h"
#include "OpenGL/Renderer/Renderer.h"
#include "OpenGL/Renderer/Camera.h"
#include "OpenGL/windowhandling/Window.h"

#include "gamelogic/collision/CubeCollider.h"
#include "gamelogic/collision/SphereCollider.h"

namespace GameLogic
{
	class GameObject
	{
	protected:
		struct TMTPair
		{
			OpenGL::Transform3D* transform;
			std::weak_ptr<OpenGL::RawModel> model;
			std::vector<std::weak_ptr<OpenGL::Texture2D>> textures;
			bool useLighting;
		};

	public:
		OpenGL::Transform3D transform;

	protected:
		std::vector<TMTPair> models;
		std::weak_ptr<OpenGL::Shader> shader;

		std::vector<std::shared_ptr<Collider>> colliders;

	public:
		GameObject();

		void draw(OpenGL::Window& window, OpenGL::Camera& camera);
		virtual void update(float deltatime) = 0;
		void checkCollision(Collider& collider);

		inline std::vector<std::shared_ptr<Collider>> getColliders() { return this->colliders; }

	private:
		virtual void setRequiredUniforms(TMTPair& tmPair) = 0;
		virtual void onCollision() = 0;
	};
}