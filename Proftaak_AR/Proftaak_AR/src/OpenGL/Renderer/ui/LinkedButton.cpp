#include "LinkedButton.h"

LinkedButton::LinkedButton(const char* text, glm::vec2 position, int width, int height)
{
}

bool LinkedButton::setUpButton(LinkedButton* upButton)
{
	if (upButton == this) 
	{
		return false;
	}
	this->upButton = upButton;
	return true;
}
