#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include "EventHandler.h"

namespace OpenGL
{
	class Window
	{
	public:
		enum ClearType
		{
			COLOR_BUFFER = GL_COLOR_BUFFER_BIT,
			DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT
		};

		enum CursorMode
		{
			DISBALED = GLFW_CURSOR_DISABLED,
			HIDDEN = GLFW_CURSOR_HIDDEN,
			NORMAL = GLFW_CURSOR_NORMAL
		};

	private:
		GLFWwindow* glfwWindow;
		EventHandler* eventHandler;

		std::string title;
		unsigned int width;
		unsigned int height;

		float lastFrame;
		float deltatime;

		float lastX, lastY;
		bool firstMouse;

	public:
		Window(const char* title, const unsigned int width, const unsigned int height);
		~Window();

		bool show();
		void close();
		bool shouldClose();

		void update();
		void updateDeltaTime();

		inline void clear(const ClearType clearType) { glClear(clearType); }

		inline unsigned int getWidth() { return this->width; }
		inline unsigned int getHeight() { return this->height; }
		inline float getDeltaTime() { return this->deltatime; }
		inline EventHandler* getEventHandler() { return this->eventHandler; }

		inline void setClearColor(const glm::vec4 color) { glClearColor(color.x, color.y, color.x, color.w); }
		inline void setEventHandler(EventHandler* eventHandler) { this->eventHandler = eventHandler; }
		inline void setCursorMode(const CursorMode cursorMode) { glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, cursorMode); }
		bool isKeyDown(int key);

	private:
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};

	inline Window::ClearType operator|(Window::ClearType a, Window::ClearType b)
	{
		return static_cast<Window::ClearType>(static_cast<int>(a) | static_cast<int>(b));
	}
}