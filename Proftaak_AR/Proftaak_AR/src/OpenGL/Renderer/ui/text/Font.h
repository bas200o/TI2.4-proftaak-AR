#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "../../shading/Texture2D.h"
#include "./utilities/StringUtil.h"

namespace OpenGL
{
	class Font
	{
	public:
		struct Character
		{
			unsigned int asciiCode;
			glm::vec2 origin;
			glm::vec2 offset;
			unsigned int width;
			unsigned int height;
			unsigned int xAdvance;
		};

	private:
		std::string name;

		std::unique_ptr<Texture2D> texture;
		std::unordered_map<unsigned int, Character> characters;

		unsigned int size;
		unsigned int lineHeight;

		friend class Text;

	public:
		Font(const std::string fontname, const std::string& folderPath);

		// Returns if character was found and sets reference to character if it does
		bool getCharacter(const unsigned int asciiCharacter, Character& character);

		unsigned int getSize() { return this->size; }
		unsigned int getLineHeight() { return this->lineHeight; }

	private:
		void loadAtlas(const std::string& filePath);
		void loadFont(const std::string& filePath);
	};
}