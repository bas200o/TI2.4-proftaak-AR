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
	CollisionBox2D box1 = CollisionBox2D(glm::vec2(0.0, 0.0), 90.0, 10.0, 5.0);
	std::array<glm::vec2, 4> corners = box1.getCorners();
	box1.setCenter(glm::vec2(10.0, 10.0));

	CollisionBox2D box2 = CollisionBox2D(glm::vec2(5.1, 0.0), 90.0, 10.0, 5.0);

	std::cout << box1.collidesWith(box2);
}

/*TODO
Collision object bumping and weight
Collision object interface to allow a group of immovable collision boxes in a gameobject
*/