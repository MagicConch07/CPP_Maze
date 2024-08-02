#include "GameTimer.h"

GameTimer::GameTimer()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

    timeScale = 1.0 / (double)periodFrequency;
}

void GameTimer::ResetTime()
{
	startTime = clock();
}

double GameTimer::GetGameTime()
{
	endTime = clock();
	return (endTime - startTime) / CLOCKS_PER_SEC;
}

void GameTimer::Update()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

    deltaTime = (double)(currentTime - lastTime) * timeScale;

    lastTime = currentTime;
}

double GameTimer::GetDeltaTime()
{
    return deltaTime;
}

void GameTimer::Init()
{
    endTime = 0;

    currentTime = 0;
    lastTime = 0;
    periodFrequency = 0;
    timeScale = 0;
    deltaTime = 0;
}
