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
	void updateYawPitchByMouse(const glm::vec2 &mouseOffset);
	void move(const Camera_Movement &direction);
	void setSpeedMax();
	void setSpeedMin();
	void update();

private:
	void updateView();
	void SetNormRightUp();
	void constrainPitch();
	

	glm::vec3 eye;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
	glm::vec3 worldUp;
	glm::mat4 view;
	glm::mat4 projection;
	glm::quat orientation;
	float pitchRadians;
	float yawRadians;
	float cameraRotationSpeed;
	float speed;
};

