#pragma once
#include "Events.h"

namespace OpenGL
{
	class EventHandler
	{
	public:
		virtual void handleEvent(Event& event) = 0;
	};
}