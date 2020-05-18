#include "Font.h"

OpenGL::Font::Font(const std::string fontname, const std::string& folderPath)
	: name(fontname)
{
	std::stringstream atlasPath, fontPath;
	atlasPath << folderPath << "/" << fontname << "/" << fontname << ".png";
	fontPath << folderPath << "/" << fontname << "/" << fontname << ".fnt";

	loadAtlas(atlasPath.str());
	loadFont(fontPath.str());
}

bool OpenGL::Font::getCharacter(const unsigned int asciiCharacter, OpenGL::Font::Character& character)
{
	if (this->characters.find(asciiCharacter) != this->characters.end())
	{
		character = this->characters[asciiCharacter];
		return true;
	}
	return false;
}

void OpenGL::Font::loadAtlas(const std::string& filePath)
{
	this->texture = std::unique_ptr<Texture2D>(new Texture2D(filePath));
}

void OpenGL::Font::loadFont(const std::string& filePath)
{
	std::ifstream stream(filePath);

	std::string line;
	while (std::getline(stream, line))
	{
		StringUtil::trim(line);
		std::string newLine = StringUtil::removeNeighboringSpaces(line);
		std::vector<std::string> lineSplit = StringUtil::split(newLine, " ");

		if (lineSplit[0] == "info")
		{
			this->size = glm::abs(std::stoi(StringUtil::split(lineSplit[2], "=")[1]));
		}
		else if (lineSplit[0] == "common")
		{
			this->lineHeight = glm::abs(std::stoi(StringUtil::split(lineSplit[1], "=")[1]));
		}
		else if (lineSplit[0] == "char")
		{
			Character character;
			character.asciiCode = glm::abs(std::stoi(StringUtil::split(lineSplit[1], "=")[1]));
			character.origin = glm::vec2(std::stof(StringUtil::split(lineSplit[2], "=")[1]),
				std::stof(StringUtil::split(lineSplit[3], "=")[1]));
			character.offset = glm::vec2(std::stof(StringUtil::split(lineSplit[6], "=")[1]),
				std::stof(StringUtil::split(lineSplit[7], "=")[1]));
			character.width = glm::abs(std::stoi(StringUtil::split(lineSplit[4], "=")[1]));
			character.height = glm::abs(std::stoi(StringUtil::split(lineSplit[5], "=")[1]));
			character.xAdvance = glm::abs(std::stoi(StringUtil::split(lineSplit[8], "=")[1]));

			if (this->characters.find(character.asciiCode) == this->characters.end())
				this->characters[character.asciiCode] = character;
		}
	}
}