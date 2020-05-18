#pragma once

#include <GL/glew.h>

#include "ui/text/Text.h"
#include "../windowhandling/Window.h"

namespace OpenGL
{
	class Renderer
	{
	public:
		static void draw(Text& text, Window& window);
	};
}