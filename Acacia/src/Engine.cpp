#include "stdafx.h"
#include "Engine.h"
#include "Errors.h"

#include "Shader.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "OBJParser.h"

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
	SDL_GL_DeleteContext(glContext);
}

void AcaciaEngine::run()
{
	initSystems();
	mainLoop();
}

void AcaciaEngine::initSystems()
{
	initSDLWindow();
	initCamera();
	input = new Input();
}

void AcaciaEngine::initSDLWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	window = SDL_CreateWindow("Acacia Engine. Beta Version", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		screenResolution.x, screenResolution.y, SDL_WINDOW_OPENGL);
	if (window == nullptr)
		fatalError("SDL Window could not be created!");
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created!");
	GLenum error = glewInit();
	if (error != GLEW_OK)
		fatalError("Could not initialize glew!");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
}

void AcaciaEngine::initCamera()
{
	camera = new Camera();
	camera->setPerspective(70.0f, (float)screenResolution.x / screenResolution.y, 0.1f, 100.0f);
}

void AcaciaEngine::mainLoop()
{
	ModelData cubeModel = OBJParser().getModelData("cube"); // abstract to model/entity
	Shader colorShader("colorShading.vert", "colorShading.frag");
	
	// TODO: Create CUBE VAO - to abstract into model class
	// model(const ModelData &model);
	VertexArray cube_vao;
	VertexBuffer cube_vb(&cubeModel.positions[0], cubeModel.positions.size() * sizeof(float));
	VertexBuffer cube_texture_vb(&cubeModel.texcoords[0], cubeModel.texcoords.size() * sizeof(float));
	cube_vao.addBuffer(cube_vb, 0, 3);
	cube_vao.addBuffer(cube_texture_vb, 1, 2);
	IndexBuffer cube_ib(&cubeModel.indices[0], cubeModel.indices.size());
 
	Texture cubeTexture;
	cubeTexture.load("box", GL_TEXTURE_2D);
	
	// TODO: Abstract Texture
	/*unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	

	int width, height;
	unsigned char * imageData = nullptr;
	try {
		imageData = SOIL_load_image("res/textures/box.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		if(imageData)
			SOIL_free_image_data(imageData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	catch (const std::exception &e)
	{
		std::cout << "Could not load image" << std::endl;
	}*/
	// also add glDeleteTexture(texture) to destructor


	Renderer renderer;

	while (engineState != ENGINE_STATE::EXIT)
	{
		// Update game loop //
		updateDeltaTime();
		input->process(event);
		processCameraMovementFromInput();
		input->update();
		camera->update();

		// Render //
		renderer.prepare();

		colorShader.bind();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		colorShader.setUniformMatrix4("model", model);
		colorShader.setUniformMatrix4("view", camera->getView());
		colorShader.setUniformMatrix4("projection", camera->getPerspective());
		
		// TODO: abstract to Texture: Bind Texture 
		//glActiveTexture(GL_TEXTURE0); // GL_TEXTURE + slot
		//glBindTexture(GL_TEXTURE_2D, texture);
		cubeTexture.bind(0);
		colorShader.setUniform1i("u_Texture", 0); // 0 is slot 0

		//renderer.render(vao, ib, shader);
		renderer.render(cube_vao, cube_ib, colorShader);

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


