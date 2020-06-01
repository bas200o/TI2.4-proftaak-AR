#pragma once
#include <OpenGL\windowhandling\Window.h>

class ActiveUI 
{
	virtual void update(OpenGL::Window& window, float deltaTime) = 0;

	virtual void draw() = 0;
};