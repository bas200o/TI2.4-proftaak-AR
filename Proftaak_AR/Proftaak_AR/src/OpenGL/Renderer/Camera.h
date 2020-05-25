#pragma once
#include "OpenGL/Renderer/Transform3D.h"
#include "OpenGL/windowhandling/Window.h"

namespace OpenGL {
	class Camera {
	public:
		Transform3D transform;

		Camera();
		void update(Window &window, float deltaTime);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix(Window& window);
		void rotate(float xoffset, float yoffset);
	private:
		float mouseSensitivity;
		float FOV;
		float nearClipPlaneDistance;
		float farClipPlaneDistance;
	};
}
