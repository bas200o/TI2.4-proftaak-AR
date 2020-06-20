#include "Transform3D.h"

OpenGL::Transform3D::Transform3D()
	: parent(nullptr)
{
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

OpenGL::Transform3D::Transform3D(Transform3D& parent)
	: parent(&parent)
{
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

OpenGL::Transform3D::Transform3D(const glm::vec3 position)
	: parent(nullptr)
{
	this->position = position;
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
}

OpenGL::Transform3D::~Transform3D()
{
	if (this->parent != nullptr)
		this->clearChild(*this);

	for (Transform3D* transform : this->children)
		transform->clearParent();
}

void OpenGL::Transform3D::translateBy(const glm::vec3 translate)
{
	this->position += translate;
}

void OpenGL::Transform3D::rotateBy(const float angle, const glm::vec3 axis)
{
	this->rotation = glm::normalize(glm::angleAxis(angle, axis) * this->rotation);
}

void OpenGL::Transform3D::rotateBy(const glm::quat rotation)
{
	this->rotation = rotation * this->rotation;
}

void OpenGL::Transform3D::scaleBy(const glm::vec3 scale)
{
	this->scale += scale;
}

glm::vec3 OpenGL::Transform3D::getWorldPosition() const
{
	if (this->parent != nullptr)
	{
		glm::vec4 rotatedPosition = glm::vec4(this->position, 1.0f) * glm::inverse(getWorldTransform());
		return this->parent->getWorldPosition() + glm::vec3(rotatedPosition.x, rotatedPosition.y, rotatedPosition.z);
	}
	else
		return this->position;
}

glm::quat OpenGL::Transform3D::getWorldRotation() const
{
	if (this->parent != nullptr)
		return this->parent->getWorldRotation() * this->rotation;
	else
		return this->rotation;
}

glm::vec3 OpenGL::Transform3D::getWorldScale() const
{
	if (this->parent != nullptr)
		return this->parent->getWorldScale() * this->scale;
	else
		return this->scale;
}

void OpenGL::Transform3D::setLocalPosition(glm::vec3 position)
{
	this->position = position;
}

void OpenGL::Transform3D::setLocalRotation(float angle, glm::vec3 axis)
{
	this->rotation = glm::normalize(glm::angleAxis(angle, axis));
}

void OpenGL::Transform3D::setLocalRotation(glm::quat rotation)
{
	this->rotation = glm::normalize(rotation);
}

void OpenGL::Transform3D::setLocalScale(glm::vec3 scale)
{
	this->scale = scale;
}

void OpenGL::Transform3D::setLocalScale(float scale)
{
	this->scale = glm::vec3(scale);
}

void OpenGL::Transform3D::setParent(Transform3D& transform)
{
	if (this->parent != nullptr)
		this->parent->clearChild(*this);

	this->parent = &transform;
	this->parent->addChild(*this);
}

void OpenGL::Transform3D::clearParent()
{
	if (this->parent != nullptr)
		this->parent->clearChild(*this);
	this->parent = nullptr;
}

void OpenGL::Transform3D::addChild(Transform3D& transform)
{
	this->children.push_back(&transform);
}

void OpenGL::Transform3D::clearChild(Transform3D& transform)
{
	this->children.erase(std::remove(this->children.begin(), this->children.end(), &transform), this->children.end());
}

glm::mat4 OpenGL::Transform3D::getLocalTransform() const
{
	glm::mat4 traMatrix = getTranslationMatrix();
	glm::mat4 scaleMatrix = getScaleMatrix();
	glm::mat4 rotMatrix = getRotationMatrix();

	return (traMatrix * rotMatrix * scaleMatrix);
}

glm::mat4 OpenGL::Transform3D::getWorldTransform() const
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

glm::mat4 OpenGL::Transform3D::getTranslationMatrix() const
{
	return glm::translate(this->position);
}

glm::mat4 OpenGL::Transform3D::getRotationMatrix() const
{
	return glm::toMat4(this->rotation);
}

glm::mat4 OpenGL::Transform3D::getScaleMatrix() const
{
	return glm::scale(this->scale);
}

glm::vec3 OpenGL::Transform3D::getFront() const
{
	return glm::normalize(this->rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 OpenGL::Transform3D::getUp() const
{
	return glm::normalize(glm::cross(getRight(), getFront()));
}

glm::vec3 OpenGL::Transform3D::getRight() const
{
	return glm::normalize(glm::cross(getFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 OpenGL::Transform3D::getBack() const
{
	return -getFront();
}

glm::vec3 OpenGL::Transform3D::getDown() const
{
	return -getUp();
}

glm::vec3 OpenGL::Transform3D::getLeft() const
{
	return -getRight();
}

void OpenGL::Transform3D::operator=(glm::mat4 const& matrix)
{
	this->position = matrix[3];
	this->rotation = glm::toQuat(matrix);
	this->scale = glm::vec3(glm::length(matrix[0]), glm::length(matrix[1]), glm::length(matrix[2]));
}
