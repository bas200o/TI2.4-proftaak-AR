#include "Renderer.h"

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.indicesCount, GL_UNSIGNED_INT, nullptr);

	text.unbind();
}

void OpenGL::Renderer::draw3D(RawModel& model, Shader& shader, Window& window, Camera& camera) {
	glEnable(GL_DEPTH_TEST);
	
	shader.bind();
	model.bind();

	setMVPUniforms(model.transform, window, shader, camera);

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.unbind();
	model.unbind();
}

void OpenGL::Renderer::setMVPUniforms(Transform3D& modelTranform, Window& window, Shader& shader, Camera& camera)
{
	shader.setUniformMat4f("model", modelTranform.getWorldTransform());
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix(window));
}