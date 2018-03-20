#include "stdafx.h"
#include "Engine.h"
#include "Errors.h"

#include <iostream>
#include <string>

#include <SOIL\SOIL.h>

AcaciaEngine::AcaciaEngine() :	screenResolution{1024,768},
					time(0.0f),
					window(nullptr),
					engineState(ENGINE_STATE::RUN)
{
}

AcaciaEngine::~AcaciaEngine()
{
	delete camera;
	delete input;
}

void AcaciaEngine::run()
{
	initSystems();
	mainLoop();
}

void AcaciaEngine::initSystems()
{
	initSDLWindow();
	initShaders();
	initCamera();
	input = new Input();
}

void AcaciaEngine::initCamera()
{
	camera = new Camera();
	camera->setPerspective(70.0f, (float)screenResolution.x / screenResolution.y, 0.1f, 100.0f);
}


void AcaciaEngine::initSDLWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	window = SDL_CreateWindow("Acacia Engine. Beta Version", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenResolution.x, screenResolution.y, SDL_WINDOW_OPENGL);
	if (window == nullptr)
		fatalError("SDL Window could not be created!");
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created!");
	GLenum error = glewInit();
	if (error != GLEW_OK)
		fatalError("Could not initialize glew!");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
}

void AcaciaEngine::initShaders()
{
	program.compileShaders("colorShading.vert", "colorShading.frag");
	program.linkShaders();
}

void AcaciaEngine::mainLoop()
{

	Mesh myCube;
	myCube.load("cube.obj");
	

	

	while (engineState != ENGINE_STATE::EXIT)
	{
		updateDeltaTime();

		input->process(event);
		processCameraMovementFromInput();

		input->update();
		camera->update();

		myCube.draw();

		// all code below to refactor to render once working properly
		clearColorBuffer();

		program.use();

		

		SDL_GL_SwapWindow(window);
	}

}

void AcaciaEngine::updateDeltaTime()
{
	time = SDL_GetTicks() / 1000.0f; // time in seconds
	GLfloat currentFrame = time;
	deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;
}

void AcaciaEngine::clearColorBuffer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AcaciaEngine::processCameraMovementFromInput()
{
	camera->updateYawPitchByMouse(input->getMouseBuffer());

	if (input->isKeyInBuffer(SDLK_w))
		camera->move(FORWARD);
	if (input->isKeyInBuffer(SDLK_a))
		camera->move(LEFT);
	if (input->isKeyInBuffer(SDLK_s))
		camera->move(BACKWARD);
	if (input->isKeyInBuffer(SDLK_d))
		camera->move(RIGHT);
	if (input->isKeyInBuffer(LSHIFT))
		camera->setSpeedMax();
	else
		camera->setSpeedMin();
	if (input->isKeyInBuffer(ESCAPE))
		engineState = ENGINE_STATE::EXIT;
}

void AcaciaEngine::render()
{
	//previous code, what is program unuse ,glend
	//GLuint timeLocation = program.getUniformLocation("time");
	//glUniform1f(timeLocation, time);

	//program.unuse();

	//glEnd();

	
}


