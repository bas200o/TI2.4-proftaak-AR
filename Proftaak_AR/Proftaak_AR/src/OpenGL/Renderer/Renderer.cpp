#include "Renderer.h"

OpenGL::Renderer::Renderer()
	: lastShaderId(0), lastTextureId(0), lastModelId(0)
{

}

void OpenGL::Renderer::draw(Text& text, Window& window)
{
	glDisable(GL_DEPTH_TEST);

	text.bind();

	glDrawElements(GL_TRIANGLES, text.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	text.unbind();
}

void OpenGL::Renderer::draw3D(Transform3D& modelTranform, RawModel& model, Shader& shader, Window& window, Camera& camera)
{
	glEnable(GL_DEPTH_TEST);
	
	glm::vec3 lightpos(2.2f, 2.0f, -2.0f);
	glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);
	
	shader.bind();
	model.bind();

	setMVPUniforms(modelTranform, window, shader, camera);

	
	shader.setUniformVec3f("lightPos", lightpos);
	shader.setUniformVec3f("lightColor", lightcolor);

	shader.setUniformVec3f("camPos", camera.transform.getWorldPosition());

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.unbind();
	model.unbind();
}

void OpenGL::Renderer::draw3D(Transform3D& modelTranform, RawModel& model, unsigned int shaderId, Window& window, Camera& camera)
{
	glEnable(GL_DEPTH_TEST);

	glm::vec3 lightpos(2.2f, 2.0f, -2.0f);
	glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);

	std::weak_ptr<OpenGL::Shader> shader = getInstance().getRegisteredShader(shaderId);
	shader.lock()->bind();
	model.bind();

	setMVPUniforms(modelTranform, window, *shader.lock().get(), camera);


	shader.lock()->setUniformVec3f("lightPos", lightpos);
	shader.lock()->setUniformVec3f("lightColor", lightcolor);

	shader.lock()->setUniformVec3f("camPos", camera.transform.getWorldPosition());

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.lock()->unbind();
	model.unbind();
}

void OpenGL::Renderer::setMVPUniforms(Transform3D& modelTranform, Window& window, Shader& shader, Camera& camera)
{
	shader.setUniformMat4f("model", modelTranform.getWorldTransform());
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix(window));
}

unsigned int OpenGL::Renderer::registerShader(const std::string vertexPath, const std::string fragmentPath)
{
	std::string combinedPath = std::string(vertexPath).append(fragmentPath);
	if (registeredFilepaths.find(combinedPath) != registeredFilepaths.end())
		return registeredFilepaths[combinedPath];

	registeredShaders[++lastShaderId] = std::make_shared<OpenGL::Shader>(vertexPath, fragmentPath);
	registeredFilepaths[combinedPath] = lastShaderId;
	return lastShaderId;
}

unsigned int OpenGL::Renderer::registerTexture(const std::string texturePath)
{
	if (registeredFilepaths.find(texturePath) != registeredFilepaths.end())
		return registeredFilepaths[texturePath];

	registeredTextures[++lastTextureId] = std::make_shared<OpenGL::Texture2D>(texturePath);
	registeredFilepaths[texturePath] = lastTextureId;
	return lastTextureId;
}

unsigned int OpenGL::Renderer::registerModel(const std::string name, const std::vector<glm::vec3> positions, const std::vector<glm::vec3> normals, const std::vector<glm::vec2> textureCoords, const std::vector<unsigned int> indices)
{
	if (registeredFilepaths.find(name) != registeredFilepaths.end())
		return registeredFilepaths[name];

	registeredModels[++lastModelId] = std::make_shared<OpenGL::RawModel>(name, positions, normals, textureCoords, indices);
	registeredFilepaths[name] = lastModelId;
	return lastModelId;
}

std::weak_ptr<OpenGL::Shader> OpenGL::Renderer::getRegisteredShader(const unsigned int shaderId)
{
	if (registeredShaders.find(shaderId) != registeredShaders.end())
		return registeredShaders[shaderId];

	return std::weak_ptr<OpenGL::Shader>();
}

std::weak_ptr<OpenGL::Texture2D> OpenGL::Renderer::getRegisteredTexture(const unsigned int textureId)
{
	if (registeredTextures.find(textureId) != registeredTextures.end())
		return registeredTextures[textureId];

	return std::weak_ptr<OpenGL::Texture2D>();
}

std::weak_ptr<OpenGL::RawModel> OpenGL::Renderer::getRegisteredModel(const unsigned int modelId)
{
	if (registeredModels.find(modelId) != registeredModels.end())
		return registeredModels[modelId];

	return std::weak_ptr<RawModel>();
}

std::weak_ptr<OpenGL::RawModel> OpenGL::Renderer::getRegisteredModel(const std::string modelName)
{
	if (registeredFilepaths.find(modelName) != registeredFilepaths.end())
	{
		unsigned int modelId = registeredFilepaths[modelName];
		if (registeredModels.find(modelId) != registeredModels.end())
			return registeredModels[modelId];
	}

	return std::weak_ptr<RawModel>();
}

OpenGL::Renderer& OpenGL::Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}