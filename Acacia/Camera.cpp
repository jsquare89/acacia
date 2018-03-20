#include "stdafx.h"
#include "Camera.h"


const GLfloat DEFAULT_FOV = 90.0f;
const glm::vec3 WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 WORLD_ZAXIS(0.0f, 0.0f, 1.0f);
const float NINETY_DEGREE_IN_RADIANS = 1.5708;
const float EYE_SPEED_MIN = 0.001f;
const float EYE_SPEED_MAX = 0.004f;

Camera::Camera() :	eye(glm::vec3(0.0f, 0.0f, 3.0f)),
					forward(glm::vec3(0.0f, 0.0f, -1.0f)),
					up(glm::vec3(0.0f, 1.0f, 0.0f)),
					cameraRotationSpeed(0.002f)
{
	SetNormRightUp();
	yawRadians = 0.0f;
	pitchRadians = 0.0f;
	orientation = glm::quat();
	speed = EYE_SPEED_MIN;
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

void Camera::updateView()
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

glm::mat4 Camera::getView()
{
	return view;
}

void Camera::updateYawPitchByMouse(const glm::vec2 &mouseOffset)
{
	yawRadians += mouseOffset.x * cameraRotationSpeed;
	pitchRadians += mouseOffset.y * cameraRotationSpeed;
	constrainPitch();
}

void Camera::move(const Camera_Movement &direction)
{
	int dx = 0;
	int dz = 0;
	if (direction == FORWARD)
		dz = 1;
	if (direction == BACKWARD)
		dz = -1;
	if (direction == LEFT)
		dx = -1;
	if (direction == RIGHT)
		dx = 1;

	glm::mat4 currentView = view;
	glm::vec3 forward(currentView[0][2], currentView[1][2], currentView[2][2]);
	glm::vec3 right(currentView[0][0], currentView[1][0], currentView[2][0]);

	eye += (-dz * forward + dx * right) * speed;
}

void Camera::SetNormRightUp()
{
	this->right = glm::normalize(glm::cross(this-> forward, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->forward));
}

void Camera::update()
{
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

void Camera::setSpeedMax()
{
	speed = EYE_SPEED_MAX;
}

void Camera::setSpeedMin()
{
	speed = EYE_SPEED_MIN;
}