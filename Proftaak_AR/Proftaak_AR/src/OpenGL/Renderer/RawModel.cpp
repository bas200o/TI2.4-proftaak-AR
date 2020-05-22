#include"RawModel.h"


OpenGL::RawModel::RawModel(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices)
	:positions(positions), normals(normals), textureCoords(textureCoords), indices(indices)
{
    genBuffers();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    std::vector<float> vertices = createVertices();
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL::RawModel::genBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	unsigned int offset = 0;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (const void*)offset);
	offset += 12;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const void*)offset);
	offset += 12;
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (const void*)offset);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

std::vector<float> OpenGL::RawModel::createVertices()
{
    std::vector<float> vertices = std::vector<float>();

    int maxSize = std::max(this->positions.size(), std::max(this->normals.size(), this->textureCoords.size()));
    for (int i = 0; i < maxSize; i++)
    {
        if (positions.size() > i)
        {
            glm::vec3& position = this->positions[i];
            vertices.push_back(position.x);
            vertices.push_back(position.y);
            vertices.push_back(position.z);
        }
        if (normals.size() > i)
        {
            glm::vec3& normal = this->normals[i];
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
        if (textureCoords.size() > i)
        {
            glm::vec2& uvCoordinate = this->textureCoords[i];
            vertices.push_back(uvCoordinate.x);
            vertices.push_back(uvCoordinate.y);
        }
    }
    return vertices;
}

void OpenGL::RawModel::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL::RawModel::bind() {
	glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
}
