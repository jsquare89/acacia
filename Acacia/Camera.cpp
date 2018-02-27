#include "stdafx.h"
#include "Camera.h"


const GLfloat DEFAULT_FOV = 90.0f;
const glm::vec3 WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 WORLD_ZAXIS(0.0f, 0.0f, 1.0f);
const float NINETY_DEGREE_IN_RADIANS = 1.5708;

Camera::Camera() :	eye(glm::vec3(0.0f, 0.0f, 3.0f)),
					forward(glm::vec3(0.0f, 0.0f, -1.0f)),
					up(glm::vec3(0.0f, 1.0f, 0.0f)),
					movementSpeed(5.0f),
					cameraRotationSpeed(0.002f),
					maxPitchRate( 5.0f),
					maxHeadingRate( 5.0f)
{
	this->worldUp = up;
	//this->currentRotationX = 0;
	verticalAngle = 0.0f;
	horizontalAngle = 0.0f;
	SetNormRightUp();
	yawRadians = 0.0f;
	pitchRadians = 0.0f;
	orientation = glm::quat();
	// quaternion implemention
	_eye = glm::vec3(0.0f, 0.0f, 3.0f);
	_savedEye = glm::vec3(0.0f, 0.0f, 0.0f);
	_target = glm::vec3(0.0f, 0.0f, 0.0f);
	_xAxis = glm::vec3(0.1f, 0.0f, 0.0f);
	_yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	_targetYAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	_zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	_viewDir = glm::vec3(0.0f, 0.0f, -1.0f);

	_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	_currentVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	_projMatrix = glm::mat4();
	_viewProjMatrix = glm::mat4(); 

	_rotationSpeed = 0.02f;

	_accumPitchDegrees = 0.0f;
}


Camera::~Camera()
{
}

void Camera::setPerspective(float fieldOfViewDegrees, float aspectRatio, float nearClipDistance, float farClipDistance )
{
	projection = glm::perspective(glm::radians(fieldOfViewDegrees), aspectRatio, nearClipDistance, farClipDistance);
}

glm::mat4 Camera::getPerspective()
{
	return projection;
}

void Camera::updateRotationOfView()
{
	glm::quat qPitch = glm::angleAxis(pitchRadians, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(yawRadians, glm::vec3(0, 1, 0));
	orientation = qPitch * qYaw;
	orientation = glm::normalize(orientation);
	glm::mat4 rotatation = glm::mat4_cast(orientation);
	glm::mat4 translatation = glm::mat4(1.0f);
	translatation = glm::translate(translatation, -eye);
	view = rotatation * translatation;
}

void Camera::updateView()
{
	updateRotationOfView();


}

glm::mat4 Camera::getView()
{
	return view;
}


void Camera::UpdateYawPitchByMouse(SDL_Window &window, SDL_MouseMotionEvent &mme)
{
	yawRadians += (float)mme.xrel * cameraRotationSpeed;
	pitchRadians += (float)mme.yrel * cameraRotationSpeed;
	constrainPitch();
	printf("pitch:%f yaw:%f\n", pitchRadians, yawRadians);
}


void Camera::move(float dx, float dy, float dz)
{
	glm::vec3 eye = this->eye;
	glm::vec3 forwards;

	forwards = glm::cross(WORLD_YAXIS, _xAxis);
	forwards = glm::normalize(forwards);

	eye += _xAxis * dx;
	eye += WORLD_YAXIS * dy;
	eye += forwards * dz;

	setPosition(eye);
}
void Camera::move(const glm::vec3 &direction, const glm::vec3 &amount)
{
	eye.x += direction.x * amount.x;
	eye.y += direction.y * amount.y;
	eye.z += direction.z * amount.z;

	updateRotationOfView();
}

void Camera::setPosition(const glm::vec3 &position)
{
	this->eye = position;
	updateRotationOfView();
}

void Camera::UpdatePosition(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD)
		this->eye += this->forward * velocity;
	if (direction == BACKWARD)
		this->eye -= this->forward * velocity;
	if (direction == LEFT)
		this->eye -= this->right * velocity;
	if (direction == RIGHT)
		this->eye += this->right * velocity;
}

void Camera::SetNormRightUp()
{
	this->right = glm::normalize(glm::cross(this-> forward, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->forward));
}


void Camera::update()
{
	updateRotationOfView();
	updateView();
}

void Camera::constrainPitch()
{
	if (pitchRadians > NINETY_DEGREE_IN_RADIANS)
	{
		pitchRadians = NINETY_DEGREE_IN_RADIANS;
	}
	if (pitchRadians < -NINETY_DEGREE_IN_RADIANS)
	{
		pitchRadians = -NINETY_DEGREE_IN_RADIANS;
	}
}
