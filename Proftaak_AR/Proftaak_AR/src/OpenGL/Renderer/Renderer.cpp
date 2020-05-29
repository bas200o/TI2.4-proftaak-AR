#include "Renderer.h"

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	text.unbind();
}

void OpenGL::Renderer::draw3D(RawModel& model, Shader& shader, Window& window) {
	glEnable(GL_DEPTH_TEST);

	shader.bind();
	model.bind();

	setMVPUniforms(model.transform, window, shader);

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.unbind();
	model.unbind();
}

void OpenGL::Renderer::setMVPUniforms(Transform3D& modelTranform, Window& window, Shader& shader)
{
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)window.getWidth() / (float)window.getHeight(), 0.01f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	shader.setUniformMat4f("model", modelTranform.getWorldTransform());
	shader.setUniformMat4f("view", view);
	shader.setUniformMat4f("projection", projection);
}