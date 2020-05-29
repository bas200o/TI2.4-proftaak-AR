#include "ButtonGroup.h"

ButtonGroup::ButtonGroup(std::vector<LinkedButton> buttons)
{
	this->buttons = buttons;
	this->currentButton = &this->buttons[0];
}

bool ButtonGroup::up()
{
	if (this->currentButton->upButton == NULL)
	{
		return false;
	}
	this->currentButton = this->currentButton->upButton;
	return true;
}

bool ButtonGroup::down()
{
	if (this->currentButton->downButton == NULL)
	{
		return false;
	}
	this->currentButton = this->currentButton->downButton;
	return true;
}

bool ButtonGroup::left()
{
	if (this->currentButton->leftButton == NULL)
	{
		return false;
	}
	this->currentButton = this->currentButton->leftButton;
	return true;
}

bool ButtonGroup::right()
{
	if (this->currentButton->rightButton == NULL)
	{
		return false;
	}
	this->currentButton = this->currentButton->rightButton;
	return true;
}
