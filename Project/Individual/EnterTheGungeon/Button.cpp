#include "Button.h"
#include "Image.h"
#include "ChangeScene.h"

HRESULT Button::Init(const char * imageName, const char * location, float posX, float posY, POINT downPoint, POINT upPoint)
{
	state = BUTTON_STATE::NONE;
	pos.x = posX;
	pos.y = posY;
	btnUpPoint = upPoint;
	btnDownPoint = downPoint;

	img = ImageManager::GetSingleton()->AddImage(imageName, location, pos.x, pos.y, 115, 140, 1, 2, true, RGB(255, 0, 255));

	rc = GetRectToCenter(pos.x, pos.y, img->GetFrameWidth(), img->GetFrameHeight());

	changeScene = nullptr;

	return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTON_STATE::DOWN;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)
			&& state == BUTTON_STATE::DOWN)
		{
			state = BUTTON_STATE::UP;

			if (buttonFunc && !slbuttonFunc)
				(changeScene->*buttonFunc)(psl->sceneName, psl->loadingName);

			else if (!buttonFunc && slbuttonFunc)
				(changeScene->*slbuttonFunc)();
		}
	}

	else
	{
		state = BUTTON_STATE::NONE;
	}
}

void Button::Render(HDC hdc)
{
	switch (state)
	{
	case BUTTON_STATE::DOWN:
		if (img)
			img->FrameRender(hdc, pos.x, pos.y, btnDownPoint.x, btnDownPoint.y);
		break;
	case BUTTON_STATE::NONE:
	case BUTTON_STATE::UP:
		if (img)
			img->FrameRender(hdc, pos.x, pos.y, btnUpPoint.x, btnUpPoint.y);
		break;
	}
}

void Button::SetButtonFunc(ChangeScene * cS, void(ChangeScene::* bF)())
{
	changeScene = cS;
	slbuttonFunc = bF;
}

void Button::SetButtonFunc(ChangeScene * cS, void(ChangeScene::* bF)(const char *, const char *), PSL_INF _psl)
{
	changeScene = cS;
	buttonFunc = bF;
	psl = _psl;
}

Button::Button()
{
}

Button::~Button()
{
}
