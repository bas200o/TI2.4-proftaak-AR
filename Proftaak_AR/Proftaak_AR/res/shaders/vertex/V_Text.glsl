#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvCoord;

out vec2 UVCoord;

uniform vec2 translation;

void main()
{
	UVCoord = uvCoord;

	gl_Position = vec4(((position + translation) * 2.0) - 1.0, 0.0, 1.0);
}