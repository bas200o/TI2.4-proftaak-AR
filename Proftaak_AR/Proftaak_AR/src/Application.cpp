#include "Application.h"

Game::Application::Application()
	: window(OpenGL::Window("Test", 1280, 720))
{
	this->window.setEventHandler(this);
}

bool Game::Application::run()
{
	if (!this->window.show())
		return false;
	window.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);

		window.update();
	}

	return true;
}

void Game::Application::handleEvent(OpenGL::Event& event)
{
	switch (event.getEventType())
	{
		case OpenGL::Event::EventType::KeyReleasedEvent:
		{
			OpenGL::KeyReleasedEvent& keyReleasedEvent = static_cast<OpenGL::KeyReleasedEvent&>(event);
			if (keyReleasedEvent.getKey() == GLFW_KEY_ESCAPE)
				this->window.close();
			break;
		}
	}
}
