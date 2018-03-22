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
	shader.compile("colorShading.vert", "colorShading.frag");
	shader.link();
}

void AcaciaEngine::initCamera()
{
	camera = new Camera();
	camera->setPerspective(70.0f, (float)screenResolution.x / screenResolution.y, 0.1f, 100.0f);
}

void AcaciaEngine::mainLoop()
{
	Mesh cube;
	cube.load("cube");
	Entity myCube(&cube, glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), 1);
	
	

	

	while (engineState != ENGINE_STATE::EXIT)
	{
		updateDeltaTime();

		input->process(event);
		processCameraMovementFromInput();

		input->update();
		camera->update();

		renderer.prepare();
		shader.use();

		GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat pos[] = { 0.0, 0.0, 1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, white);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white);

		shader.setUniformMatrix4(shader.getUniformLocation("view"), camera->getView());
		shader.setUniformMatrix4(shader.getUniformLocation("projection"), camera->getPerspective());
		//glUniformMatrix4fv(shader.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->getView()));
		//glUniformMatrix4fv(shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(camera->getPerspective()));
		//glUniformMatrix4fv(program.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
		
		//glm::mat4 model;
		//	GLfloat angle = glm::radians(20.0f * i);
		//	if (i % 3 == 0) // make every 3rd cube rotate
		//		angle = time * angle;
		//	model = glm::translate(model, cubePositions[i]);
		//	model = glm::rotate(model,
		//		angle, glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setUniformMatrix4(shader.getUniformLocation("model"), myCube.getTransformMatrix());
		
		renderer.render(myCube, shader);


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


