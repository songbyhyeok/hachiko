#include "Missile.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"
#include "pch.h"
#include "Animation.h"

HRESULT Missile::Init()
{
	
	pos.x = -500;
	pos.y = -500;
	size = 20;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	adjustAngle = 0.0f;
	isCrash = false;
	isMissileCrash = false;
	direction = PI / 2.0f;
	target = nullptr;
	effecttime = 0;

	img = ImageManager::GetSingleton()->AddImage("bullet", "Image/bullet.bmp", pos.x, pos.y, 80, 20, 4, 1, true, RGB(255, 0, 255));
	effectimg = ImageManager::GetSingleton()->AddImage("bulleteffect", "Image/bulleteffect.bmp", pos.x, pos.y, 90, 30, 3, 1, true, RGB(255, 0, 255));
	


	effectframeX = 0;

	return S_OK;
}

void Missile::Release()
{
	
}

void Missile::Update()
{
	if (isCrash)
	{
		isFire = false;
		effecttime++;
		if (effecttime % 5 == 4)
		{
			effectframeX++;
			effecttime = 0;
			if (effectframeX > 2)
			{
				isCrash = false;
				pos.x = -200;
				pos.y = -200;
			}
		}
		
		
	}

	if (isFire)
	{
		pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();

		if (pos.x > 780 || pos.y > 780 || pos.x < 0 || pos.y < 0)
		{
			isFire = false;
			pos.x = -500;
			pos.y = -500;
		}
				
	}

	if (ani)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}

	if (isMissileCrash)
	{
		pos.x = -200;
		pos.y = -200;

		isFire = false;

	}

	
}

void Missile::Render(HDC hdc)
{
	if (isFire)
	{
		if (img)
		{
							
			img->FrameRender(hdc, pos.x, pos.y, direction, 0);
			
			//img->Render(hdc, pos.x, pos.y);
			
		}

		//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
	}

	if (isCrash)
	{
		effectimg->FrameRender(hdc, pos.x, pos.y, effectframeX, 0,2);
		//effectimg->AnimationRender(hdc, pos.x, pos.y, ani);
	}

	//RenderRect(hdc, pos.x - size / 2, pos.y - size / 2, size, size);
}

Missile::Missile()
{
}


Missile::~Missile()
{
}
