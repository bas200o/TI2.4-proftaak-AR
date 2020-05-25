#pragma once

#include <GL/glew.h>
#include "OpenGL/Renderer/RawModel.h"
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

#include "ui/text/Text.h"
#include "../windowhandling/Window.h"
#include "Transform3D.h"

namespace OpenGL
{
	class Renderer
	{
	public:
		static void draw(Text& text, Window& window);
		static void draw3D(RawModel& model, Shader& shader, Window& window);

	private:
		static void setMVPUniforms(Transform3D& modelTranform, Window& window, Shader& shader);
	};
}