#pragma once

#include <GL/glew.h>
#include <memory>

#include "OpenGL/windowhandling/Window.h"
#include "OpenGL/windowhandling/Events.h"
#include "OpenGL/windowhandling/EventHandler.h"

#include "OpenGL/Renderer/ui/text/Font.h"
#include "OpenGL/Renderer/ui/text/Text.h"
#include "OpenGL/Renderer/Renderer.h"

#include "OpenGL/Renderer/RawModel.h"
#include "OpenGL/Renderer/Camera.h"

namespace Game
{
	class Application : public OpenGL::EventHandler
	{
	private:
		OpenGL::Window window;
		OpenGL::Text* text;
		OpenGL::Camera camera;

	public:
		Application();

		bool run();

		virtual void handleEvent(OpenGL::Event& event) override;
	};
}