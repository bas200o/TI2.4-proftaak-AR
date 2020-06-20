#pragma once

#include <GL/glew.h>

#include <string>

namespace OpenGL
{
	class Texture2D
	{
	private:
		unsigned int id;
		std::string filepath;
		int width, height, bpp;

	public:
		Texture2D();
		Texture2D(const std::string& filepath);
		~Texture2D();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline unsigned int* getId() { return &this->id; }
		inline int getWidth() const { return this->width; }
		inline int getHeight() const { return this->height; }
	};
}