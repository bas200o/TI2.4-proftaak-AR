#include "Loader.h"



OpenGL::RawModel OpenGL::Loader::loadToVAO(float positions[]) {
	int vaoID = createVAO();
	storeDataInAttributeList(0, positions);
	unbindVao();
	RawModel returnModel = RawModel(vaoID, (sizeof(positions) / sizeof(*positions)));
	return returnModel;
}

int OpenGL::Loader::createVAO() {
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void OpenGL::Loader::storeDataInAttributeList(int attributeNumber, float data[]) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void OpenGL::Loader::unbindVao() {
	glBindVertexArray(0);
}