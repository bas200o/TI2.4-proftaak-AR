//#include <opencv2/opencv.hpp>
//#include "opencv2/imgproc/imgproc.hpp" 
//#include "opencv2/highgui/highgui.hpp"

#include "Application.h"

int main()
{
	Game::Application app;
	if (!app.run())
		return -1;

	return 0;
}