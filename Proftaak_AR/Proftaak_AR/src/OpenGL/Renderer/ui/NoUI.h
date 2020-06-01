#pragma once
#include "OpenGL\Renderer\ui\ActiveUI.h"

class NoUI : public ActiveUI
{
public:
	NoUI();

	virtual void update(OpenGL::Window& window, float deltaTime) override;

	virtual void draw() override;
};