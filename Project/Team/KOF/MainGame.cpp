#include "MainGame.h"
#include "Image.h"
#include "SieKensou.h"
#include "SieKensou2.h"
#include "Collision.h"

HRESULT MainGame::Init()
{
	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	KeyManager::GetSingleton()->Init();
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// BG
	bg = new Image[10];
	bg[0].Init("Image/BackGround/1.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[1].Init("Image/BackGround/2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[2].Init("Image/BackGround/3.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[3].Init("Image/BackGround/4.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[4].Init("Image/BackGround/5.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[5].Init("Image/BackGround/6.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[6].Init("Image/BackGround/7.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[7].Init("Image/BackGround/8.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[8].Init("Image/BackGround/9.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	bg[9].Init("Image/BackGround/10.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	//SieKensou
	sieKensou = new SieKensou();
	sieKensou->Init();
	sieKensou->SetPosX(200);
	sieKensou->SetPosY(300);
	sieKensou->SetTarget(sieKensou2);

	//SieKensou2
	sieKensou2 = new SieKensou2();
	sieKensou2->Init();
	sieKensou2->SetPosX(800);
	sieKensou2->SetPosY(300);
	sieKensou2->SetTarget(sieKensou);

	isInit = true;
	elapsedFrame = 0;	curFrame = 0;

	collision = new Collision();
	collision->Init();
	collision->SetPlayer(sieKensou, sieKensou2);

	return S_OK;
}

void MainGame::Release()
{
	for (int i = 0; i < 10; i++)
		bg[i].Release();
	delete[] bg;

	KillTimer(g_hWnd, 0);

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	sieKensou->Release();
	delete sieKensou;

	sieKensou2->Release();
	delete sieKensou2;

	collision->Release();
	delete collision;

	backBuffer->Release();
	delete backBuffer;
}

void MainGame::Update()
{
	if (collision)
		collision->Update();

	if (sieKensou && sieKensou2)
	{
		sieKensou->Update();
		sieKensou2->Update();
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	++elapsedFrame;

	if (bg)
	{
		bg[curFrame].Render(backBuffer->GetMemDc(), 0, 0);

		if (elapsedFrame % 20 == 19)
		{
			curFrame++;
			if (curFrame == 10)
				curFrame = 0;

			elapsedFrame = 0;
		}
	}

	if (sieKensou)
		sieKensou->Render(backBuffer->GetMemDc());

	if (sieKensou2)
		sieKensou2->Render(backBuffer->GetMemDc());

	if (collision)
		collision->Render(backBuffer->GetMemDc());

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		if (isInit)
			this->Update();

		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);

				break;
		}

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (isInit)
			this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);

		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame() : isInit(false) {}
MainGame::~MainGame() {}
