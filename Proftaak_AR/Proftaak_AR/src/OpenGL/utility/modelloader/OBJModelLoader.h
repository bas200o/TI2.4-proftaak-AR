#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "utilities/StringUtil.h"
#include "../../Renderer/RawModel.h"

namespace OpenGL
{
	class OBJModelLoader
	{
	private:
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
			std::vector<Vertex> Vertices;
			std::vector<unsigned int> Indices;
		};

	private:
		std::vector<Mesh> loadedMeshes;

	public:
		OBJModelLoader();
		~OBJModelLoader();

		void loadModel(std::string filePath);
		void clearLoadedMeshes();

		std::vector<RawModel> getRawModels();
		RawModel getRawModel(std::string name);

	private:
		void processVertex(std::string vertexData, std::vector<Vertex>& vertices, std::vector<Vec3>& positions, std::vector<Vec3>& normals, std::vector<Vec2>& uvCoordinates);
	};
}