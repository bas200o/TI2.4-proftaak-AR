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
	if (glewInit() != GLEW_OK)
		return false;
	window.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	kart = new GameLogic::Kart(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 5.0f, 2.0f, 4.0f);

	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);

		this->camera.update(this->window, deltatime);

		kart->update(deltatime);
		kart->draw(this->window, this->camera);

		window.update();
	}

	delete this->kart;

	return true;
}

void Game::Application::handleEvent(OpenGL::Event& event)
{
	switch (event.getEventType())
	{
		case OpenGL::Event::EventType::KeyPressedEvent:
		{
			OpenGL::KeyPressedEvent& keyPressedEvent = static_cast<OpenGL::KeyPressedEvent&>(event);
			if (keyPressedEvent.getKey() == GLFW_KEY_UP)
				this->kart->setIsAccelarating(true);
			if (keyPressedEvent.getKey() == GLFW_KEY_DOWN)
				this->kart->setIsBraking(true);
			if (keyPressedEvent.getKey() == GLFW_KEY_LEFT)
				this->kart->steer(20.0f);
			if (keyPressedEvent.getKey() == GLFW_KEY_RIGHT)
				this->kart->steer(-20.0f);
			break;
		}
		case OpenGL::Event::EventType::KeyReleasedEvent:
		{
			OpenGL::KeyReleasedEvent& keyReleasedEvent = static_cast<OpenGL::KeyReleasedEvent&>(event);
			if (keyReleasedEvent.getKey() == GLFW_KEY_ESCAPE)
				this->window.close();

			if (keyReleasedEvent.getKey() == GLFW_KEY_UP)
				this->kart->setIsAccelarating(false);
			if (keyReleasedEvent.getKey() == GLFW_KEY_DOWN)
				this->kart->setIsBraking(false);
			if (keyReleasedEvent.getKey() == GLFW_KEY_LEFT)
				this->kart->steer(0.0f);
			if (keyReleasedEvent.getKey() == GLFW_KEY_RIGHT)
				this->kart->steer(0.0f);
			break;
		}
		case OpenGL::Event::EventType::WindowResizeEvent:
		{
			OpenGL::WindowResizeEvent& windowResizeEvent = static_cast<OpenGL::WindowResizeEvent&>(event);
			//if (text != nullptr)
			//	this->text->onWindowResize(glm::vec2(windowResizeEvent.getWidth(), windowResizeEvent.getHeight()));
			break;
		}
		case OpenGL::Event::EventType::MouseMovedEvent:
		{
			OpenGL::MouseMovedEvent& moved = static_cast<OpenGL::MouseMovedEvent&>(event);
			this->camera.rotate(moved.getXOffset(), moved.getYOffset());
			break;
		}
	}
}
