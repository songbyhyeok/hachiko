#include "EndingScene.h"
#include "Image.h"

HRESULT EndingScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	bg = ImageManager::GetSingleton()->AddImage("Ending", "Image/CLEAR.bmp", 880, 780);

	//bgs->FrameRender(hdc, bgs->GetFrameWidth() / 2, bgs->GetHeight() / 2, curFrameX, 0);
	return S_OK;
}

void EndingScene::Release()
{
}

void EndingScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("Titlescene");
	}
}

void EndingScene::Render(HDC hdc)
{
	bg->Render(hdc, pos.x - 140, 0);
}

EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{
}
