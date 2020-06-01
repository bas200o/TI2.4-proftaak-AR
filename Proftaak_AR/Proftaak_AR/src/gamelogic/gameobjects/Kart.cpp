#include "Kart.h"

GameLogic::Kart::Kart(const glm::vec3 color, const float wheelRadius, const float maxSpeed, const float accelaration, const float brakeForce)
	: color(color), maxSpeed(maxSpeed), accelaration(accelaration), brakeForce(brakeForce), steeringAngle(0.0f), maxSteeringAngle(glm::radians(25.0f)), currentSpeed(0.0f), drag(2.0f),
	isAccelarating(false), isBraking(false)
{
	this->wheelCircumference = (wheelRadius * 2) * glm::pi<float>();

	// Setup meshes and transforms
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	this->shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl"));

	this->textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Diffuse.png")));
	this->textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Specular.png")));
	this->textures.push_back(renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Color_Mask.png")));

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

void GameLogic::Kart::steer(const float angle)
{
	float newAngle = glm::radians(angle);
	if (glm::abs(newAngle) > this->maxSteeringAngle)
	{
		if (newAngle < 0.0f)
			this->steeringAngle = -this->maxSteeringAngle;
		else
			this->steeringAngle = this->maxSteeringAngle;
	}
	else
		this->steeringAngle = newAngle;
}

void GameLogic::Kart::update(float deltatime)
{
	if (this->isBraking)
		this->currentSpeed -= this->brakeForce * deltatime;

	if (this->isAccelarating)
		this->currentSpeed += (this->accelaration * deltatime);
	else
		this->currentSpeed -= this->drag * deltatime;

	if (this->currentSpeed > this->maxSpeed)
		this->currentSpeed = this->maxSpeed;
	if (this->currentSpeed < 0.0f)
		this->currentSpeed = 0.0f;

	float wheelRotationSpeed = ((this->currentSpeed / this->wheelCircumference) * (glm::pi<float>() * 2)) * deltatime;
	rotateWheels(wheelRotationSpeed);
	float steerSpeed = (this->steeringAngle * this->currentSpeed) * deltatime;

	this->transform.rotateBy(steerSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
	this->transform.translateBy(this->transform.getFront() * (this->currentSpeed * deltatime));
}

void GameLogic::Kart::rotateWheels(float wheelRotationSpeed)
{
	this->currentWheelAngle += wheelRotationSpeed;
	if (this->currentWheelAngle > (glm::pi<float>() * 2))
		this->currentWheelAngle -= (glm::pi<float>() * 2);

	// Steering wheel
	this->steeringWheelTransform.setLocalRotation(this->steeringAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	this->steeringWheelTransform.rotateBy(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Front wheels
	this->leftFrontWheelTransform.setLocalRotation(this->currentWheelAngle, glm::vec3(-1.0f, 0.0f, 0.0f));
	this->rightFrontWheelTransform.setLocalRotation(this->currentWheelAngle, glm::vec3(-1.0f, 0.0f, 0.0f));
	this->leftFrontWheelTransform.rotateBy(this->steeringAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	this->rightFrontWheelTransform.rotateBy(this->steeringAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	//this->leftFrontWheelTransform.setLocalRotation(this->steeringAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	//this->rightFrontWheelTransform.setLocalRotation(this->steeringAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	//this->leftFrontWheelTransform.rotateBy(wheelRotationSpeed, glm::vec3(-1.0f, 0.0f, 0.0f));
	//this->rightFrontWheelTransform.rotateBy(wheelRotationSpeed, glm::vec3(-1.0f, 0.0f, 0.0f));

	// Back wheels
	this->backWheelsTransform.rotateBy(wheelRotationSpeed, glm::vec3(-1.0f, 0.0f, 0.0f));
}

void GameLogic::Kart::setRequiredUniforms()
{
	this->shader.lock()->bind();
	this->shader.lock()->setUniformVec3f("kartColor", this->color);
	this->shader.lock()->setUniformBool("useDiffuseMap", true);
	this->shader.lock()->setUniformBool("useSpecularMap", true);
	this->shader.lock()->setUniformBool("useDiffuseMask", true);
	this->shader.lock()->setUniform1i("diffuseMap", 0);
	this->shader.lock()->setUniform1i("specularMap", 1);
	this->shader.lock()->setUniform1i("diffuseMask", 2);
	this->shader.lock()->unbind();
}
