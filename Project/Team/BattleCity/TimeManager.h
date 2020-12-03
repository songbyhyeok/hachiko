#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;

	char strText[256];

	bool isTestStart;
	float testTime;

public:
	HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update(float lockFPS = 0.0f);		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }


	TimeManager();
	~TimeManager();
};

