#pragma once

#include <memory>
#include <thread>

#include <GL/glew.h>

#include "OpenGL/windowhandling/Window.h"
#include "OpenGL/windowhandling/Events.h"
#include "OpenGL/windowhandling/EventHandler.h"
#include "OpenGL/Renderer/ui/text/Font.h"
#include "OpenGL/Renderer/ui/text/Text.h"
#include "OpenGL/Renderer/Renderer.h"
#include "OpenGL/Renderer/RawModel.h"
#include "OpenGL/Renderer/Camera.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

#include "gamelogic/gameobjects/Kart.h"
#include "gamelogic/gameobjects/Track.h"

#include "Vision/VisionCamera.h"

#include "Timer.h"

namespace GameLogic
{
	class Application : public OpenGL::EventHandler, public Vision::VisionCameraCallbackHandler
	{
	private:
		OpenGL::Window window;
		OpenGL::Camera camera;

		std::unique_ptr<GameLogic::Kart> kart;
		std::unique_ptr<OpenGL::Text> timeText;
		std::unique_ptr<OpenGL::Text> speedText;
		Vision::VisionCamera visionCamera;

		Timer timer;

	public:
		Application();

		bool run();

		virtual void handleEvent(OpenGL::Event& event) override;
		virtual void setAngle(float angle) override;
	};
}