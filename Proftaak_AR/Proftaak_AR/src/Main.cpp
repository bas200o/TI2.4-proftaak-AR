//#include <opencv2/opencv.hpp>
//#include "opencv2/imgproc/imgproc.hpp" 
//#include "opencv2/highgui/highgui.hpp"

#include "Application.h"

int main()
{
	Game::Application app = Game::Application();
	if (!app.run())
		return -1;

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}