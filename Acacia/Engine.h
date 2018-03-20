// (C) Jarred Jardine 2017
#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Camera.h"
#include "Input.h"
#include "Mesh.h"
#include "Texture.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>



enum ENGINE_STATE{RUN, EXIT};


class AcaciaEngine
{
public:
	AcaciaEngine();
	~AcaciaEngine();

	void run();

private:
	void initSystems();
	void initCamera();
	void initSDLWindow();
	void initShaders();
	void mainLoop();
	void updateDeltaTime();
	void clearColorBuffer();
	void processCameraMovementFromInput();
	void render();

	SDL_Window* window;
	glm::uvec2 screenResolution;
	ENGINE_STATE engineState;
	
	GLSLProgram program;

	Camera *camera;
	Input *input;

	bool inputKeyBuffer[1024]; 
	glm::vec2 mouseBuffer;
	SDL_Event event;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrameTime = 0.0f;
	GLfloat time;
	
};

