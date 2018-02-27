#include "stdafx.h"
#include "Camera.h"

const GLfloat DEFAULT_FOV = 90.0f;
const glm::vec3 WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

Camera::Camera() :	position(glm::vec3(0.0f, 0.0f, 3.0f)),
					front(glm::vec3(0.0f, 0.0f, -1.0f)),
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
	yaw = 0.0f;
	pitch = 0.0f;
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

void Camera::updateView()
{
	//view = glm::lookAt(this->position, this->position + this->front, this->up);

	//glm::quat key_quat = glm::quat(glm::vec3(pitch, yaw, roll));
	
	glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
	
	orientation = qPitch * qYaw;
	orientation = glm::normalize(orientation);

	glm::mat4 rota = glm::mat4_cast(orientation);
	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -position);

	view = rota * translate;

	//orientation = glm::quat_cast(view);
}

glm::mat4 Camera::getView()
{
	return view;
}


void Camera::UpdateYawPitchByMouse(SDL_Window &window, SDL_MouseMotionEvent &mme, glm::uvec2 prevMouse)
{
	int xDistanceFromWindowCenter =  mme.xrel - prevMouse.x ;
	int yDistanceFromWindowCenter = prevMouse.x - mme.yrel  ;
	yaw += (float)mme.xrel * cameraRotationSpeed;
	pitch += (float)mme.yrel * cameraRotationSpeed;
	printf("yaw:%f  pitch:%f", yaw, pitch);

	//SDL_WarpMouseInWindow(&window, 1024 / 2, 768 / 2);
}

void Camera::UpdatePosition(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD)
		this->position += this->front * velocity;
	if (direction == BACKWARD)
		this->position -= this->front * velocity;
	if (direction == LEFT)
		this->position -= this->right * velocity;
	if (direction == RIGHT)
		this->position += this->right * velocity;
	updateView();
}

void Camera::SetNormRightUp()
{
	this->right = glm::normalize(glm::cross(this-> front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}


void Camera::Update()
{
	updateView();
}

void Camera::rotate(float yawDegrees, float pitchDegrees)
{
	// Rotates the camera based on its current behavior.
	// Note that not all behaviors support rolling.

	pitchDegrees = -pitchDegrees;
	yawDegrees = -yawDegrees;
	// Implements the rotation logic for the first person style and
	// spectator style camera behaviors. Roll is ignored.

	constrainPitch(pitchDegrees);

	glm::quat rotate;
	// Rotate camera about the world y axis.
	if (yaw != 0.0f)
	{
		rotate = glm::angleAxis(yaw, WORLD_YAXIS);
		orientation = glm::cross(orientation, rotate);
	}

	// Rotate camera about its local x axis.
	if (pitch != 0.0f)
	{
		rotate = glm::angleAxis(pitch, WORLD_XAXIS);
		orientation = glm::cross(orientation, rotate);
		int i = 0;
	}

	view = glm::toMat4(orientation);

}

void Camera::constrainPitch(float pitchDegrees)
{
	_accumPitchDegrees += pitchDegrees;

	if (_accumPitchDegrees > 90.0f)
	{
		pitch = 90.0f - (_accumPitchDegrees - pitchDegrees);
		_accumPitchDegrees = 90.0f;
	}

	if (_accumPitchDegrees < -90.0f)
	{
		pitch = -90.0f - (_accumPitchDegrees - pitchDegrees);
		_accumPitchDegrees = -90.0f;
	}
}
