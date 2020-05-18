#pragma once

#include <GL/glew.h>

#include <string>
#include <memory>
#include <vector>

#include "Font.h"
#include "../../shading/Shader.h"

namespace OpenGL
{
	class Text
	{
	private:
		static constexpr unsigned int quadIndices[] = {
			0, 1, 2,
			2 ,1 ,3
		};

		std::string value;
		unsigned int textSize;
		glm::vec3 color;

		glm::vec2 position;
		float maxLineSize;
		unsigned int maxNumberOfLines;

		glm::vec2 windowSize;

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Font> font;

		// Buffers
		unsigned int vertexBufferId;
		unsigned int indexBufferId;
		unsigned int vertexArrayId;
		unsigned int indicesCount;

		friend class Renderer;

	public:
		Text(const std::string value, std::shared_ptr<Font> font, glm::vec2 position, glm::vec3 color, const unsigned int textSize, const float maxLineSize, const unsigned int maxNumLines, glm::vec2 windowSize);
		~Text();

		void setValue(const std::string value);
		void setTextSize(const unsigned int textSize);
		void setMaxLineSize(const float maxLineSize);
		void setMaxNumerOfLines(const unsigned int maxNumLines);
		void setFont(const std::shared_ptr<Font> font);

		void onWindowResize(const glm::vec2 windowSize);

		void bind();
		void unbind();

	private:
		void buildMesh();
		void buildQuad(glm::vec2& cursor, Font::Character& fontCharacter, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& lastIndex);
	};
}