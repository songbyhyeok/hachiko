#include "MainGame.h"
#include "macroFunction.h"
#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Image.h"
#include "Camel.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "TilemapToolScene.h"
#include "ChangeScene.h"
#include "BattleScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"

HRESULT MainGame::Init()
{
	ImageManager::GetSingleton()->AddImage("LoadingScene", "Image/loadingImg.bmp", 0, 0, 7200, 800, 12, 1);
	ImageManager::GetSingleton()->AddImage("Ending", "Image/CLEAR.bmp", 880, 780);
	ImageManager::GetSingleton()->AddImage("GameOver", "Image/GameOver.bmp", 880, 780);
	ImageManager::GetSingleton()->AddImage("battlesceneBG", "Image/battlesceneBG.bmp", 940, 900);
	ImageManager::GetSingleton()->AddImage("battleblackBG", "Image/blackBG.bmp", 780, 780);
	ImageManager::GetSingleton()->AddImage("로드버튼2", "Image/load2.bmp", 0.0f, 0.0f, 100, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("EnemyTank2", "Image/EnemyTank2.bmp", pos.x, pos.y, 480, 60, 8, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("TankCrasheffect", "Image/bigEffect.bmp", pos.x, pos.y, 66, 35, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Enemystart", "Image/spawn.bmp", pos.x, pos.y, 160, 40, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("EnemyTank1", "Image/EnemyTank1.bmp", pos.x, pos.y, 480, 120, 8, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("EnemyTank3", "Image/EnemyTank3.bmp", pos.x, pos.y, 480, 120, 8, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("EnemyTank4", "Image/EnemyTank4.bmp", pos.x, pos.y, 480, 240, 8, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("세이브버튼", "Image/save.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("로드버튼", "Image/load.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("체인지버튼", "Image/change.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("나가기버튼", "Image/exit.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("bullet", "Image/bullet.bmp", pos.x, pos.y, 80, 20, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("bulleteffect", "Image/bulleteffect.bmp", pos.x, pos.y, 90, 30, 3, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("샘플타일", "Image/material.bmp", 0, 0,
		210, 30, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("오브젝트타일", "Image/object.bmp", 0, 0,
		360, 60, OBJECT_TILE_X, OBJECT_TILE_Y, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemynum", "Image/enemyNum1.bmp", 30, 30, true, RGB(255, 0, 255));



	hdc = GetDC(g_hWnd);

	scenenum = 0;
	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);


	titlescene = new TitleScene();
	battlescene = new BattleScene();
	loadingscene = new LoadingScene();
	gameOverScene = new GameOverScene();
	endingScene = new EndingScene();
		
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->AddScene(scene[0], titlescene);
	SceneManager::GetSingleton()->AddScene(scene[1], battlescene);
	SceneManager::GetSingleton()->AddScene(scene[2], gameOverScene);
	SceneManager::GetSingleton()->AddScene(scene[3], endingScene);
	SceneManager::GetSingleton()->AddLoadingScene("loadingscene", loadingscene);
	SceneManager::GetSingleton()->ChangeScene(scene[0], "loadingscene");
		
	tilemapToolScene = new TilemapToolScene();
	SceneManager::GetSingleton()->AddScene("타일맵툴", tilemapToolScene);

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();
	
	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;



	tilemapToolScene->Release();
	SAFE_DELETE(tilemapToolScene);

	battlescene->Release();
	SAFE_DELETE(battlescene);

	loadingscene->Release();
	SAFE_DELETE(loadingscene);

	gameOverScene->Release();
	SAFE_DELETE(gameOverScene);

	endingScene->Release();
	SAFE_DELETE(endingScene);
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	
	SceneManager::GetSingleton()->Update();

	
	
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{	
	SceneManager::GetSingleton()->Render(backBuffer->GetMemDC());

	//TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//if (isInit)
		//	this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			//tank->Fire();
			break;
		case VK_LEFT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() + (PI / 180 * 1));
			break;
		case VK_RIGHT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() - (PI / 180 * 1));
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
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

bool MainGame::CheckCollision(Missile * m1, Missile * m2)
{
	float halfSize1 = m1->GetSize() / 2;
	float halfSize2 = m2->GetSize() / 2;
	FPOINT pos1 = m1->GetPos();
	FPOINT pos2 = m2->GetPos();

	if ((halfSize1 + halfSize2) >=
		GetDistance(pos1.x, pos1.y, pos2.x, pos2.y))
	{
		return true;
	}

	return false;
}

MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
