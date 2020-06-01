#include "LinkedButton.h"

LinkedButton::LinkedButton(const char* text, LinkedButton::buttonAction onPressedFunction, glm::vec2 position, int width, int height)
{
	this->text = text;
	this->onPressed = onPressed;
	this->position = position;
	this->width = width;
	this->height = height;
}

void LinkedButton::draw()
{
	//TODO implement
}

void LinkedButton::pressButton()
{
	this->onPressed();
}
