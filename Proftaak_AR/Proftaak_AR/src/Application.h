#pragma once

#include "OpenGL/windowhandling/Window.h"
#include "OpenGL/windowhandling/Events.h"
#include "OpenGL/windowhandling/EventHandler.h"

namespace Game
{
	class Application : public OpenGL::EventHandler
	{
	private:
		OpenGL::Window window;

	public:
		Application();

		bool run();

		virtual void handleEvent(OpenGL::Event& event) override;
	};
}