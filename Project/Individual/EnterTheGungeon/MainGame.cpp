#include "MainGame.h"
#include "Image.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "BattleScene.h"
#include "TilemapToolScene.h"
#include "ChangeScene.h"

HRESULT MainGame::Init()
{
	backBuffer = new Image();
	backBuffer->Init(TILE_MAP_X, TILE_MAP_Y);

	titleScene = new TitleScene();
	loadingScene = new LoadingScene();
	mapTool = new TilemapToolScene();
	mapTool->Init();
	battleScene = new BattleScene();
	((BattleScene*)battleScene)->SetMapTool(((TilemapToolScene*)mapTool)); //다운 캐스팅

	TimeManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("타이틀", titleScene);
	SceneManager::GetSingleton()->AddScene("배틀", battleScene);
	SceneManager::GetSingleton()->AddScene("맵툴", mapTool);
	//SceneManager::GetSingleton()->AddLoadingScene("null", loadingScene);

	SceneManager::GetSingleton()->ChangeScene("타이틀");

	cursor = ImageManager::GetSingleton()->AddImage("조준점", "Image/UI/aiming.bmp", 50, 50, true, RGB(255, 0, 255));
	
	isInit = true;

	hdc = GetDC(g_hWnd);

	SetCursor(hCursor);

	return S_OK;
}

void MainGame::Release()
{
	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	ChangeScene::GetSingleton()->ReleaseSingleton();

	titleScene->Release();
	SAFE_DELETE(titleScene);

	loadingScene->Release();
	SAFE_DELETE(loadingScene);

	battleScene->Release();
	SAFE_DELETE(battleScene);

	mapTool->Release();
	SAFE_DELETE(mapTool);

	backBuffer->Release();
	delete backBuffer;
}

void MainGame::Update()
{
	if (isInit)
		SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{	
	SceneManager::GetSingleton()->Render(backBuffer->GetMemDC());

	cursor->Render(backBuffer->GetMemDC(), g_ptMouse.x, g_ptMouse.y);
	//camera->Render(backBuffer->GetMemDC(), 500, 300);
	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		if (isInit)
		{
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);
		}
		break;

	case WM_TIMER:
		//if (isInit)
		//	this->Update();
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

MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
