#include "Renderer.h"

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.indicesCount, GL_UNSIGNED_INT, nullptr);

	text.unbind();
}