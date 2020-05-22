#include <GL/glew.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"

#include <gamelogic\collision\CollisionObject2D.h>
#include <vector>;

void collisionTest();

int main()
{
	collisionTest();
	return 0;
}

void collisionTest() 
{
	std::vector<CollisionBox> v1;
	v1.push_back(CollisionBox(glm::vec2(0.0, 0.0), 0.0, 10.0, 5.0));
	CollisionObject2D o1 = CollisionObject2D(glm::vec2(0, 0), v1);

	std::vector<CollisionBox> v2;
	v2.push_back(CollisionBox(glm::vec2(0.0, 0.0), 0.0, 10.0, 10.0));
	CollisionObject2D o2 = CollisionObject2D(glm::vec2(2.0, 2.0), v2);

	o1.rotate(90);

	std::cout << o1.collidesWith(o2) << "\n";
}