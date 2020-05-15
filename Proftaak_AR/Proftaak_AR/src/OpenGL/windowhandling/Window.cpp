#include "Window.h"

OpenGL::Window::Window(const char* title, const unsigned int width, const unsigned int height)
	: title(title), width(width), height(height)
{
	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
	this->firstMouse = true;
	this->eventHandler = nullptr;
	this->deltatime = 0.0f;
}

OpenGL::Window::~Window()
{
	close();
	glfwTerminate();
}

bool OpenGL::Window::show()
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->glfwWindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	if (this->glfwWindow == nullptr)
	{
		close();
		return false;
	}

	glfwMakeContextCurrent(this->glfwWindow);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(this->glfwWindow, this);
	glfwSetFramebufferSizeCallback(this->glfwWindow, Window::framebufferSizeCallback);
	glfwSetCursorPosCallback(this->glfwWindow, Window::mouseCallback);
	glfwSetScrollCallback(this->glfwWindow, Window::scrollCallback);
	glfwSetMouseButtonCallback(this->glfwWindow, Window::mouseButtonCallback);
	glfwSetKeyCallback(this->glfwWindow, Window::keyCallback);

	setCursorMode(CursorMode::NORMAL);

	return true;
}

void OpenGL::Window::close()
{
	glfwSetWindowShouldClose(this->glfwWindow, true);
}

bool OpenGL::Window::shouldClose()
{
	return glfwWindowShouldClose(this->glfwWindow);
}

void OpenGL::Window::update()
{
	glfwSwapBuffers(this->glfwWindow);
	glfwPollEvents();
}

void OpenGL::Window::updateDeltaTime()
{
	float currentFrame = glfwGetTime();
	this->deltatime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;
}

void OpenGL::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);

	glViewport(0, 0, width, height);

	windowObj.width = width;
	windowObj.height = height;

	if (windowObj.getEventHandler() != nullptr)
	{
		WindowResizeEvent event = WindowResizeEvent(width, height);
		windowObj.getEventHandler()->handleEvent(event);
	}
}

void OpenGL::Window::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);

	if (windowObj.firstMouse)
	{
		windowObj.lastX = xpos;
		windowObj.lastY = ypos;
		windowObj.firstMouse = false;
	}

	float xoffset = xpos - windowObj.lastX;
	float yoffset = windowObj.lastY - ypos;

	windowObj.lastX = xpos;
	windowObj.lastY = ypos;

	if (windowObj.getEventHandler() != nullptr)
	{
		MouseMovedEvent event = MouseMovedEvent(xoffset, yoffset);
		windowObj.getEventHandler()->handleEvent(event);
	}
}

void OpenGL::Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);

	if (windowObj.getEventHandler() != nullptr)
	{
		MouseScrollEvent event = MouseScrollEvent(yoffset);
		windowObj.getEventHandler()->handleEvent(event);
	}
}

void OpenGL::Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);

	if (windowObj.getEventHandler() != nullptr)
	{
		if (action == GLFW_PRESS)
		{
			KeyPressedEvent event = KeyPressedEvent(key);
			windowObj.getEventHandler()->handleEvent(event);
		}
		else if (action == GLFW_RELEASE)
		{
			KeyReleasedEvent event = KeyReleasedEvent(key);
			windowObj.getEventHandler()->handleEvent(event);
		}
	}
}

void OpenGL::Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window& windowObj = *(Window*)glfwGetWindowUserPointer(window);

	if (windowObj.getEventHandler() != nullptr)
	{
		if (action == GLFW_PRESS)
		{
			MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
			windowObj.getEventHandler()->handleEvent(event);
		}
		else if (action == GLFW_RELEASE)
		{
			MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
			windowObj.getEventHandler()->handleEvent(event);
		}
	}
}
