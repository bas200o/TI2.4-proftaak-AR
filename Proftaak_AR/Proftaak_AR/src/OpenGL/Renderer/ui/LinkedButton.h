#pragma once
#include <glm/vec2.hpp>
#include <OpenGL\windowhandling\Window.h>


class LinkedButton
{
public:
	typedef void (*buttonAction)(void);

private:
	const char* text;
	glm::vec2 position;
	int width; 
	int height;
	buttonAction onPressed;

public:
	LinkedButton(const char* text, buttonAction onPressedFunction, glm::vec2 position, int width, int height);

	void draw();

	void pressButton();

	LinkedButton* upButton;
	LinkedButton* downButton;
	LinkedButton* leftButton;
	LinkedButton* rightButton;
};