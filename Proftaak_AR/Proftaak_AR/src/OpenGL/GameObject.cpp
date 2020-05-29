#include "GameObject.h"

OpenGL::GameObject::GameObject()
	: shader(Shader("", ""))
{

}

void OpenGL::GameObject::draw(Window& window)
{
	for(RawModel model : this->models)
		Renderer::draw3D(model, this->shader, window);
}
