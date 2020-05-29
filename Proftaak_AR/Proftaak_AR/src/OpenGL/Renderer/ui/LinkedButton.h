#pragma once
#include <glm/vec2.hpp>

class LinkedButton
{
private:


public:
	LinkedButton(const char* text, glm::vec2 position, int width, int height);

	bool setUpButton(LinkedButton* upButton);

	LinkedButton* upButton;
	LinkedButton* downButton;
	LinkedButton* leftButton;
	LinkedButton* rightButton;
};