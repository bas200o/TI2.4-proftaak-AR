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
	CollisionBox2D box2 = CollisionBox2D(glm::vec2(0.0, 0.0), 90.0, 10.0, 5.0);

	//test 1
	box1.setCenter(glm::vec2(4.9, 0.0));
	std::cout << "test 1 is: " << box1.collidesWith(box2) << " should be: " << 1 << "\n"; //should be 1

	//test 2
	box1.setCenter(glm::vec2(5.1, 0.0));
	std::cout << "test 2 is: " << box1.collidesWith(box2) << " should be: " << 0 << "\n"; //should be 0

	//test 3
	box1.setCenter(glm::vec2(0.0, 0.0));
	box2.rotate(-90.0);
	std::cout << "test 3 is: " << box1.collidesWith(box2) << " should be: " << 1 << "\n"; //should be 1

	//test 4
	box1.setCenter(glm::vec2(0.0, 0.0));
	box2.push(7.4, 0.0);
	std::cout << "test 4 is: " << box1.collidesWith(box2) << " should be: " << 1 << "\n"; //should be 1

	//test 5
	box1.setCenter(glm::vec2(0.0, 0.0));
	box2.push(0.2, 0.0);
	std::cout << "test 5 is: " << box1.collidesWith(box2) << " should be: " << 0 << "\n"; //should be 0
}

/*TODO
Collision object bumping and weight/force?
*/