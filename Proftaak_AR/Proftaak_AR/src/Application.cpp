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

	OpenGL::OBJModelLoader modelLoader = OpenGL::OBJModelLoader();
	modelLoader.loadModel("res/models/kart/Kart.obj");
	OpenGL::RawModel model = modelLoader.getRawModel("Frame");
	model.transform.translateBy(glm::vec3(0.0f, 0.0f, -4.0f));

	OpenGL::Shader shader = OpenGL::Shader("res/shaders/vertex/VertexShader.glsl", "res/shaders/fragment/FragmentShader.glsl");

	float counter = 0.0f;
	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);

		model.transform.rotateBy(glm::pi<float>() * deltatime, glm::vec3(0.0f, 1.0f, 0.0f));
		OpenGL::Renderer::draw3D(model, shader, this->window);

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
