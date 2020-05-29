#include "OpenGL/Renderer/Camera.h"

OpenGL::Camera::Camera()
{
	FOV = 45.0f;
	nearClipPlaneDistance = 0.01f;
	farClipPlaneDistance = 1000.0f;
	mouseSensitivity = 0.2;
};

void OpenGL::Camera::update(Window &window, float deltaTime) {
	
	float cameraSpeed = 2.5;
	
	if (window.isKeyDown(GLFW_KEY_W)) {
		this->transform.translateBy(this->transform.getFront() * (cameraSpeed * deltaTime));
	}
	if (window.isKeyDown(GLFW_KEY_A)) {
		this->transform.translateBy(this->transform.getLeft() * (cameraSpeed * deltaTime));
	}
	if (window.isKeyDown(GLFW_KEY_S)) {
		this->transform.translateBy(this->transform.getBack() * (cameraSpeed * deltaTime));
	}
	if (window.isKeyDown(GLFW_KEY_D)) {
		this->transform.translateBy(this->transform.getRight() * (cameraSpeed * deltaTime));
	}
	if (window.isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		this->transform.translateBy(this->transform.getDown() * (cameraSpeed * deltaTime));
	}
	if (window.isKeyDown(GLFW_KEY_SPACE)) {
		this->transform.translateBy(this->transform.getUp() * (cameraSpeed * deltaTime));
	}
}

glm::mat4 OpenGL::Camera::getViewMatrix() {
	return glm::lookAt(this->transform.getWorldPosition(), this->transform.getWorldPosition() + this->transform.getFront(), this->transform.getUp());
}

glm::mat4 OpenGL::Camera::getProjectionMatrix(Window &window) {
	return glm::perspective(glm::radians(this->FOV), (float)window.getWidth() / (float)window.getHeight(), this->nearClipPlaneDistance, this->farClipPlaneDistance);
}

void OpenGL::Camera::rotate(float xoffset, float yoffset) {
	xoffset *= this->mouseSensitivity;
	yoffset *= this->mouseSensitivity;

	this->transform.rotateBy(glm::radians(yoffset), this->transform.getRight());
	this->transform.rotateBy(-glm::radians(xoffset), glm::vec3(0.0f, 1.0f, 0.0f));
}