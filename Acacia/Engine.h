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
	void initCamera();
	void initMouse();
	void setupWindowSDL();
	void initShaders();
	void mainLoop();
	void setDeltaTime();
	void clearColorBuffer();
	void processUserInput();
	void handleInputOnEvent(SDL_Event &event);
	void updateKeysOnKeyDown(SDL_Event &event);
	void updateKeysOnKeyUp(SDL_Event &event);
	void processMovementOnKeys();
	void updateCamera(float deltaTime, glm::vec2 mousePos );
	void render();

	SDL_Window* window;
	glm::uvec2 screenResolution;
	EngineState engineState;
	
	GLSLProgram program;

	Object *triangle;

	Camera *camera;
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	GLfloat cameraYaw;
	GLfloat cameraPitch;
	bool inputKeys[1024]; 
	glm::uvec2 mouseCurrentPosition;
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrameTime = 0.0f;
	GLfloat time;
	SDL_Event event;
};

