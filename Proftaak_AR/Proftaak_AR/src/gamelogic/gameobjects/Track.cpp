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
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(192.4f, 0.0f, -1.08f), 92.0f, 5.0f, 33.2f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(248.87f, 0.0f, -0.0f), 31.192f, 5.0f, 420.16f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-193.1f, 0.0f, -0.0f), 31.192f, 5.0f, 420.16f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(28.02f, 0.0f, -211.378f), 466.26f, 5.0f, 39.24f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(28.02f, 0.0f, 206.48f), 466.26f, 5.0f, 39.24f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-93.08f, 0.0f, -5.8f), 33.886f, 5.0f, 275.15f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-84.35f, 0.0f, -63.49f), 33.886f, 5.0f, 159.37f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-28.39f, 0.0f, -52.48f), 85.86f, 5.0f, 20.84f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(54.89f, 0.0f, -56.99f), 96.24f, 5.0f, 11.80f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(103.1f, 0.0f, -65.95f), 24.88f, 5.0f, 11.906f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(115.48f, 0.0f, -74.93f), 24.88f, 5.0f, 11.906f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(140.91f, 0.0f, -101.12f), 44.76f, 5.0f, 64.28f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(37.79f, 0.0f, 93.8f), 245.44f, 5.0f, 14.056f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-66.2f, 0.0f, 111.15f), 41.08f, 5.0f, 41.08f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(133.59f, 0.0f, 107.4f), 53.74f, 5.0f, 24.4f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(28.61f, 0.0f, -163.27f), 46.588f, 5.0f, 106.16f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-111.57f, 0.0f, -30.73f), 15.50f, 5.0f, 195.76f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(-79.26f, 0.0f, 139.26f), 6.24f, 5.0f, 29.08f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(30.11f, 0.0f, 175.91f), 6.6f, 5.0f, 29.08f));
	this->colliders.push_back(std::make_shared<CubeCollider>(glm::vec3(30.11f, 0.0f, 145.74f), 6.6f, 5.0f, 19.12f));
}