#pragma once

#include "pch.h"

class Timer
{
private:
	bool isHardware;			// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����
	float timeScale;			// ��� �������� �ʴ� �������� ����� �������� �ð� ������ ��ȯ
	float timeElapsed;			// ������ �ð��� ���� �ð��� �����
	__int64 curTime;			// ���� �ð� (���� Ÿ�̸� ��)
	__int64 lastTime;			// ���� �ð� (���� Ÿ�̸� ��)
	__int64 periodFrequency;	// ���� Ÿ�̸��� ���ļ� (�ʴ� ������), �������� ������ 0 ��ȯ

	unsigned long frameRate;
	unsigned long fPSFrameCount;
	float fpsTimeElapsed;
	float worldTime;

public:

	HRESULT Init();
	void Tick(float lockFPS = 0.0f);

	unsigned long GetFrameRate() { return frameRate; }
	float GetWorldTime() { return worldTime; }
	float GetDeltaTime() { return timeElapsed; }

	Timer();
	~Timer();
};

