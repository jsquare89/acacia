#pragma once

#include <SDL/SDL.h>

enum ACACIA_KEYS {
	LSHIFT = 1023,
	ESCAPE = 1022
};

class Input
{
public:
	Input();
	~Input();
	void process(SDL_Event & event);
	bool isKeyInBuffer(int key);
	glm::vec2 getMouseBuffer();
	void update();

private:
	void handleInputOnEvent(SDL_Event & event);
	void updateKeysOnKeyUp(SDL_Event & event);
	void updateKeysOnKeyDown(SDL_Event & event);
	void resetMouseBuffer();

	bool inputKeyBuffer[1024];
	glm::vec2 mouseBuffer;
};

