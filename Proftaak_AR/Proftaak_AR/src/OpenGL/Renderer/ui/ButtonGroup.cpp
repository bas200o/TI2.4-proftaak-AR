#include "ButtonGroup.h"

//public:
ButtonGroup::ButtonGroup(std::vector<LinkedButton> buttons)
{
	this->buttons = buttons;
	this->currentButton = &this->buttons[0];
}

void ButtonGroup::update(OpenGL::Window& window, float deltaTime)
{
	this->keypressCooldown -= deltaTime;

	if (keypressCooldown <= 0.0f) {
		if (window.isKeyDown(GLFW_KEY_W) || window.isKeyDown(GLFW_KEY_UP)) {
			this->up();
			this->keypressCooldown = this->baseCooldown;
		}
		if (window.isKeyDown(GLFW_KEY_A) || window.isKeyDown(GLFW_KEY_LEFT)) {
			this->left();
			this->keypressCooldown = this->baseCooldown;
		}
		if (window.isKeyDown(GLFW_KEY_S) || window.isKeyDown(GLFW_KEY_DOWN)) {
			this->down();
			this->keypressCooldown = this->baseCooldown;
		}
		if (window.isKeyDown(GLFW_KEY_D) || window.isKeyDown(GLFW_KEY_RIGHT)) {
			this->right();
			this->keypressCooldown = this->baseCooldown;
		}
		if (window.isKeyDown(GLFW_KEY_ENTER) || window.isKeyDown(GLFW_KEY_SPACE)) {
			//todo confirm
			this->keypressCooldown = this->baseCooldown;
		}
	}
	//TODO add mouse support
}

void ButtonGroup::draw()
{
	for (LinkedButton button : this->buttons) 
	{
		button.draw();
	}
}

//private
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
