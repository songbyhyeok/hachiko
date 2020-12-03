#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ChangeScene.h"

HRESULT TitleScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	SoundManager::GetSingleton()->AddSound("Dark Waltz.mp3", "Sound/Dark Waltz.mp3", true, true);

	ImageManager::GetSingleton()->AddImage("일반버튼", "Image/button.bmp", 0.0f, 0.0f, 121, 62, 1, 2, false, NULL);

	bg = ImageManager::GetSingleton()->AddImage("titleBG", "Image/Intro.bmp", 0, 0, WINSIZE_X * 2, WINSIZE_Y, 2, 1);

	POINT upFramePoint = { 0, 0 };
	POINT downFramePoint = { 0, 1 };

	changescene = new ChangeScene();
	/*button1 = new Button();
	button1->Init("일반버튼", 150, 150, downFramePoint, upFramePoint);
	args = new ARGUMENT_INFO;
	args->sceneName = "Battlescene";
	args->loadingName = "loadingscene";
	button1->SetButtonFunc(changescene, &ChangeScene::BattleButton, args);*/
	/*

		눌렀을 때, 메시지박스 출력 (프로그램을 종료하시겠습니까?)
		OK / CANCEL

	*/

	/*button2 = new Button();
	button2->Init("일반버튼", 450, 150, downFramePoint, upFramePoint);
	args1 = new ARGUMENT_INFO;
	args1->sceneName = "타일맵툴";
	args1->loadingName = "loadingscene";
	button2->SetButtonFunc(changescene, &ChangeScene::BattleButton, args1);*/

	curFrameX = 0;

	return S_OK;
}

void TitleScene::Release()
{
	/*button1->Release();
	SAFE_DELETE(button1);

	button2->Release();
	SAFE_DELETE(button2);

	SAFE_DELETE(args);
	SAFE_DELETE(args1);*/

	SAFE_DELETE(changescene);

}

void TitleScene::Update()
{
	SoundManager::GetSingleton()->Update();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN) ||
		KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		if (curFrameX == 0)
			curFrameX = 1;
		else
			curFrameX = 0;
	}

	/*if (button1)	button1->Update();
	if (button2)	button2->Update();*/

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RETURN))
	{
		if (curFrameX == 0)
			SceneManager::GetSingleton()->ChangeScene("Battlescene", "loadingscene");

		else
			SceneManager::GetSingleton()->ChangeScene("타일맵툴", "loadingscene");
	}
}

void TitleScene::Render(HDC hdc)
{
	bg->FrameRender(hdc, bg->GetFrameWidth() / 2, bg->GetHeight() / 2, curFrameX, 0);

	/*if (button1)	button1->Render(hdc);
	if (button2)	button2->Render(hdc);*/
}


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
