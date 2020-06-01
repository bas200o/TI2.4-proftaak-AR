#include "Kart.h"

GameLogic::Kart::Kart(const glm::vec3 color)
	: color(color)
{
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	this->shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl"));

	OpenGL::OBJModelLoader modelLoader = OpenGL::OBJModelLoader();
	if (renderer.getRegisteredModel("Frame").expired())
	{
		modelLoader.loadModel("res/models/kart/Kart_V2.obj");
		OpenGL::OBJModelLoader::Mesh frame = *modelLoader.getLoadedMesh("Frame");
		OpenGL::OBJModelLoader::Mesh leftFrontWheel = *modelLoader.getLoadedMesh("Front_Left_Wheel");
		OpenGL::OBJModelLoader::Mesh rightFrontWheel = *modelLoader.getLoadedMesh("Front_Right_Wheel");
		OpenGL::OBJModelLoader::Mesh backWheels = *modelLoader.getLoadedMesh("Back_Wheels");
		OpenGL::OBJModelLoader::Mesh steeringWheel = *modelLoader.getLoadedMesh("Steering_Wheel");
		OpenGL::OBJModelLoader::Mesh gasPedal = *modelLoader.getLoadedMesh("Gas_Pedal");
		OpenGL::OBJModelLoader::Mesh brakePedal = *modelLoader.getLoadedMesh("Brake_Pedal");

		renderer.registerModel(frame.name, frame.Positions, frame.Normals, frame.UVCoordinates, frame.Indices);
		renderer.registerModel(leftFrontWheel.name, leftFrontWheel.Positions, leftFrontWheel.Normals, leftFrontWheel.UVCoordinates, leftFrontWheel.Indices);
		renderer.registerModel(rightFrontWheel.name, rightFrontWheel.Positions, rightFrontWheel.Normals, rightFrontWheel.UVCoordinates, rightFrontWheel.Indices);
		renderer.registerModel(backWheels.name, backWheels.Positions, backWheels.Normals, backWheels.UVCoordinates, backWheels.Indices);
		renderer.registerModel(steeringWheel.name, steeringWheel.Positions, steeringWheel.Normals, steeringWheel.UVCoordinates, steeringWheel.Indices);
		renderer.registerModel(gasPedal.name, gasPedal.Positions, gasPedal.Normals, gasPedal.UVCoordinates, gasPedal.Indices);
		renderer.registerModel(brakePedal.name, brakePedal.Positions, brakePedal.Normals, brakePedal.UVCoordinates, brakePedal.Indices);
	}

	steeringWheelTransform.setParent(this->transform);
	leftFrontWheelTransform.setParent(this->transform);
	rightFrontWheelTransform.setParent(this->transform);
	backWheelsTransform.setParent(this->transform);
	gasPedalTransform.setParent(this->transform);
	brakePedalTransform.setParent(this->transform);

	steeringWheelTransform.translateBy(glm::vec3(0.0f, 1.34f, -1.62f));
	steeringWheelTransform.rotateBy(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rightFrontWheelTransform.translateBy(glm::vec3(0.75f, 0.5f, -2.0f));
	leftFrontWheelTransform.translateBy(glm::vec3(-0.75f, 0.5f, -2.0f));
	backWheelsTransform.translateBy(glm::vec3(0.0f, 0.5f, 0.0f));
	gasPedalTransform.translateBy(glm::vec3(0.23f, 0.88f, -1.75f));
	brakePedalTransform.translateBy(glm::vec3(-0.23f, 0.88f, -1.75f));

	this->models.push_back({ &this->transform, renderer.getRegisteredModel("Frame") });
	this->models.push_back({ &leftFrontWheelTransform, renderer.getRegisteredModel("Front_Left_Wheel") });
	this->models.push_back({ &rightFrontWheelTransform, renderer.getRegisteredModel("Front_Right_Wheel") });
	this->models.push_back({ &backWheelsTransform, renderer.getRegisteredModel("Back_Wheels") });
	this->models.push_back({ &steeringWheelTransform, renderer.getRegisteredModel("Steering_Wheel") });
	this->models.push_back({ &gasPedalTransform, renderer.getRegisteredModel("Gas_Pedal") });
	this->models.push_back({ &brakePedalTransform, renderer.getRegisteredModel("Brake_Pedal") });
}

void GameLogic::Kart::update(float deltatime)
{

}
