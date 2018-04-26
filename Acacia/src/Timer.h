#pragma once
class Timer
{
public:
	Timer();
	~Timer();

	void update();
	float getDeltaTime();
	float getCurrentTime();
private:
	float deltaTime;
	float lastFrameTime;
};

