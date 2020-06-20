#include "Kart.h"

GameLogic::Kart::Kart(const glm::vec3 color, const float wheelRadius, const float maxSpeed, const float accelaration, const float brakeForce)
	: color(color), maxSpeed(maxSpeed), accelaration(accelaration), brakeForce(brakeForce), steeringAngle(0.0f), maxSteeringAngle(glm::radians(25.0f)), currentSpeed(0.0f), drag(2.0f),
	isAccelarating(false), isBraking(false)
{
	this->wheelCircumference = (wheelRadius * 2) * glm::pi<float>();

	this->lastSpeed = 0.0f;
	this->interpolationTimer = 1.0f;

	// Setup meshes and transforms
	OpenGL::Renderer& renderer = OpenGL::Renderer::getInstance();
	this->shader = renderer.getRegisteredShader(renderer.registerShader("res/shaders/vertex/V_Basic.glsl", "res/shaders/fragment/F_Kart.glsl"));

	OpenGL::OBJModelLoader modelLoader = OpenGL::OBJModelLoader();
	if (renderer.getRegisteredModel("Frame").expired())
	{
		modelLoader.loadModel("res/models/kart", "Kart_V2");
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

	std::vector<std::weak_ptr<OpenGL::Texture2D>> textures = std::vector<std::weak_ptr<OpenGL::Texture2D>>({
			renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Diffuse.png")),
			renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Specular.png")),
			renderer.getRegisteredTexture(renderer.registerTexture("res/textures/kart/Kart_Color_Mask.png"))
	});

	this->models.push_back({ &this->transform, renderer.getRegisteredModel("Frame"), textures, true });
	this->models.push_back({ &leftFrontWheelTransform, renderer.getRegisteredModel("Front_Left_Wheel"), textures, true });
	this->models.push_back({ &rightFrontWheelTransform, renderer.getRegisteredModel("Front_Right_Wheel"), textures, true });
	this->models.push_back({ &backWheelsTransform, renderer.getRegisteredModel("Back_Wheels"), textures, true });
	this->models.push_back({ &steeringWheelTransform, renderer.getRegisteredModel("Steering_Wheel"), textures, true });
	this->models.push_back({ &gasPedalTransform, renderer.getRegisteredModel("Gas_Pedal"), textures, true });
	this->models.push_back({ &brakePedalTransform, renderer.getRegisteredModel("Brake_Pedal"), textures, true });

	std::shared_ptr<SphereCollider> sphereCollider = std::make_shared<SphereCollider>(2.2f);
	sphereCollider->transform.translateBy(this->transform.getFront() * 1.13f);
	sphereCollider->transform.setParent(this->transform);
	this->colliders.push_back(sphereCollider);
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

void GameLogic::Kart::setIsAccelarating(bool isAccelarating)
{
	if (!isAccelarating && !this->isBraking && this->isAccelarating != isAccelarating)
	{
		this->interpolationTimer = 0.0f;
		this->lastSpeed = this->currentSpeed;
	}

	this->isAccelarating = isAccelarating;
}

void GameLogic::Kart::setIsBraking(bool isBraking)
{
	if (!isBraking && !this->isAccelarating && this->isBraking != isBraking)
	{
		this->interpolationTimer = 0.0f;
		this->lastSpeed = this->currentSpeed;
	}

	this->isBraking = isBraking;
}

void GameLogic::Kart::update(float deltatime)
{
	//if (this->isBraking)
	//	this->currentSpeed -= this->brakeForce * deltatime;

	//if (this->isAccelarating)
	//	this->currentSpeed += (this->accelaration * deltatime);
	//else
	//	this->currentSpeed -= this->drag * deltatime;

	//if (this->currentSpeed > this->maxSpeed)
	//	this->currentSpeed = this->maxSpeed;
	//if (this->currentSpeed < 0.0f)
	//	this->currentSpeed = 0.0f;

	if (this->isBraking)
		this->currentSpeed -= ((this->currentSpeed > 0.0f) ? this->brakeForce : this->accelaration) * deltatime;

	if (this->isAccelarating)
		this->currentSpeed += ((this->currentSpeed < 0.0f) ? this->brakeForce : this->accelaration) * deltatime;

	if (glm::abs(this->currentSpeed) > this->maxSpeed)
	{
		if(this->currentSpeed > 0.0f)
			this->currentSpeed = this->maxSpeed;
		else
			this->currentSpeed = -this->maxSpeed;
	}

	if (!this->isAccelarating && !this->isBraking && this->interpolationTimer != 1.0f)
	{
		this->interpolationTimer += glm::abs((1.0f / (this->lastSpeed / this->drag)) * deltatime);
		if (this->interpolationTimer > 1.0f)
			this->interpolationTimer = 1.0f;
		this->currentSpeed = this->lastSpeed * (1.0f - this->interpolationTimer);
	}

	float wheelRotationSpeed = ((this->currentSpeed / this->wheelCircumference) * (glm::pi<float>() * 2)) * deltatime;
	rotateWheels(wheelRotationSpeed);
	float steerSpeed = (this->steeringAngle * ((this->currentSpeed > 0.0f || this->currentSpeed < 0.0f) ? glm::clamp((50.0f * (1.0f / this->currentSpeed)), -2.0f, 2.0f) : 0.0f)) * deltatime;

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

	// Back wheels
	this->backWheelsTransform.rotateBy(wheelRotationSpeed, glm::vec3(-1.0f, 0.0f, 0.0f));
}

void GameLogic::Kart::setRequiredUniforms(TMTPair& tmPair)
{
	this->shader.lock()->bind();
	this->shader.lock()->setUniformVec3f("kartColor", this->color);
	this->shader.lock()->setUniformBool("useDiffuseMap", true);
	this->shader.lock()->setUniformBool("useSpecularMap", true);
	this->shader.lock()->setUniformBool("useDiffuseMask", true);
	this->shader.lock()->setUniform1i("diffuseMap", 0);
	this->shader.lock()->setUniform1i("specularMap", 1);
	this->shader.lock()->setUniform1i("diffuseMask", 2);
	this->shader.lock()->setUniformBool("useLighting", tmPair.useLighting);
	this->shader.lock()->unbind();
}

void GameLogic::Kart::onCollision()
{
	this->currentSpeed = 0.0f;
}