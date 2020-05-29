#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "../OpenGL/Renderer/shading/Shader.h"
#include "Transform3D.h"


namespace OpenGL
{
	class RawModel
	{	
	public:
		Transform3D transform;

	private: 
		unsigned int vaoID;
		unsigned int vertexCount;
		unsigned int indexBuffer;
		unsigned int vertexBuffer;

		std::vector<unsigned int> indices;
		std::vector<glm::vec3> positions; 
		std::vector<glm::vec3> normals; 
		std::vector<glm::vec2> textureCoords;

		std::string name;

	public:
		RawModel(std::string name, std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices);
		RawModel(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices);
		
		void unbind();
		void bind();

		int getIndexCount() { return this->indices.size(); };

	private:
		void genBuffers();
		std::vector<float> createVertices();
	};
}