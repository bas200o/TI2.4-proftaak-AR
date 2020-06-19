#include "Application.h"

#include "gamelogic/collision/CollisionDetector.h"

GameLogic::Application::Application() 
	: window(OpenGL::Window("Kart racing game", 1280, 720))
{
	this->window.setEventHandler(this);

	this->visionCamera.setCallbackHandler(this);
}

bool GameLogic::Application::run()
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

	std::shared_ptr<OpenGL::Font> font = std::make_shared<OpenGL::Font>("Arial", "res/fonts");
	this->timeText = std::make_unique<OpenGL::Text>("Time:", font, glm::vec2(5.0f, 5.0f), glm::vec3(1.0f), 20.0f, 500.0f, 1, glm::vec2(this->window.getWidth(), this->window.getHeight()));
	this->speedText = std::make_unique<OpenGL::Text>("Speed:", font, glm::vec2(5.0f, 35.0f), glm::vec3(1.0f), 20.0f, 500.0f, 1, glm::vec2(this->window.getWidth(), this->window.getHeight()));

	GameLogic::Track track(glm::vec3(0.0f, 0.0f, 0.0f), "Track_1");

	this->kart = std::make_unique<GameLogic::Kart>(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 50.0f, 10.0f, 20.0f);
	this->camera.transform.setParent(this->kart->transform);
	this->kart->transform.setLocalPosition(glm::vec3(-150.0f, 0.0f, 0.0f));
	this->camera.transform.setLocalPosition(glm::vec3(0.0f, 1.6f, -0.5f));
	
	std::thread listenerThread = std::thread(&Vision::VisionCamera::activateCamera, this->visionCamera);	// Start thread
	listenerThread.detach();	// Detach thread from main thread

	//GameLogic::SphereCollider testCollider(glm::vec3(0.0, 0.0f, 0.0f), 5.0f);
	//GameLogic::CubeCollider testCollider(glm::vec3(0.0, 0.0f, 0.0f), 5.0f, 5.0f, 5.0f);

	OpenGL::Renderer::window = &this->window;
	OpenGL::Renderer::camera = &this->camera;

	while (!window.shouldClose())
	{
		window.updateDeltaTime();
		float deltatime = window.getDeltaTime();
		window.clear(OpenGL::Window::ClearType::COLOR_BUFFER | OpenGL::Window::ClearType::DEPTH_BUFFER);
		this->time.addSeconds(deltatime);
		this->camera.update(this->window, deltatime);

		track.draw(this->window, this->camera);

		kart->update(deltatime);
		//kart->checkCollision(testCollider);
		for(std::shared_ptr<Collider> collider : track.getColliders())
			kart->checkCollision(*collider.get());
		kart->draw(this->window, this->camera);

		//this->text->setValue(std::string("Speed: ").append(std::to_string(this->kart->getSpeed())).append(" m/s"));
		this->timeText->setValue(std::string("Time: ").append(this->time.getString()));
		this->speedText->setValue(std::string("Speed: ").append(std::to_string((int)((this->kart->getSpeed() * 3600.0f) / 1000.0f))).append(" km/h"));
		OpenGL::Renderer::draw(*this->timeText, this->window);
		OpenGL::Renderer::draw(*this->speedText, this->window);

		//OpenGL::Renderer::drawDebugCube(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f), this->window, this->camera);
		//OpenGL::Renderer::drawDebugSphere(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), 5.0f, this->window, this->camera);

		window.update();
	}

	return true;
}

void GameLogic::Application::handleEvent(OpenGL::Event& event)
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
			//if (keyPressedEvent.getKey() == GLFW_KEY_RIGHT_CONTROL)
			//	this->kart->setIsAccelarating(true);
			//if (keyPressedEvent.getKey() == GLFW_KEY_LEFT_CONTROL)
			//	this->kart->setIsBraking(true);
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
			//if (keyReleasedEvent.getKey() == GLFW_KEY_RIGHT_CONTROL)
			//	this->kart->setIsAccelarating(false);
			//if (keyReleasedEvent.getKey() == GLFW_KEY_LEFT_CONTROL)
			//	this->kart->setIsBraking(false);
			break;
		}
		case OpenGL::Event::EventType::WindowResizeEvent:
		{
			OpenGL::WindowResizeEvent& windowResizeEvent = static_cast<OpenGL::WindowResizeEvent&>(event);
			if (this->timeText != nullptr)
				this->timeText->onWindowResize(glm::vec2(windowResizeEvent.getWidth(), windowResizeEvent.getHeight()));
			if (this->speedText != nullptr)
				this->speedText->onWindowResize(glm::vec2(windowResizeEvent.getWidth(), windowResizeEvent.getHeight()));
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

void GameLogic::Application::setAngle(float angle)
{
	float clampedAngle = glm::clamp(angle, -1.0f, 1.0f);

	this->kart->steer(clampedAngle * 25);
}