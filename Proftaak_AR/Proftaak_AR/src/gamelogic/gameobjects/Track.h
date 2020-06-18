#pragma once

#include <string>

#include <glm/glm.hpp>

#include "OpenGL/GameObject.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

namespace GameLogic
{
	class Track : public OpenGL::GameObject
	{
	public:
		Track(const glm::vec3 position, const std::string trackName);
		~Track();

		virtual void update(float deltatime) override;
		virtual void setRequiredUniforms(TMTPair& tmPair) override;
	};
}