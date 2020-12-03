#include "SpaceShip.h"
#include "Image.h"


HRESULT SpaceShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("SpaceShip",
		"Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	if (image == nullptr)
	{
		return E_FAIL;
	}

	angle = 0.0f;
	moveSpeed = 200.0f;
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 120;
	rotateAngle = 0.0;

	return S_OK;
}

void SpaceShip::Release()
{
}

void SpaceShip::Update()
{
	// rotate Test
	rotateAngle += 1;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		pos.x -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		pos.x += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		pos.y -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
	}
}

void SpaceShip::Render(HDC hdc)
{
	if (image)
	{
		//image->Render(hdc, pos.x, pos.y);
		//image->AlphaRender(hdc, pos.x, pos.y, 255);
		//image->RotateRender(hdc, rotateAngle, pos.x, pos.y);
		image->RotateAlphaRender(hdc, rotateAngle, pos.x, pos.y, 180.0);
	}
}

SpaceShip::SpaceShip()
{
}


SpaceShip::~SpaceShip()
{
}
