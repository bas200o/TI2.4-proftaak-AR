#include "Renderer.h"

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	text.unbind();
}



void OpenGL::Renderer::draw3D(RawModel& model, Shader& shader, Window& window, Camera& camera) {
	glEnable(GL_DEPTH_TEST);
	
	glm::vec3 lightpos(2.2f, 2.0f, -2.0f);
	glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);
	
	shader.bind();
	model.bind();

	setMVPUniforms(model.transform, window, shader, camera);

	
	shader.setUniformVec3f("lightPos", lightpos);
	shader.setUniformVec3f("lightColor", lightcolor);

	shader.setUniformVec3f("camPos", camera.transform.getWorldPosition());

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