#include "stdafx.h"
#include "Camera.h"


const glm::vec3 WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

Camera::Camera() : position(glm::vec3(0.0f, 0.0f, 3.0f)),
front(glm::vec3(0.0f, 0.0f, -1.0f)),
up(glm::vec3(0.0f, 1.0f, 0.0f)),
movementSpeed(5.0f),
mouseSensitivity(0.002f),
maxPitchRate( 5.0f),
maxHeadingRate( 5.0f)
{
	this->worldUp = up;
	//this->currentRotationX = 0;
	verticalAngle = 0.0f;
	horizontalAngle = 0.0f;
	updateCamera();


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

glm::mat4 Camera::GetViewMatrix()
{
	
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::UpdateViewByMouse(SDL_Window &window, GLfloat deltaTime, GLfloat mouseX, GLfloat mouseY, GLfloat &lastMouseX, GLfloat &lastMouseY)
{
	//SDL_WarpMouseInWindow(&window, 1024 / 2, 768 / 2);

	pitch = ( mouseY - float(1024 / 2)) * mouseSensitivity;
	yaw = (mouseX - float(768 / 2)) * mouseSensitivity;
	//horizontalAngle += mouseSensitivity * deltaTime * float(1024 / 2 - mouseX);
	//verticalAngle += mouseSensitivity * deltaTime * float(768/2 - mouseY) ;

	//front = glm::vec3(
	//	cos(verticalAngle) * sin(horizontalAngle),
	//	sin(verticalAngle),
	//	cos(verticalAngle)*cos(horizontalAngle));

	//right = glm::vec3(
	//	sin(horizontalAngle - 3.14f / 2.0f),
	//	0.0f,
	//	cos(horizontalAngle - 3.14f / 2.0f));

	//up = glm::cross(right, front);

	//RotateSmoothly(yaw, pitch, 0.0f);

	// move mouse back to center of the window
	SDL_WarpMouseInWindow(&window, 1024 / 2, 768 / 2);

	//float dx = lastMouseX - mouseX;
	//float dy = lastMouseY - mouseY;
	//Heading(horizontalAngle);
	//Pitch(verticalAngle);


	//
	//
	//glm::vec3 axis = glm::cross(front, up);
	////compute quaternion for pitch based on the camera pitch angle
	//glm::quat pitch_quat = glm::angleAxis(_pitch, axis);
	////determine heading quaternion from the camera up vector and the heading angle
	//glm::quat heading_quat = glm::angleAxis(_heading, up);
	////add the two quaternions
	//glm::quat temp = glm::cross(pitch_quat, heading_quat);
	//temp = glm::normalize(temp);
	////update the direction from the quaternion
	//front = glm::rotate(temp, front);
	//front = glm::normalize(front);
	////add the camera delta
	//////position += camera_position_delta;
	////set the look at to be infront of the camera
	////camera_look_at = camera_position + camera_direction * 1.0f;
	////damping for smooth camera
	////_heading *= .5;
	////_pitch *= .5;
	////camera_position_delta = camera_position_delta * .8f;

}

void Camera::Pitch(float angle)
{
	//// Rotate up and look vector about the right vector.
	//XMMATRIX R =
	//	XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);
	//XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&R));
	//XMStoreFloat3(&mLook,
	//	XMVector3TransformNormal(XMLoadFloat3(&mLook), R));

	//glm::mat4 rot = glm::rotate( angle, right);
	//up = glm::normalize(rot);
	//front = 
	
	if (angle < -maxPitchRate)
		angle = -maxPitchRate;
	else if (angle > maxPitchRate)
		angle = maxPitchRate;
	_pitch += angle;

	//Check bounds for pitch
	if (_pitch > 360.0f) {
		_pitch -= 360.0f;
	}
	else if (_pitch < -360.0f) {
		_pitch += 360.0f;
	}
}

void Camera::Heading(float angle)
{
	//Check bounds with the max heading rate so that we aren't moving too fast
	if (angle < -maxHeadingRate) {
		angle = -maxHeadingRate;
	}
	else if (angle > maxHeadingRate) {
		angle = maxHeadingRate;
	}
	//This controls how the heading is changed if the camera is pointed straight up or down
	//The heading delta direction changes
	if (_pitch > 90 && _pitch < 270 || (_pitch < -90 && _pitch > -270)) {
		_heading -= angle;
	}
	else {
		_heading += angle;
	}
	//Check bounds for the camera heading
	if (_heading > 360.0f) {
		_heading -= 360.0f;
	}
	else if (_heading < -360.0f) {
		_heading += 360.0f;
	}
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
}

void Camera::updateCamera()
{
	//glm::vec3 front;

	this->right = glm::normalize(glm::cross(this-> front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

	
}


void Camera::RotateCamera(float yawDegrees, float pitchDegrees)
{
	//// Implements the rotation logic for the first person style and
	//// spectator style camera behaviors. Roll is ignored.

	//_accumPitchDegrees += pitchDegrees;

	//if (_accumPitchDegrees > 90.0f)
	//{
	//	pitchDegrees = 90.0f - (_accumPitchDegrees - pitchDegrees);
	//	_accumPitchDegrees = 90.0f;
	//}

	//if (_accumPitchDegrees < -90.0f)
	//{
	//	pitchDegrees = -90.0f - (_accumPitchDegrees - pitchDegrees);
	//	_accumPitchDegrees = -90.0f;
	//}

	//Quaternion rot;

	//// Rotate camera about the world y axis.
	//// Note the order the quaternions are multiplied. That is important!
	//if (yawDegrees != 0.0f)
	//{
	//	rot = glm::angleAxis(yawDegrees, WORLD_YAXIS);
	//	_orientation = rot * _orientation;
	//}

	//// Rotate camera about its local x axis.
	//// Note the order the quaternions are multiplied. That is important!
	//if (pitchDegrees != 0.0f)
	//{
	//	rot = glm::angleAxis(pitchDegrees, WORLD_XAXIS);
	//	_orientation = _orientation * rot;
	//}

	/*glm::quat temp, quat_view, result;
	
	temp.x = x * sin(Angle / 2);
	temp.y = y * sin(Angle / 2);
	temp.z = z * sin(Angle / 2);
	temp.w = cos(Angle / 2);

	quat_view.x = view.x;
	quat_view.y = view.y;
	quat_view.z = view.z;
	quat_view.w = 0;
	
	result = glm::cross(glm::cross(temp, quat_view), glm::conjugate(temp));

	view.x = result.x;
	view.y = result.y;
	view.z = result.z;
	std::cout << glm::to_string(view);*/
}



void Camera::RotateSmoothly(float yawDegrees, float pitchDegrees, float rollDegrees)
{
	// This method applies a scaling factor to the rotation angles prior to
	// using these rotation angles to rotate the camera. This method is usually
	// called when the camera is being rotated using an input device (such as a
	// mouse or a joystick). 

	//yawDegrees *= _rotationSpeed;
	//pitchDegrees *= _rotationSpeed;
	//rollDegrees *= m_rotationSpeed;

	pitchDegrees = -pitchDegrees;
	yawDegrees = -yawDegrees;

	RotateCamera(yawDegrees, pitchDegrees);

}

void Camera::SetOrientation(const glm::quat &orientation)
{
	glm::mat4 m = glm::toMat4(orientation);

	_accumPitchDegrees = glm::degrees(asinf(m[1][2]));
	//_orientation = orientation;

	glm::lookAt(_eye, _eye + _viewDir, WORLD_YAXIS);
	
}

//void Camera::Move2D(int x, int y) {
//	//compute the mouse delta from the previous mouse position
//	glm::vec3 mouse_delta = mouse_position - glm::vec3(x, y, 0);
//
//	//float dx = 
//	//if the camera is moving, meaning that the mouse was clicked and dragged, change the pitch and heading
//	
//		ChangeHeading(.08f * mouse_delta.x);
//		ChangePitch(.08f * mouse_delta.y);
//	
//	mouse_position = glm::vec3(x, y, 0);
//}


void Camera::rotate(float headingDegrees, float pitchDegrees)
{
	// Rotates the camera based on its current behavior.
	// Note that not all behaviors support rolling.

	pitchDegrees = -pitchDegrees;
	headingDegrees = -headingDegrees;

	// Implements the rotation logic for the first person style and
	// spectator style camera behaviors. Roll is ignored.

	_accumPitchDegrees += pitchDegrees;

	if (_accumPitchDegrees > 90.0f)
	{
		pitchDegrees = 90.0f - (_accumPitchDegrees - pitchDegrees);
		_accumPitchDegrees = 90.0f;
	}

	if (_accumPitchDegrees < -90.0f)
	{
		pitchDegrees = -90.0f - (_accumPitchDegrees - pitchDegrees);
		_accumPitchDegrees = -90.0f;
	}

}