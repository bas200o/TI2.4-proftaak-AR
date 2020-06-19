#include "Track.h"

GameLogic::Track::Track(const glm::vec3 position, const std::string trackName)
{
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	OpenGL::OBJModelLoader modelLoader = OpenGL::OBJModelLoader();
	modelLoader.loadModel(std::string("res/models/tracks/").append(trackName), trackName);

	// Track
	std::vector<OpenGL::OBJModelLoader::Mesh> meshes = modelLoader.getLoadedMeshes();
	for (OpenGL::OBJModelLoader::Mesh mesh : meshes)
	{
		if (renderer.getRegisteredModel(mesh.name).expired())
		{
			std::weak_ptr<OpenGL::RawModel> model = renderer.getRegisteredModel(renderer.registerModel(mesh.name, mesh.Positions, mesh.Normals, mesh.UVCoordinates, mesh.Indices));

			std::vector<std::weak_ptr<OpenGL::Texture2D>> textures;
			if (mesh.textureFilePath != "")
			{
				textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture(mesh.textureFilePath)));
				textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture(std::string("res/textures/tracks/").append(trackName).append("SpecularMap.png"))));
			}

			OpenGL::Transform3D* modelTransform = new OpenGL::Transform3D();
			modelTransform->setParent(this->transform);
			this->models.push_back({ modelTransform, model, textures, true });
		}
	}

	// Skybox
	modelLoader.loadModel(std::string("res/models/tracks/").append(trackName), std::string("Skybox_").append(trackName));
	meshes = modelLoader.getLoadedMeshes();
	for (OpenGL::OBJModelLoader::Mesh mesh : meshes)
	{
		if (renderer.getRegisteredModel(mesh.name).expired())
		{
			std::weak_ptr<OpenGL::RawModel> model = renderer.getRegisteredModel(renderer.registerModel(mesh.name, mesh.Positions, mesh.Normals, mesh.UVCoordinates, mesh.Indices));

			std::vector<std::weak_ptr<OpenGL::Texture2D>> textures;
			if (mesh.textureFilePath != "")
			{
				textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture(mesh.textureFilePath)));
				textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture(std::string("res/textures/tracks/").append(trackName).append("SpecularMap.png"))));
			}

			OpenGL::Transform3D* modelTransform = new OpenGL::Transform3D();
			modelTransform->setParent(this->transform);
			this->models.push_back({ modelTransform, model, textures, false });
		}
	}

	this->transform.translateBy(position);

	setupColliders();
}

GameLogic::Track::~Track()
{

}

void GameLogic::Track::update(float deltatime)
{

}

void GameLogic::Track::setRequiredUniforms(TMTPair& tmPair)
{
	this->shader.lock()->bind();
	this->shader.lock()->setUniformBool("useDiffuseMap", false);
	this->shader.lock()->setUniformBool("useSpecularMap", false);
	if (tmPair.textures.size() > 0)
	{
		this->shader.lock()->setUniformBool("useDiffuseMap", true);
		this->shader.lock()->setUniform1i("diffuseMap", 0);
	}
	if (tmPair.textures.size() > 1)
	{
		this->shader.lock()->setUniformBool("useSpecularMap", true);
		this->shader.lock()->setUniform1i("specularMap", 1);
	}
	this->shader.lock()->setUniformBool("useLighting", tmPair.useLighting);
	this->shader.lock()->unbind();
}

void GameLogic::Track::onCollision()
{

}

void GameLogic::Track::setupColliders()
{
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(48.05f, 0.0f, 24.95f), 84.5f, 5.0f, 17.2f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(50.73f, 0.0f, 10.8f), 64.8f, 5.0f, 12.77f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(158.68f, 0.0f, 8.55f), 155.776f, 5.0f, 33.224f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(158.68f, 0.0f, 8.55f), 155.776f, 5.0f, 33.224f));
}