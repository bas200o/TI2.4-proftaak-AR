#pragma once

#include <string>

#include <glm/glm.hpp>

#include "OpenGL/GameObject.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

namespace OpenGL
{
	class Track : public GameObject
	{
	public:
		Track(const glm::vec3 position, const std::string trackName);

		virtual void update(float deltatime) override;
		virtual void setRequiredUniforms() override;
	};
}