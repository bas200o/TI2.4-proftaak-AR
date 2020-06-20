#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

OpenGL::Texture2D::Texture2D()
{

}

OpenGL::Texture2D::Texture2D(const std::string& filepath)
	: id(0), filepath(filepath), width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localbuffer = stbi_load(filepath.c_str(), &this->width, &this->height, &this->bpp, 4);

	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localbuffer != nullptr)
		stbi_image_free(localbuffer);
}

OpenGL::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &this->id);
}

void OpenGL::Texture2D::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void OpenGL::Texture2D::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}