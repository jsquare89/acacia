// (C) Jarred Jardine 2017
#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Object.h"
#include "Camera.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

enum class EngineState{RUN, EXIT};

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	void initSystems();
	void initShaders();
	void mainLoop();
	void handleInput();
	void handleMovement();
	void UpdateCamera(float deltaTime, glm::vec2 mousePos );
	void render();

	SDL_Window* window;
	uint32_t screenWidth;
	uint32_t screenHeight;
	EngineState engineState;
	
	GLSLProgram program;

	Object *triangle;


	//Camera
	Camera *camera;
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	GLfloat yaw;
	GLfloat pitch;

	//input
	bool keys[1024];
	//mouse 
	GLfloat lastX, lastY;
	bool firstMouse;

	// time
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	GLfloat time;
};

