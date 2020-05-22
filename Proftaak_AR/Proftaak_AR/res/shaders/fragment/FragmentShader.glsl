#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

void main()
{
	color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
};