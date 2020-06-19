#pragma once

#include <string>

#include <glm/glm.hpp>

#include "GameObject.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

namespace GameLogic
{
	class Track : public GameObject
	{
	public:
		Track(const glm::vec3 position, const std::string trackName);
		~Track();

		virtual void update(float deltatime) override;
		virtual void setRequiredUniforms(TMTPair& tmPair) override;

		// Inherited via GameObject
		virtual void onCollision() override;

	private:
		void setupColliders();
	};
}