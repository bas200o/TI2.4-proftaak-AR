#pragma once

#include <memory>

#include <glm/gtx/transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>

namespace OpenGL
{
	class Transform3D
	{
	private:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		// Parent of the transform (can be a nullptr is no parent is required)
		std::shared_ptr<Transform3D> parent;

	public:
		Transform3D();
		Transform3D(std::shared_ptr<Transform3D> parent);
		Transform3D(const glm::vec3 position);

		// Methods for translating, rotating and scaling the transform
		void translateBy(const glm::vec3 translate);
		void rotateBy(const float angle, const glm::vec3 axis);
		void rotateBy(const glm::quat rotation);
		void scaleBy(const glm::vec3 scale);

		// Getters for local position, rotation and scale
		inline glm::vec3 getLocalPosition() const { return this->position; }
		inline glm::quat getLocalRotation() const { return this->rotation; }
		inline glm::vec3 getScale() const { return this->scale; }

		// Getters for world position, rotation and scale
		glm::vec3 getWorldPosition() const;
		glm::quat getWorldRotation() const;
		glm::vec3 getWorldScale() const;

		// Setters for local tranform
		void setLocalPosition(const glm::vec3 position);
		void setLocalRotation(const float angle, const glm::vec3 axis);
		void setLocalRotation(const glm::quat rotation);
		void setLocalScale(const glm::vec3 scale);
		void setLocalScale(const float scale);

		// Set the parent of the transform
		void setParent(std::shared_ptr<Transform3D> transform);

		// Getters for local and world transform
		glm::mat4 getLocalTransform() const;
		glm::mat4 getWorldTransform() const;

		// Geters for translation, rotation and scale matrices
		glm::mat4 getTranslationMatrix() const;
		glm::mat4 getRotationMatrix() const;
		glm::mat4 getScaleMatrix() const;

		// Utility methods for getting directional vectors of the transform
		glm::vec3 getFront() const;
		glm::vec3 getUp() const;
		glm::vec3 getRight() const;
		glm::vec3 getBack() const;
		glm::vec3 getDown() const;
		glm::vec3 getLeft() const;

		// Operator overload for creating a transfrom from a transformation matrix
		void operator=(glm::mat4 const& matrix);
	};
}