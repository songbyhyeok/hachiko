#include "GameOverScene.h"
#include "Image.h"

HRESULT GameOverScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	bg = ImageManager::GetSingleton()->AddImage("GameOver", "Image/GameOver.bmp", 880, 780);

	return S_OK;
}

void GameOverScene::Release()
{
}

void GameOverScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("Titlescene");
	}
}

void GameOverScene::Render(HDC hdc)
{
	bg->Render(hdc, pos.x - 140, 0);
}

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}
