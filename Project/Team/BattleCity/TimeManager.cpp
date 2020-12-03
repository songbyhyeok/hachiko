#include "TimeManager.h"
#include "Timer.h"


HRESULT TimeManager::Init()
{
	timer = new Timer();
	timer->Init();

	testTime = 0.0f;
	isTestStart = false;

	return S_OK;
}

void TimeManager::Release()
{
	SAFE_DELETE(timer);
}

void TimeManager::Update(float lockFPS/* = 0.0f*/)
{
	if (timer)
	{
		timer->Tick(lockFPS);
	}

	if (isTestStart)
	{
		testTime += timer->GetDeltaTime();
	}
}

void TimeManager::Render(HDC hdc)
{
#ifdef _DEBUG
	if (timer)
	{
		SetBkMode(hdc, TRANSPARENT);

		wsprintf(strText, "FPS : %d", timer->GetFrameRate());
		TextOut(hdc, 10, 10, strText, strlen(strText));

		sprintf_s(strText, "WorldTime : %f", timer->GetWorldTime());
		TextOut(hdc, 10, 30, strText, strlen(strText));

		sprintf_s(strText, "TestTime : %f", testTime);
		TextOut(hdc, 10, 50, strText, strlen(strText));
	}
#endif
}

float TimeManager::GetDeltaTime()
{
	if (timer)
		return timer->GetDeltaTime();

	return 0.0f;
}

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}
