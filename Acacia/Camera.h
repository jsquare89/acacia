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

	glm::mat4 getPerspective();
	glm::mat4 getView();
	void Camera::setPerspective(float FieldOfViewDegrees, float aspectRatio, float nearClip, float farClip);
	
	void UpdateYawPitchByMouse(SDL_Window &window, SDL_MouseMotionEvent &mme, glm::uvec2 prevMouse);
	void UpdatePosition(Camera_Movement direction, GLfloat deltaTime);
	void RotateCamera(float headingDegrees, float pitchDegrees);
	void RotateSmoothly(float headingDegrees, float pitchDegrees, float rollDegrees);

	void rotate(float headingDegrees, float pitchDegrees);

	void constrainPitch(float pitchDegrees);

	void Pitch(float angle);
	void Heading(float angle);
	
	void SetOrientation(const glm::quat &orientation);
	void Update();

	

private:
	void updateView();
	void SetNormRightUp();

	glm::vec3 position;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;

	bool viewDirty = true;

	glm::mat4 view;
	glm::mat4 projection;

	float _pitch;
	float _heading;

	float maxPitchRate;
	float maxHeadingRate;

	glm::quat orientation;

	glm::quat rotationQuat;
	glm::vec3 mousePos;

	glm::vec3 worldUp;


	float pitch;
	float yaw;
	GLfloat roll;

	GLfloat movementSpeed;
	float cameraRotationSpeed;
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


	

};

