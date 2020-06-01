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

		float maxSteeringAngle;	// Radians
		float steeringAngle;	// Radians

		float maxSpeed;
		float currentSpeed;
		float accelaration;
		float brakeForce;

		float wheelCircumference;
		float drag;
		float currentWheelAngle;

		bool isAccelarating;
		bool isBraking;

	public:
		Kart(const glm::vec3 color, const float wheelRadius, const float maxSpeed, const float accelaration, const float brakeForce);

		void steer(const float angle);

		inline void setIsAccelarating(bool isAccelarating) { this->isAccelarating = isAccelarating; }
		inline void setIsBraking(bool isBraking) { this->isBraking = isBraking; }

		virtual void update(float deltatime) override;

	private:
		void rotateWheels(float wheelRotationSpeed);

		virtual void setRequiredUniforms() override;
	};
}