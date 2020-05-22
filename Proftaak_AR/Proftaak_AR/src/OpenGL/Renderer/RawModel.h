#pragma once
#include "../OpenGL/Renderer/shading/Shader.h"
#include <vector>
#include <algorithm>


namespace OpenGL
{
	class RawModel
	{
		
	private: 
		unsigned int vaoID;
		unsigned int vertexCount;
		unsigned int indexBuffer;
		unsigned int vertexBuffer;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> positions; 
		std::vector<glm::vec3> normals; 
		std::vector<glm::vec2> textureCoords;

		void genBuffers();
		std::vector<float> createVertices();
	public:
		RawModel(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices);
		int getIndexCount() { return this->indices.size(); };


		
		void unbind();
		void bind();

	};
}