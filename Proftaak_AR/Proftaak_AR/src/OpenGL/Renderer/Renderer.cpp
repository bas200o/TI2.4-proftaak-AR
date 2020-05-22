#include "Renderer.h"

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.indicesCount, GL_UNSIGNED_INT, nullptr);

	text.unbind();
}

void OpenGL::Renderer::draw3D(RawModel& model, Shader& shader, Window& window) {
	glEnable(GL_DEPTH_TEST);
	
	shader.bind();
	model.bind();

	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)window.getWidth() / (float)window.getHeight(), 0.01f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 modelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -4.0f));
	shader.setUniformMat4f("model", modelMatrix);
	shader.setUniformMat4f("view", view);
	shader.setUniformMat4f("projection", projection);

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);
	
	shader.unbind();
	model.unbind();

	
}