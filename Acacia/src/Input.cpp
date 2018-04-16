#include "stdafx.h"
#include "Input.h"


Input::Input()
{
	resetMouseBuffer();
	for (int i = 0; i < 1024; i++)
	{
		inputKeyBuffer[i] = false;
	}
}


Input::~Input()
{
}


void Input::process(SDL_Event &event)
{
	while (SDL_PollEvent(&event))
	{
		handleInputOnEvent(event);
	}
}

bool Input::isKeyInBuffer(int key)
{
	try {
		return inputKeyBuffer[key];
	}
	catch(...){
		return false;
	}
	
}

glm::vec2 Input::getMouseBuffer()
{
	return mouseBuffer;
}

void Input::handleInputOnEvent(SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		inputKeyBuffer[ESCAPE] = true;
		break;
	case SDL_MOUSEMOTION:
		mouseBuffer.x = (float)event.motion.xrel;
		mouseBuffer.y = (float)event.motion.yrel;
		break;
	case SDL_KEYDOWN:
		updateKeysOnKeyDown(event);
		break;
	case SDL_KEYUP:
		updateKeysOnKeyUp(event);
		break;
	}
}

void Input::updateKeysOnKeyUp(SDL_Event &event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		inputKeyBuffer[SDLK_w] = false;
		break;
	case SDLK_a:
		inputKeyBuffer[SDLK_a] = false;
		break;
	case SDLK_s:
		inputKeyBuffer[SDLK_s] = false;
		break;
	case SDLK_d:
		inputKeyBuffer[SDLK_d] = false;
		break;
	case SDLK_LSHIFT:
		inputKeyBuffer[LSHIFT] = false;
		break;
	default:
		break;
	}
}

void Input::updateKeysOnKeyDown(SDL_Event &event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		inputKeyBuffer[SDLK_w] = true;
		break;
	case SDLK_a:
		inputKeyBuffer[SDLK_a] = true;
		break;
	case SDLK_s:
		inputKeyBuffer[SDLK_s] = true;
		break;
	case SDLK_d:
		inputKeyBuffer[SDLK_d] = true;
		break;
	case SDLK_LSHIFT:
		inputKeyBuffer[LSHIFT] = true;
		break;
	case SDLK_ESCAPE:
		inputKeyBuffer[ESCAPE] = true;
	default:
		break;
	}
}

void Input::update()
{
	resetMouseBuffer();
}

void Input::resetMouseBuffer()
{
	mouseBuffer = glm::vec2(0.0f, 0.0f);
}
