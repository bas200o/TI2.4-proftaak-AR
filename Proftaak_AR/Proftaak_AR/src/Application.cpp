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
	

	//OpenGL::OBJModelLoader modelLoader = OpenGL::OBJModelLoader();
	//modelLoader.loadModel("res/models/kart/Kart.obj");
	//OpenGL::RawModel model = modelLoader.getRawModel("Frame");
	//OpenGL::Transform3D transform;
	//transform.translateBy(glm::vec3(0.0f, 0.0f, -4.0f));

	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();

	//OpenGL::Shader shader = OpenGL::Shader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl");

	//unsigned int shaderId = renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl");
	//std::weak_ptr<OpenGL::Shader> shader = renderer.getRegisteredShader(shaderId);

	//std::weak_ptr<OpenGL::Texture2D> diffuseTexture = renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Diffuse.png"));
	//std::weak_ptr<OpenGL::Texture2D> specularTexture = renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Specular.png"));
	//std::weak_ptr<OpenGL::Texture2D> diffuseTextureMask = renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Color_Mask.png"));

	//shader.lock()->bind();
	//shader.lock()->setUniformVec3f("kartColor", glm::vec3(1.0f, 1.0f, 0.0f));
	//shader.lock()->setUniformBool("useDiffuseMap", true);
	//shader.lock()->setUniformBool("useSpecularMap", true);
	//shader.lock()->setUniformBool("useDiffuseMask", true);
	//shader.lock()->setUniform1i("diffuseMap", 0);
	//shader.lock()->setUniform1i("specularMap", 1);
	//shader.lock()->setUniform1i("diffuseMask", 2);
	//shader.lock()->unbind();

	//diffuseTexture.lock()->bind(0);
	//specularTexture.lock()->bind(1);
	//diffuseTextureMask.lock()->bind(2);

	kart = new GameLogic::Kart(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 5.0f, 2.0f, 4.0f);

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

		kart->update(deltatime);
		kart->draw(this->window, this->camera);

		//kart->transform.rotateBy(glm::pi<float>() * deltatime, glm::vec3(0.0f, 1.0f, 0.0f));
		//OpenGL::Renderer::draw3D(transform, model, *shader.lock(), this->window, camera);

		window.update();
	}

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
