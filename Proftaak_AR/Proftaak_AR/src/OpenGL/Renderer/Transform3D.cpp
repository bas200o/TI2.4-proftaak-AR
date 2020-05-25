#include "Transform3D.h"

Engine::Transform3D::Transform3D()
	: parent(nullptr)
{
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

Engine::Transform3D::Transform3D(std::shared_ptr<Transform3D> parent)
	: parent(parent)
{
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

Engine::Transform3D::Transform3D(const glm::vec3 position)
	: parent(nullptr)
{
	this->position = position;
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

void Engine::Transform3D::translateBy(const glm::vec3 translate)
{
	this->position += translate;
}

void Engine::Transform3D::rotateBy(const float angle, const glm::vec3 axis)
{
	this->rotation = glm::normalize(glm::angleAxis(angle, axis) * this->rotation);
}

void Engine::Transform3D::rotateBy(const glm::quat rotation)
{
	this->rotation = rotation * this->rotation;
}

void Engine::Transform3D::scaleBy(const glm::vec3 scale)
{
	this->scale += scale;
}

glm::vec3 Engine::Transform3D::getWorldPosition() const
{
	if (this->parent != nullptr)
		return this->parent->getWorldPosition() + this->position;
	else
		return this->position;
}

glm::quat Engine::Transform3D::getWorldRotation() const
{
	if (this->parent != nullptr)
		return this->parent->getWorldRotation() * this->rotation;
	else
		return this->rotation;
}

glm::vec3 Engine::Transform3D::getWorldScale() const
{
	if (this->parent != nullptr)
		return this->parent->getWorldScale() * this->scale;
	else
		return this->scale;
}

void Engine::Transform3D::setLocalPosition(glm::vec3 position)
{
	this->position = position;
}

void Engine::Transform3D::setLocalRotation(float angle, glm::vec3 axis)
{
	this->rotation = glm::normalize(glm::angleAxis(angle, axis));
}

void Engine::Transform3D::setLocalRotation(glm::quat rotation)
{
	this->rotation = glm::normalize(rotation);
}

void Engine::Transform3D::setLocalScale(glm::vec3 scale)
{
	this->scale = scale;
}

void Engine::Transform3D::setLocalScale(float scale)
{
	this->scale = glm::vec3(scale);
}

void Engine::Transform3D::setParent(std::shared_ptr<Transform3D> transform)
{
	this->parent = transform;
}

glm::mat4 Engine::Transform3D::getLocalTransform() const
{
	glm::mat4 traMatrix = getTranslationMatrix();
	glm::mat4 scaleMatrix = getScaleMatrix();
	glm::mat4 rotMatrix = getRotationMatrix();

	return (traMatrix * rotMatrix * scaleMatrix);
}

glm::mat4 Engine::Transform3D::getWorldTransform() const
{
	glm::mat4 traMatrix = getTranslationMatrix();
	glm::mat4 scaleMatrix = getScaleMatrix();
	glm::mat4 rotMatrix = getRotationMatrix();

	glm::mat4 transformationL = (traMatrix * rotMatrix * scaleMatrix);

	if (this->parent != nullptr)
	{
		glm::mat4 transformationP = this->parent->getWorldTransform();
		return transformationP * transformationL;
	}
	else
		return transformationL;
}

glm::mat4 Engine::Transform3D::getTranslationMatrix() const
{
	return glm::translate(this->position);
}

glm::mat4 Engine::Transform3D::getRotationMatrix() const
{
	return glm::toMat4(this->rotation);
}

glm::mat4 Engine::Transform3D::getScaleMatrix() const
{
	return glm::scale(this->scale);
}

glm::vec3 Engine::Transform3D::getFront() const
{
	return glm::normalize(this->rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Engine::Transform3D::getUp() const
{
	return glm::normalize(glm::cross(getRight(), getFront()));
}

glm::vec3 Engine::Transform3D::getRight() const
{
	return glm::normalize(glm::cross(getFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Engine::Transform3D::getBack() const
{
	return -getFront();
}

glm::vec3 Engine::Transform3D::getDown() const
{
	return -getUp();
}

glm::vec3 Engine::Transform3D::getLeft() const
{
	return -getRight();
}

void Engine::Transform3D::operator=(glm::mat4 const& matrix)
{
	this->position = matrix[3];
	this->rotation = glm::toQuat(matrix);
	this->scale = glm::vec3(glm::length(matrix[0]), glm::length(matrix[1]), glm::length(matrix[2]));
}
