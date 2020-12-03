#include "TitleScene.h"
#include "Image.h"
#include "Button.h"

HRESULT TitleScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	main = ImageManager::GetSingleton()->AddImage("타이틀", "Image/title.bmp", 0, 0, 6000, 900, 5, 1);

	playRect = GetRectToCenter(55, 735, 50, 30);
	mapToolRect = GetRectToCenter(75, 775, 90, 30);
	optionRect = GetRectToCenter(65, 815, 80, 35);
	exitRect = GetRectToCenter(50, 855, 40, 35);

	state = BUTTON_STATE::NONE;
	curFrameX = 0;

	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	if (PtInRect(&playRect, g_ptMouse))
		curRect = playRect;
	if (PtInRect(&mapToolRect, g_ptMouse))
		curRect = mapToolRect;
	if (PtInRect(&optionRect, g_ptMouse))
		curRect = optionRect;
	if (PtInRect(&exitRect, g_ptMouse))
		curRect = exitRect;

	LbuttonSetting(curRect);
}

void TitleScene::Render(HDC hdc)
{
	switch (state)
	{
	case BUTTON_STATE::DOWN:
		if (main)
			main->FrameRender(hdc, pos.x, pos.y, curFrameX, 1);
		break;
	case BUTTON_STATE::NONE:
	case BUTTON_STATE::UP:
		if (main)
			main->FrameRender(hdc, pos.x, pos.y, 0, 1);
		break;
	}

	sprintf_s(szText, "마우스 : [%d, %d]", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, WINSIZE_X - 135, 10, szText, strlen(szText));

	//RenderRectToCenter(hdc, 50, 855, 40, 35);
}

void TitleScene::LbuttonSetting(RECT rect)
{
	if (playRect.left == rect.left && playRect.right == rect.right)
		curFrameX = 1;
	else if (mapToolRect.left == rect.left && mapToolRect.right == rect.right)
		curFrameX = 2;
	else if (optionRect.left == rect.left && optionRect.right == rect.right)
		curFrameX = 3;
	else if (exitRect.left == rect.left && exitRect.right == rect.right)
		curFrameX = 4;

	if (PtInRect(&rect, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTON_STATE::DOWN;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && state == BUTTON_STATE::DOWN)
		{
			state = BUTTON_STATE::UP;
			
			switch (curFrameX)
			{
			case 1:
				Play();
				break;
			case 2:
				Maptool();
				break;
			case 3:
				Play();
				break;
			case 4:
				Exit();
				break;
			}
		}
	}

	else
	{
		state = BUTTON_STATE::NONE;
	}
}

void TitleScene::Play()
{
	SceneManager::GetSingleton()->ChangeScene("배틀", "로딩");
}

void TitleScene::Maptool()
{
	SceneManager::GetSingleton()->ChangeScene("맵툴", "로딩");
}

void TitleScene::Option()
{
}

void TitleScene::Exit()
{
	PostQuitMessage(0);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
