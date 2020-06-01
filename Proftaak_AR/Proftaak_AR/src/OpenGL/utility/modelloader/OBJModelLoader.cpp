#include "OBJModelLoader.h"

OpenGL::OBJModelLoader::OBJModelLoader()
{
	this->loadedMeshes = std::vector<Mesh>();
}

OpenGL::OBJModelLoader::~OBJModelLoader()
{

}

void OpenGL::OBJModelLoader::loadModel(std::string filePath)
{
	this->loadedMeshes.clear();

	std::ifstream stream(filePath);
	std::string line;

	std::vector<Vec3> loadedPositions = std::vector<Vec3>();
	std::vector<Vec3> loadedNormals = std::vector<Vec3>();
	std::vector<Vec2> loadedUVCoordinates = std::vector<Vec2>();
	std::vector<unsigned int> loadedIndices = std::vector<unsigned int>();

	std::vector<Vertex> vertices = std::vector<Vertex>();
	Mesh* mesh = nullptr;

	while (getline(stream, line))
	{
		std::vector<std::string> lineSplit = StringUtil::split(line, " ");

		if (line.find("o ") != std::string::npos)
		{
			if (mesh != nullptr)
			{
				mesh->setVertices(vertices);
				mesh->Indices = loadedIndices;

				loadedIndices.clear();
				vertices.clear();

				this->loadedMeshes.push_back(*mesh);
			}

			mesh = new Mesh(lineSplit[1]);
		}
		else if (line.find("v ") != std::string::npos)
			loadedPositions.push_back(Vec3(std::stof(lineSplit[1]), std::stof(lineSplit[2]), std::stof(lineSplit[3])));
		else if (line.find("vt ") != std::string::npos)
			loadedUVCoordinates.push_back(Vec2(std::stof(lineSplit[1]), std::stof(lineSplit[2])));
		else if (line.find("vn ") != std::string::npos)
			loadedNormals.push_back(Vec3(std::stof(lineSplit[1]), std::stof(lineSplit[2]), std::stof(lineSplit[3])));
		else if (line.find("f ") != std::string::npos)
		{
			unsigned int size = loadedIndices.size();
			loadedIndices.push_back(size);
			loadedIndices.push_back(size + 1);
			loadedIndices.push_back(size + 2);

			processVertex(lineSplit[1], vertices, loadedPositions, loadedNormals, loadedUVCoordinates);
			processVertex(lineSplit[2], vertices, loadedPositions, loadedNormals, loadedUVCoordinates);
			processVertex(lineSplit[3], vertices, loadedPositions, loadedNormals, loadedUVCoordinates);
		}
	}

	if (mesh != nullptr)
	{
		mesh->setVertices(vertices);
		mesh->Indices = loadedIndices;

		loadedPositions.clear();
		loadedNormals.clear();
		loadedUVCoordinates.clear();
		loadedIndices.clear();
		vertices.clear();

		this->loadedMeshes.push_back(*mesh);
	}
}

void OpenGL::OBJModelLoader::clearLoadedMeshes()
{
	this->loadedMeshes.clear();
}

OpenGL::OBJModelLoader::Mesh* OpenGL::OBJModelLoader::getLoadedMesh(const std::string name)
{
	for (int i = 0; i < this->loadedMeshes.size(); i++)
	{
		if (this->loadedMeshes[i].name == name)
			return &this->loadedMeshes[i];
	}

	return nullptr;
}

void OpenGL::OBJModelLoader::processVertex(std::string vertexData, std::vector<Vertex>& vertices, std::vector<Vec3>& positions, std::vector<Vec3>& normals, std::vector<Vec2>& uvCoordinates)
{
	std::vector<std::string> indexData = StringUtil::split(vertexData, "/");
	unsigned int index = std::stoi(indexData[0]) - 1;
	Vertex vertex = Vertex();
	vertex.Position = positions[index];
	vertex.Normal = normals[std::stoi(indexData[2]) - 1];
	vertex.UVCoordinate = uvCoordinates[std::stoi(indexData[1]) - 1];

	vertices.push_back(vertex);
}