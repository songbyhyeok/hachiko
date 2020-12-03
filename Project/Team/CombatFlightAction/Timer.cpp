#include "Timer.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

HRESULT Timer::Init()
{
	frameRate = 0;
	fPSFrameCount = 0;
	fpsTimeElapsed = 0;
	worldTime = 0;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime); // 현재 시간 (진동수의 누적값)
		timeScale = 1.0f / periodFrequency;
	}

	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

	return S_OK;
}

void Timer::Tick(float lockFPS)
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	}

	else
	{
		curTime = timeGetTime();
	}

	timeElapsed = (curTime - lastTime) * timeScale;

	if (lockFPS > 0.0f)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			if (isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			}

			else
			{
				curTime = timeGetTime();
			}

			timeElapsed = (curTime - lastTime) * timeScale;
		}
	}

	worldTime += timeElapsed;

	fPSFrameCount++;
	fpsTimeElapsed += timeElapsed;

	if (fpsTimeElapsed > 1.0f)
	{
		frameRate = fPSFrameCount;
		fPSFrameCount = 0;
		fpsTimeElapsed = 0;
	}

	lastTime = curTime;

}

Timer::Timer()
{
}

Timer::~Timer()
{
}
