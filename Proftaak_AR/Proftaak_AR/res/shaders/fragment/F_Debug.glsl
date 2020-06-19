#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoord;

uniform vec3 debugColor;

void main()
{
	color = vec4(debugColor, 1.0f);
};