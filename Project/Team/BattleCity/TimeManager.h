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
	HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update(float lockFPS = 0.0f);		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }


	TimeManager();
	~TimeManager();
};

