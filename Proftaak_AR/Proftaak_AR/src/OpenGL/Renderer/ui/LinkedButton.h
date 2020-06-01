#pragma once
#include <glm/vec2.hpp>
#include <OpenGL\windowhandling\Window.h>

/*This class represents a button that is linked to other buttons
The links should be set before the button is used
Not all links have to be set
The button must be in a ButtonGroup for the links to be functional*/
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

	//links
	LinkedButton* upButton;
	LinkedButton* downButton;
	LinkedButton* leftButton;
	LinkedButton* rightButton;
};