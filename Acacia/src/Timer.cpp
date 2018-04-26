#include "stdafx.h"
#include "Timer.h"
#include <SDL/SDL.h>

Timer::Timer()
{
	deltaTime = 0.0f;
	lastFrameTime = 0.0f;
}


Timer::~Timer()
{
}

void Timer::update()
{
	float currentFrameTime = getCurrentTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}

float Timer::getDeltaTime()
{
	return deltaTime;
}

float Timer::getCurrentTime()
{
	return SDL_GetTicks() / 1000.0f;
}
