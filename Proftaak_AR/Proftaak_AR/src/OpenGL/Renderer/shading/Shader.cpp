#include "Shader.h"

OpenGL::Shader::Shader(const std::string vertexFilepath, const std::string fragmentFilePath)
{
	std::string vertexSource = parseShader(vertexFilepath);
	std::string fragmentSource = parseShader(fragmentFilePath);
	this->id = createShader(vertexSource, fragmentSource);
}

OpenGL::Shader::~Shader()
{
	glDeleteProgram(this->id);
}

void OpenGL::Shader::bind() const
{
	glUseProgram(this->id);
}

void OpenGL::Shader::unbind() const
{
	glUseProgram(0);
}

void OpenGL::Shader::setUniform1i(const std::string& name, const int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void OpenGL::Shader::setUniform1f(const std::string& name, const float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void OpenGL::Shader::setUniform3f(const std::string& name, const float v0, const float v1, const float v2)
{
	glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void OpenGL::Shader::setUniformVec3f(const std::string& name, const glm::vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void OpenGL::Shader::setUniform2f(const std::string& name, const float v0, const float v1)
{
	glUniform2f(getUniformLocation(name), v0, v1);
}

void OpenGL::Shader::setUniformVec2f(const std::string& name, const glm::vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void OpenGL::Shader::setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3)
{
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void OpenGL::Shader::setUniformVec4f(const std::string& name, const glm::vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void OpenGL::Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void OpenGL::Shader::setUniformBool(const std::string& name, const bool value)
{
	glUniform1i(getUniformLocation(name), (value) ? 1 : 0);
}

std::string OpenGL::Shader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
		ss << line << '\n';

	return ss.str();
}

unsigned int OpenGL::Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int OpenGL::Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int OpenGL::Shader::getUniformLocation(const std::string& name)
{
	if (this->uniformLocationCache.find(name) != this->uniformLocationCache.end())
		return this->uniformLocationCache[name];

	int location = glGetUniformLocation(this->id, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	this->uniformLocationCache[name] = location;
	return location;
}