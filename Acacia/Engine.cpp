#include "stdafx.h"
#include "Engine.h"
#include "Errors.h"

#include <iostream>
#include <string>

#include <SOIL\SOIL.h>

Engine::Engine() :	screenResolution{1024,768},
					time(0.0f),
					window(nullptr),
					engineState(ENGINE_STATE::RUN)
{
}

Engine::~Engine()
{
	delete camera;
	delete input;
}

void Engine::run()
{
	initSystems();
	mainLoop();
}

void Engine::initSystems()
{
	initSDLWindow();
	initShaders();
	initCamera();
	input = new Input();
}

void Engine::initCamera()
{
	camera = new Camera();
	camera->setPerspective(70.0f, (float)screenResolution.x / screenResolution.y, 0.1f, 100.0f);
}


void Engine::initSDLWindow()
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
}

void Engine::initShaders()
{
	program.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	program.linkShaders();
}

void Engine::mainLoop()
{
	GLuint cubeIndices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLfloat cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//// Color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Load and create a texture 
	GLuint texture1;
	GLuint texture2;
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("Textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
									 
	// ===================
	// Texture 2
	// ===================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("Textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);


	while (engineState != ENGINE_STATE::EXIT)
	{
		updateDeltaTime();
		input->process(event);
		processCameraMovement();


		input->update();
		camera->update();

		clearColorBuffer();

		// Draw our first triangle
		program.use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(program.getUniformLocation("ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(program.getUniformLocation("ourTexture2"), 1);
		
		// transform in vertex shader
		glUniformMatrix4fv(program.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->getView()));
		glUniformMatrix4fv(program.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(camera->getPerspective()));

		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			GLfloat angle = glm::radians(20.0f * i);
			if (i % 3 == 0) // make every 3rd cube rotate
				angle = time * angle;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, 
				angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(program.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}

}

void Engine::updateDeltaTime()
{
	time = SDL_GetTicks() / 1000.0f; // time in seconds
	GLfloat currentFrame = time;
	deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;
}

void Engine::clearColorBuffer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::processCameraMovement()
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

void Engine::render()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.use();

	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);

	program.unuse();

	glEnd();

	// Swap buffer and draw everything to the screen.
	SDL_GL_SwapWindow(window);
}


