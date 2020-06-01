#pragma once
#include <OpenGL\Renderer\ui\LinkedButton.h>
#include <vector>
#include <OpenGL\windowhandling\Window.h>

class ButtonGroup
{
private:
	LinkedButton* currentButton;
	std::vector<LinkedButton> buttons;
	float keypressCooldown;
	const float baseCooldown = 0.5f;

	bool up();

	bool down();

	bool left();

	bool right();

	void confirm();

public:
	/*Creates a ButtonGroup
	The first element in the vector will be selected at first*/
	ButtonGroup(std::vector<LinkedButton> buttons);

	void update(OpenGL::Window& window, float deltaTime);

	void draw();

};

