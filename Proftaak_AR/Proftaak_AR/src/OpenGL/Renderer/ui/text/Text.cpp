#include "Text.h"

//constexpr unsigned int Engine::Text::indices[];

OpenGL::Text::Text(const std::string value, std::shared_ptr<Font> font, glm::vec2 position, glm::vec3 color, const unsigned int textSize, const float maxLineSize, const unsigned int maxNumLines, glm::vec2 windowSize)
	: value(value), font(font), position(position), color(color), textSize(textSize), maxLineSize(maxLineSize), maxNumberOfLines(maxNumLines), windowSize(windowSize)
{
	// Generate buffers
	glGenBuffers(1, &this->vertexBufferId);
	glGenBuffers(1, &this->indexBufferId);
	glGenVertexArrays(1, &this->vertexArrayId);

	// Enable and set attribute pointers
	glBindVertexArray(this->vertexArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);

	unsigned int offset = 0;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, (const void*)offset);
	offset += 8; // 8 bytes because 2 * sizeof(float) == 8
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (const void*)offset);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->shader = std::unique_ptr<Shader>(new Shader("res/shaders/vertex/V_Text.glsl", "res/shaders/fragment/F_Text.glsl"));
	this->shader->bind();
	this->shader->setUniform1i("fontAtlas", 0);
	this->shader->unbind();

	buildMesh();
}

OpenGL::Text::~Text()
{
	// Delete buffers
	glDeleteBuffers(1, &this->vertexBufferId);
	glDeleteBuffers(1, &this->indexBufferId);
	glDeleteVertexArrays(1, &this->vertexArrayId);
}

void OpenGL::Text::setValue(const std::string value)
{
	if (this->value != value)
	{
		this->value = value;
		buildMesh();
	}
}

void OpenGL::Text::setTextSize(const unsigned int textSize)
{
	this->textSize = textSize;
}

void OpenGL::Text::setMaxLineSize(const float maxLineSize)
{
	this->maxLineSize = maxLineSize;
	buildMesh();
}

void OpenGL::Text::setMaxNumerOfLines(const unsigned int maxNumLines)
{
	this->maxNumberOfLines = maxNumberOfLines;
	buildMesh();
}

void OpenGL::Text::setFont(const std::shared_ptr<Font> font)
{
	this->font = font;
	buildMesh();
}

void OpenGL::Text::onWindowResize(const glm::vec2 windowSize)
{
	this->windowSize = windowSize;
	buildMesh();
}

void OpenGL::Text::bind()
{
	this->shader.get()->bind();
	this->shader.get()->setUniformVec3f("textColor", this->color);
	this->shader.get()->setUniformVec2f("translation", glm::vec2((1.0f / this->windowSize.x) * this->position.x, (1.0f / this->windowSize.y) * -this->position.y));
	this->font->texture->bind(0);

	glBindVertexArray(this->vertexArrayId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
}

void OpenGL::Text::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->font->texture->unbind();
	this->shader.get()->unbind();
}

void OpenGL::Text::buildMesh()
{
	if (this->font != nullptr)
	{
		if (this->value == "")
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
			glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			return;
		}

		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		glm::vec2 cursor = glm::vec2(0.0f);
		unsigned int lineNumber = 1;
		unsigned int lastIndex = 0;

		for (char character : this->value)
		{
			Font::Character fontCharacter;
			if (!this->font->getCharacter(character, fontCharacter))
				continue;

			float sizedAdvance = ((float)fontCharacter.xAdvance / this->font->getSize()) * this->textSize;
			float sizedLineHeight = ((float)this->font->getLineHeight() / this->font->getSize()) * this->textSize;
			if ((cursor.x - this->position.x + sizedAdvance) > this->maxLineSize)
			{
				cursor.x = 0;
				cursor.y += sizedLineHeight;
				lineNumber++;

				if (lineNumber > this->maxNumberOfLines)
					break;
			}

			buildQuad(cursor, fontCharacter, vertices, indices, lastIndex);

			lastIndex += 4;
			cursor.x += sizedAdvance;
		}
		
		this->indicesCount = indices.size();

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void OpenGL::Text::buildQuad(glm::vec2& cursor, Font::Character& fontCharacter, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& lastIndex)
{
	float windowWidthMult = (1.0f / this->windowSize.x), windowHeightMult = (1.0f / this->windowSize.y);
	float characterWidth = ((float)fontCharacter.width / this->font->getSize()) * this->textSize;
	float characterHeight = ((float)fontCharacter.height / this->font->getSize()) * this->textSize;
	float characterOffsetX = ((float)fontCharacter.offset.x / this->font->getSize()) * this->textSize;
	float characterOffsetY = ((float)fontCharacter.offset.y / this->font->getSize()) * this->textSize;

	// Top Left
	vertices.push_back(windowWidthMult * (cursor.x + characterOffsetX));
	vertices.push_back(1.0f - windowHeightMult * (cursor.y + characterOffsetY));
	vertices.push_back((1.0f / 512) * fontCharacter.origin.x);
	vertices.push_back(1.0f - (1.0f / 512) * fontCharacter.origin.y);
	// Top Right
	vertices.push_back(windowWidthMult * (cursor.x + characterOffsetX + characterWidth));
	vertices.push_back(1.0f - windowHeightMult * (cursor.y + characterOffsetY));
	vertices.push_back((1.0f / 512) * (fontCharacter.origin.x + fontCharacter.width));
	vertices.push_back(1.0f - (1.0f / 512) * fontCharacter.origin.y);
	// Bottom Left
	vertices.push_back(windowWidthMult * (cursor.x + characterOffsetX));
	vertices.push_back(1.0f - windowHeightMult * (cursor.y + characterOffsetY + characterHeight));
	vertices.push_back((1.0f / 512) * fontCharacter.origin.x);
	vertices.push_back(1.0f - (1.0f / 512) * (fontCharacter.origin.y + fontCharacter.height));
	// Bottom Right
	vertices.push_back(windowWidthMult * (cursor.x + characterOffsetX + characterWidth));
	vertices.push_back(1.0f - windowHeightMult * (cursor.y + characterOffsetY + characterHeight));
	vertices.push_back((1.0f / 512) * (fontCharacter.origin.x + fontCharacter.width));
	vertices.push_back(1.0f - (1.0f / 512) * (fontCharacter.origin.y + fontCharacter.height));

	for (unsigned int index : this->quadIndices)
		indices.push_back(index + lastIndex);
}
