#include "Loader.h"



OpenGL::RawModel OpenGL::Loader::loadToVAO(std::vector<float> positions) {
	int vaoID = createVAO();
	storeDataInAttributeList(0, positions);
	unbindVao();
	RawModel returnModel = RawModel(vaoID, positions.size()/3);
	return returnModel;
}

int OpenGL::Loader::createVAO() {
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	vaos.push_back(VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void OpenGL::Loader::storeDataInAttributeList(int attributeNumber, std::vector<float> data) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	vbos.push_back(VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGL::Loader::unbindVao() {
	glBindVertexArray(0);
}

void OpenGL::Loader::cleanup() {
	for (GLuint vao : vaos) {
		glDeleteVertexArrays(vao);
	}
	for (GLuint vbo : vbos) {
		glDeleteBuffers(GL_ARRAY_BUFFER, vbo);
	}
}