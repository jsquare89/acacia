#pragma once
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>



enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{

public:
	Camera();
	~Camera();



	void Camera::SetPerspective(float FieldOfViewDegrees, float aspectRatio, float nearClip, float farClip);
	glm::mat4 GetPerspectiveMatrix();
	glm::mat4 GetViewMatrix();
	void UpdateViewByMouse(SDL_Window &window, GLfloat detlaTime, GLfloat mouseX, GLfloat mouseY, GLfloat &lastMouseX, GLfloat &lastMouseY);
	void UpdatePosition(Camera_Movement direction, GLfloat deltaTime);
	//void RotateCamera(GLfloat Angle, GLfloat x, GLfloat y, GLfloat z);
	void RotateCamera(float headingDegrees, float pitchDegrees);
	void RotateSmoothly(float headingDegrees, float pitchDegrees, float rollDegrees);

	void Rotate(float headingDegrees, float pitchDegrees);

	void Pitch(float angle);
	void Heading(float angle);
	void Move2D(int x, int y);
	void UpdateViewMatrix();
	void SetOrientation(const glm::quat &orientation);
	void Update();

	glm::vec3 position;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;

	bool viewDirty = true;

	//
	glm::mat4 view;
	glm::mat4 projection;

	float _pitch;
	float _heading;

	float maxPitchRate;
	float maxHeadingRate;

	glm::quat rotationQuat;
	glm::vec3 mousePos;

	glm::vec3 worldUp;


	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	glm::vec2 mousePosition;

	//GLfloat currentRotationX;
	GLfloat verticalAngle;
	GLfloat horizontalAngle;

	float _accumPitchDegrees;
	float _savedAccumPitchDegrees;
	float _rotationSpeed;
	glm::mat4 _projMatrix;
	glm::mat4 _viewProjMatrix;
	glm::vec3 _eye;
	glm::vec3 _savedEye;
	glm::vec3 _target;
	glm::vec3 _targetYAxis;
	glm::vec3 _xAxis;
	glm::vec3 _yAxis;
	glm::vec3 _zAxis;
	glm::vec3 _viewDir;
	glm::vec3 _acceleration;
	glm::vec3 _currentVelocity;
	glm::vec3 _velocity;

	

private:
	void SetNormRightUp();

};

