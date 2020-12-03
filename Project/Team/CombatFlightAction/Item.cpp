
#include "Item.h"
#include "Image.h"
#include <cStdlib>
#include <cTime>

HRESULT Item::Init()
{
	pos.x = -500;	pos.y = -500;

	width = 120;	height = 40;
	speed = 400.0f;

	item = ImageManager::GetSingleton()->AddImage("item", "Image/UI/Item.bmp",
		pos.x, pos.y, width, height, 3, 1, true, RGB(255, 0, 255));

	isDropA = false;
	isDropB = false;
	isDropC = false;

	isDecide = false;

	return S_OK;

}

void Item::Update()
{
	srand(time(NULL));

	if (isDropA || isDropB || isDropC)
	{
		SetHitBox(pos, width / 3, height);
		pos.x += speed * cosf(PI / 2) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(-90) * TimeManager::GetSingleton()->GetDeltaTime();
	}

	DropItem();
	Disappear();
}

void Item::Render(HDC hdc)
{
	if (isDropA)
	{
		item->FrameRender(hdc, pos.x, pos.y, (width / 3) * 1, key.curFrameY, 2.0f);
		//item->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
	}

	else if (isDropB)
	{
		item->FrameRender(hdc, pos.x, pos.y, (width / 3) * 2, key.curFrameY, 2.0f);
		//item->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
	}

	else if (isDropC)
	{
		item->FrameRender(hdc, pos.x, pos.y, (width / 3) * 3, key.curFrameY, 2.0f);
		//item->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
	}


	HitBoxRender(hdc, hitBox);
}

void Item::DropItem()
{
	int randomNum = rand() % 3;

	if (isDecide == true)
	{
		if (randomNum == 0)
			isDropA = true;

		else if (randomNum == 1)
			isDropB = true;

		else if (randomNum == 2)
			isDropC = true;
	}

	isDecide = false;
}

void Item::Disappear()
{
	if (isDropA || isDropB || isDropC)
	{
		if (TimeManager::GetSingleton()->GetDeltaTime() > 5.00f)
		{
			isDropA = false;
			isDropB = false;
			isDropC = false;
		}
	}
}
