#pragma once

#include <glm/glm.hpp>

#include "OpenGL/GameObject.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

namespace GameLogic
{
	class Kart : public OpenGL::GameObject
	{
	private:
		glm::vec3 color;

		OpenGL::Transform3D steeringWheelTransform;
		OpenGL::Transform3D leftFrontWheelTransform;
		OpenGL::Transform3D rightFrontWheelTransform;
		OpenGL::Transform3D backWheelsTransform;
		OpenGL::Transform3D gasPedalTransform;
		OpenGL::Transform3D brakePedalTransform;

	public:
		Kart(const glm::vec3 color);

		virtual void update(float deltatime) override;
	};
}