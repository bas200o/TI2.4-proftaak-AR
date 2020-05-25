#include <GL/glew.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"

#include <gamelogic\collision\CollisionBox2D.h>

void collisionTest();

int main()
{
	collisionTest();
	return 0;
}

void collisionTest() 
{
	CollisionBox2D box = CollisionBox2D(glm::vec2(0.0, 0.0), 90.0, 10.0, 5.0);
	box.calculateCorners();
}