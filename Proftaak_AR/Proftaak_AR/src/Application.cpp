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

	std::shared_ptr<OpenGL::Font> font = std::shared_ptr<OpenGL::Font>(new OpenGL::Font("Arial", "res/fonts"));
	this->text = new OpenGL::Text("", font, glm::vec2(10.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 500.0f, 5, glm::vec2(this->window.getWidth(), this->window.getHeight()));

	float counter = 0.0f;
	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);

		counter += deltatime;
		if (counter > 0.5f)
		{
			counter = 0.0f;
			this->text->setValue(std::string().append("FPS: ").append(std::to_string((int)(1.0 / deltatime))));
		}

		OpenGL::Renderer::draw(*this->text, this->window);

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
		case OpenGL::Event::EventType::WindowResizeEvent:
		{
			OpenGL::WindowResizeEvent& windowResizeEvent = static_cast<OpenGL::WindowResizeEvent&>(event);
			this->text->onWindowResize(glm::vec2(windowResizeEvent.getWidth(), windowResizeEvent.getHeight()));
			break;
		}
	}
}
