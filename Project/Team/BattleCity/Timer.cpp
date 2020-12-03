#include "Timer.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")


HRESULT Timer::Init()
{
	//bool	isHardware;		// 고성능 타이머를 쓸 수 있는지 여부
	//float	timeScale;		// 경과 진동수를 초당 진동수로 나누어서 진동수를 시간단위로 변환
	//float	timeElapsed;	// 마지막 시간과 현재 시간의 경과량
	//__int64	currTime;		// 현재 시간 (고성능 타이머 값)
	//__int64 lastTime;		// 이전 시간 (고성능 타이머 값)
	//__int64 periodFrequency;// 고성능 타이머의 주파수 (초당 진동수), 지원하지 않으면 0 반환

	frameRate = 0;
	FPSFrameCount = 0;
	FPSTimeElapsed = 0;
	worldTime = 0;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);	// 현재시간 (진동수의 누적값)
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
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}

	timeElapsed = (currTime - lastTime) * timeScale;

	if (lockFPS > 0.0f)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			if (isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
			}
			else
			{
				currTime = timeGetTime();
			}

			timeElapsed = (currTime - lastTime) * timeScale;
		}
	}


	worldTime += timeElapsed;

	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;
	if (FPSTimeElapsed > 1.0f)
	{
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0;
	}

	lastTime = currTime;

}

Timer::Timer()
{
}


Timer::~Timer()
{
}
