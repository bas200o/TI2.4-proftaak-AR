#include "Renderer.h"

OpenGL::Window* OpenGL::Renderer::window;
OpenGL::Camera* OpenGL::Renderer::camera;
bool OpenGL::Renderer::drawDebug = false;

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
	
	glm::vec3 lightDir(1.0f, 1.0f, 1.0f);
	glm::normalize(lightDir);
	glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);
	
	
	shader.bind();
	model.bind();

	setMVPUniforms(modelTranform, window, shader, camera);

	
	shader.setUniformVec3f("lightDir", lightDir);
	shader.setUniformVec3f("lightColor", lightcolor);

	shader.setUniformVec3f("camPos", camera.transform.getWorldPosition());

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.unbind();
	model.unbind();
}

void OpenGL::Renderer::draw3D(Transform3D& modelTranform, RawModel& model, unsigned int shaderId, Window& window, Camera& camera)
{
	glEnable(GL_DEPTH_TEST);

	glm::vec3 lightDir(1.0f, 1.0f, 1.0f);
	glm::normalize(lightDir);
	glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);

	std::weak_ptr<OpenGL::Shader> shader = getInstance().getRegisteredShader(shaderId);
	shader.lock()->bind();
	model.bind();

	setMVPUniforms(modelTranform, window, *shader.lock().get(), camera);


	shader.lock()->setUniformVec3f("lightDir", lightDir);
	shader.lock()->setUniformVec3f("lightColor", lightcolor);

	shader.lock()->setUniformVec3f("camPos", camera.transform.getWorldPosition());

	glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	shader.lock()->unbind();
	model.unbind();
}

void OpenGL::Renderer::drawDebugCube(const glm::vec3 color, const glm::vec3 position, const glm::vec3 size, Window& window, Camera& camera)
{
	if (drawDebug)
	{
		glDisable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Renderer& renderer = Renderer::getInstance();
		std::weak_ptr<Shader> shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Debug.glsl"));

		std::weak_ptr<RawModel> rawModel = renderer.getRegisteredModel("DebugCube");
		if (rawModel.expired())
		{
			OBJModelLoader modelLoader = OBJModelLoader();
			modelLoader.loadModel("res/models/debug", "DebugCube");
			OBJModelLoader::Mesh mesh = modelLoader.getLoadedMeshes()[0];
			rawModel = renderer.getRegisteredModel(renderer.registerModel("DebugCube", mesh.Positions, mesh.Normals, mesh.UVCoordinates, mesh.Indices));
		}

		shader.lock()->bind();
		rawModel.lock()->bind();
		shader.lock()->setUniformVec3f("debugColor", color);
		shader.lock()->setUniformMat4f("model", (glm::translate(position) * glm::scale(size)));
		shader.lock()->setUniformMat4f("view", camera.getViewMatrix());
		shader.lock()->setUniformMat4f("projection", camera.getProjectionMatrix(window));

		glDrawElements(GL_TRIANGLES, rawModel.lock()->getIndexCount(), GL_UNSIGNED_INT, nullptr);

		rawModel.lock()->unbind();
		shader.lock()->unbind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
	}
}

void OpenGL::Renderer::drawDebugSphere(const glm::vec3 color, const glm::vec3 position, const float radius, Window& window, Camera& camera)
{
	if (drawDebug)
	{
		glDisable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Renderer& renderer = Renderer::getInstance();
		std::weak_ptr<Shader> shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Debug.glsl"));

		std::weak_ptr<RawModel> rawModel = renderer.getRegisteredModel("DebugSphere");
		if (rawModel.expired())
		{
			OBJModelLoader modelLoader = OBJModelLoader();
			modelLoader.loadModel("res/models/debug", "DebugSphere");
			OBJModelLoader::Mesh mesh = modelLoader.getLoadedMeshes()[0];
			rawModel = renderer.getRegisteredModel(renderer.registerModel("DebugSphere", mesh.Positions, mesh.Normals, mesh.UVCoordinates, mesh.Indices));
		}

		shader.lock()->bind();
		rawModel.lock()->bind();
		shader.lock()->setUniformVec3f("debugColor", color);
		shader.lock()->setUniformMat4f("model", (glm::translate(position) * glm::scale(glm::vec3(radius))));
		shader.lock()->setUniformMat4f("view", camera.getViewMatrix());
		shader.lock()->setUniformMat4f("projection", camera.getProjectionMatrix(window));

		glDrawElements(GL_TRIANGLES, rawModel.lock()->getIndexCount(), GL_UNSIGNED_INT, nullptr);

		rawModel.lock()->unbind();
		shader.lock()->unbind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
	}
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