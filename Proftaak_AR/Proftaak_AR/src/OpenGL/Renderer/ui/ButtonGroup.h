#pragma once
#include <OpenGL\Renderer\ui\LinkedButton.h>
#include <vector>

class ButtonGroup
{
private:
	LinkedButton* currentButton;
	std::vector<LinkedButton> buttons;

public:
	/*Creates a ButtonGroup
	The first element in the vector will be selected at first*/
	ButtonGroup(std::vector<LinkedButton> buttons);

	bool up();

	bool down();

	bool left();

	bool right();
};

