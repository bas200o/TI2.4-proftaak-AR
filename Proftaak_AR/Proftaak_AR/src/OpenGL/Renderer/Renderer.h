#pragma once

#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include "OpenGL/Renderer/RawModel.h"
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

#include "ui/text/Text.h"
#include "../windowhandling/Window.h"
#include "Transform3D.h"
#include "OpenGL/Renderer/Camera.h"

#include "OpenGL/Renderer/shading/Shader.h"
#include "OpenGL/Renderer/shading/Texture2D.h"

namespace OpenGL
{
	class Renderer
	{
		// Registerd resources
		std::unordered_map<std::string, unsigned int> registeredFilepaths;
		std::unordered_map<unsigned int, std::shared_ptr<Shader>> registeredShaders;
		std::unordered_map<unsigned int, std::shared_ptr<Texture2D>> registeredTextures;
		std::unordered_map<unsigned int, std::shared_ptr<RawModel>> registeredModels;

		unsigned int lastShaderId;
		unsigned int lastTextureId;
		unsigned int lastModelId;

	private:
		Renderer();
		Renderer(Renderer const&) = delete;

	public:
		static void draw(Text& text, Window& window);
		static void draw3D(Transform3D& modelTranform, RawModel& model, Shader& shader, Window& window, Camera& camera);
		static void draw3D(Transform3D& modelTranform, RawModel& model, unsigned int shaderId, Window& window, Camera& camera);
		static void drawDebugCube(Transform3D& modelTranform, Window& window, Camera& camera);
		static void drawDebugSphere(Transform3D& modelTranform, Window& window, Camera& camera);

	private:
		static void setMVPUniforms(Transform3D& modelTranform, Window& window, Shader& shader, Camera& camera);

	public:
		unsigned int registerShader(const std::string vertexPath, const std::string fragmentPath);
		unsigned int registerTexture(const std::string texturePath);
		unsigned int registerModel(const std::string name, const std::vector<glm::vec3> positions, const std::vector<glm::vec3> normals, const std::vector<glm::vec2> textureCoords, const std::vector<unsigned int> indices);

		std::weak_ptr<Shader> getRegisteredShader(const unsigned int shaderId);
		std::weak_ptr<Texture2D> getRegisteredTexture(const unsigned int textureId);
		std::weak_ptr<RawModel> getRegisteredModel(const unsigned int modelId);
		std::weak_ptr<RawModel> getRegisteredModel(const std::string modelName);

		static Renderer& getInstance();

		void operator=(Renderer const&) = delete;
	};
}