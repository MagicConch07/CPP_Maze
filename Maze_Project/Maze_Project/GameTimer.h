#pragma once
#include "define.h"

class GameTimer
{
private:
	clock_t startTime = clock();
	double endTime = 0;

	__int64 currentTime = 0;
	__int64 lastTime = 0;
	__int64 periodFrequency = 0;
	double timeScale = 0;
	double deltaTime = 0;

public:
	GameTimer();
	void ResetTime();
	double GetGameTime();
	void Update();
	double GetDeltaTime();
	void Init();
};

