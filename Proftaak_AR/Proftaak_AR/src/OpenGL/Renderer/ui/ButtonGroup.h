#pragma once
#include <OpenGL\Renderer\ui\LinkedButton.h>
#include <vector>
#include <OpenGL\windowhandling\Window.h>
#include "OpenGL\Renderer\ui\ActiveUI.h"

/*This class represents a group of LinkedButtons*/
class ButtonGroup : public ActiveUI
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

	/*Checks if any LinkedButtons do not have a links and gives a warning if one does*/
	void unlinkedWarning();

public:
	/*Creates a ButtonGroup
	The first element in the vector will be selected at first*/
	ButtonGroup(std::vector<LinkedButton> buttons);

	/*Checks if any keys are pressed and changes the current button if necessary*/
	virtual void update(OpenGL::Window& window, float deltaTime) override;

	/*Calls the draw function of all LinkedButtons managed by this object
	The ButtonGroup itself does not have a graphical representation to draw*/
	virtual void draw() override;
};

