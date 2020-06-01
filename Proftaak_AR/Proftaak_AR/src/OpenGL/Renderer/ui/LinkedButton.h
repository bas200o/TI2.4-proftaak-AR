#pragma once
#include <glm/vec2.hpp>
#include <OpenGL\windowhandling\Window.h>


class LinkedButton
{
private:
	const char* text;
	glm::vec2 position;
	int width; 
	int height;

public:
	LinkedButton(const char* text, glm::vec2 position, int width, int height);

	void draw();

	LinkedButton* upButton;
	LinkedButton* downButton;
	LinkedButton* leftButton;
	LinkedButton* rightButton;
};