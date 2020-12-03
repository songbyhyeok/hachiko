#include "MainGame.h"
#include "Image.h"
#include "GameManager.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	isInit = true;

	ImageManager::GetSingleton()->Init();
	KeyManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->AddSound("Sound/Dark Waltz.mp3", "Sound/Dark Waltz.mp3", true, true); //bgm

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	volume = 0;

	gameMgr = new GameManager();
	gameMgr->Init();

	return S_OK;
}

void MainGame::Release()
{
	if (gameMgr)
	{
		gameMgr->Release();
		SAFE_DELETE(gameMgr);
	}

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();
	
	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SoundManager::GetSingleton()->Update();

	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		SoundManager::GetSingleton()->Play("Sound/Dark Waltz.mp3");
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	{
		SoundManager::GetSingleton()->Stop("Sound/Dark Waltz.mp3");
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		SoundManager::GetSingleton()->Pause("Sound/Dark Waltz.mp3");
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
	{
		SoundManager::GetSingleton()->Resume("Sound/Dark Waltz.mp3");
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
	{
		volume += 0.1f;
		SoundManager::GetSingleton()->VolumeUp("Sound/Dark Waltz.mp3", volume);
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		volume -= 0.1f;
		SoundManager::GetSingleton()->VolumeUp("Sound/Dark Waltz.mp3", volume);
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
	{
		SoundManager::GetSingleton()->Play("Sound/Missile.mp3");
	}

	if (gameMgr)
		gameMgr->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{	
	if (gameMgr)
		gameMgr->Render(backBuffer->GetMemDC());

	TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

float MainGame::GetAngle(float x1, float y1, float x2, float y2)
{
	/*
		tan (theta) = x / y;
					= (x2 - x1) / (y2 - y1);

					atan2( (y2 - y1), (x2 - x1) );
	*/

	return atan2((y2 - y1), (x2 - x1));
}

float MainGame::GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}

MainGame::MainGame()
	: isInit(false)
{
}

MainGame::~MainGame()
{
}
