#include "Application.h"

Game::Application::Application() : window(OpenGL::Window("Test", 1280, 720))
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

	OpenGL::Shader shader = OpenGL::Shader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl");

	OpenGL::Texture2D diffuseTexture = OpenGL::Texture2D("res/textures/kart/Kart_Diffuse.png");
	OpenGL::Texture2D specularTexture = OpenGL::Texture2D("res/textures/kart/Kart_Specular.png");
	OpenGL::Texture2D diffuseTextureMask = OpenGL::Texture2D("res/textures/kart/Kart_Color_Mask.png");

	shader.bind();
	shader.setUniformVec3f("kartColor", glm::vec3(1.0f, 1.0f, 0.0f));
	shader.setUniformBool("useDiffuseMap", true);
	shader.setUniformBool("useSpecularMap", true);
	shader.setUniformBool("useDiffuseMask", true);
	shader.setUniform1i("diffuseMap", 0);
	shader.setUniform1i("specularMap", 1);
	shader.setUniform1i("diffuseMask", 2);
	shader.unbind();

	diffuseTexture.bind(0);
	specularTexture.bind(1);
	diffuseTextureMask.bind(2);

	this->camera = OpenGL::Camera();
	float counter = 0.0f;

	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);
		//OpenGL::Renderer::draw(*this->text, this->window);
		//OpenGL::Renderer::draw3D(model, shader, this->window, camera);
		this->camera.update(this->window, deltatime);

		model.transform.rotateBy(glm::pi<float>() * deltatime, glm::vec3(0.0f, 1.0f, 0.0f));
		OpenGL::Renderer::draw3D(model, shader, this->window, camera);

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
			if (text != nullptr)
			{
				this->text->onWindowResize(glm::vec2(windowResizeEvent.getWidth(), windowResizeEvent.getHeight()));
			}
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
