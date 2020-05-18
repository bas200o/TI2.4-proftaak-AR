#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

namespace OpenGL
{
	class Shader
	{
	private:
		unsigned int id;
		std::unordered_map<std::string, int> uniformLocationCache;
		std::string filepath;

	public:
		Shader(const std::string vertexFilepath, const std::string fragmentFilePath);
		~Shader();

		void bind() const;
		void unbind() const;

		void setUniform1i(const std::string& name, const int value);
		void setUniform1f(const std::string& name, const float value);
		void setUniform3f(const std::string& name, const float v0, const float v1, const float v2);
		void setUniformVec3f(const std::string& name, const glm::vec3& vector);
		void setUniform2f(const std::string& name, const float v0, const float v1);
		void setUniformVec2f(const std::string& name, const glm::vec2& vector);
		void setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3);
		void setUniformVec4f(const std::string& name, const glm::vec4& vector);
		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		void setUniformBool(const std::string& name, const bool value);
	private:
		std::string parseShader(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

		int getUniformLocation(const std::string& name);
	};
}