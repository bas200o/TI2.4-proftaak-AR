#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>

#include "utilities/StringUtil.h"
#include "../../Renderer/RawModel.h"

namespace OpenGL
{
	class OBJModelLoader
	{
	public:
		struct Vec3
		{
			Vec3()
				: X(0), Y(0), Z(0) {};
			Vec3(float x, float y, float z)
				: X(x), Y(y), Z(z) {};

			float X, Y, Z;
		};

		struct Vec2
		{
			Vec2()
				: X(0), Y(0) {};
			Vec2(float x, float y)
				: X(x), Y(y) {};

			float X, Y;
		};

		struct Vertex
		{
			Vertex() {};
			Vertex(Vec3 position, Vec3 normal, Vec2 uvCoordinate)
				: Position(position), Normal(normal), UVCoordinate(uvCoordinate) {};

			Vec3 Position;
			Vec3 Normal;
			Vec2 UVCoordinate;
		};

		struct Mesh
		{
			Mesh(std::string name)
				: name(name) {};

			std::string name;
			std::string textureFilePath;
			std::vector<glm::vec3> Positions;
			std::vector<glm::vec3> Normals;
			std::vector<glm::vec2> UVCoordinates;
			std::vector<unsigned int> Indices;

			inline void setVertices(std::vector<Vertex> vertices)
			{
				for (Vertex vertex : vertices)
				{
					this->Positions.push_back(glm::vec3(vertex.Position.X, vertex.Position.Y, vertex.Position.Z));
					this->Normals.push_back(glm::vec3(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z));
					this->UVCoordinates.push_back(glm::vec2(vertex.UVCoordinate.X, vertex.UVCoordinate.Y));
				}
			}
		};

	private:
		std::vector<Mesh> loadedMeshes;
		std::unordered_map<std::string, std::string> loadedTexturePaths;

	public:
		OBJModelLoader();
		~OBJModelLoader();

		void loadModel(std::string directoryPath, std::string filename);
		void clearLoadedResources();

		inline std::vector<Mesh> getLoadedMeshes() { return this->loadedMeshes; }
		Mesh* getLoadedMesh(const std::string name);

	private:
		void processVertex(std::string vertexData, std::vector<Vertex>& vertices, std::vector<Vec3>& positions, std::vector<Vec3>& normals, std::vector<Vec2>& uvCoordinates);
		void loadMTLFile(std::string filepath, Mesh* mesh);
	};
}