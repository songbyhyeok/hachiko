#include "Missile.h"
#include "Image.h"

HRESULT Missile::Init()
{
	isFire = false;
	isHit = false;

	return S_OK;
}

void Missile::Update(bool boss)
{
	if (!boss)
	if (isFire)
	{
		pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
	}

	else
		if (isFire)
		{
			pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
			pos.y -= speed * sinf(angle2) * TimeManager::GetSingleton()->GetDeltaTime();
		}
}

void Missile::SetAngle(float _angle, float _angle2)
{
	angle = _angle;
	angle2 = _angle2;
}

void Missile::SetSpeed(float _speed)
{
	speed = _speed;
}

void Missile::SetisHit(bool _isHit)
{
	isHit = _isHit;
}

bool Missile::GetisHit()
{
	return isHit;
}

void Missile::SetisFire(bool fire)
{
	isFire = fire;
}

bool Missile::GetisFire()
{
	return isFire;
}

Missile::Missile()
{}

Missile::~Missile()
{}

HRESULT PlayerMissile::Init()
{
	Missile::Init();

	pMissile = ImageManager::GetSingleton()->AddImage("플레이어미사일", "Image/weapon/fire.bmp", 0, 0, 87, 10,
		3, 1, true, RGB(255, 0, 255));

	pMissile2 = ImageManager::GetSingleton()->AddImage("플레이어미사일2", "Image/weapon/fire2.bmp", 0, 0, 10, 87,
		1, 3, true, RGB(255, 0, 255));

	SetFrame(&playerKey, 15, 0, 0, pMissile->GetMaxKeyFrameX(), pMissile->GetMaxKeyFrameY());

	SetFrame(&playerKey2, 15, 0, 0, pMissile2->GetMaxKeyFrameX(), pMissile2->GetMaxKeyFrameY());

	angle = PI / 2.0f;
	adjustAngle = 0.0f;
	speed = 100;

	return S_OK;
}

void PlayerMissile::Release()
{
}

void PlayerMissile::Update()
{
	SetMoveFrameX(&playerKey, 16, 15);
	SetMoveFrameY(&playerKey2, 16, 15);

	Missile::Update();
}

void PlayerMissile::Render(HDC hdc, bool north, bool south, bool east, bool west)
{
	if (north && !south && !east && !west)
		pMissile2->FrameRender(hdc, pos.x, pos.y, playerKey.curFrameX, playerKey.curFrameY, false, false);

	if (south && !north && !east && !west)
		pMissile2->FrameRender(hdc, pos.x, pos.y, playerKey2.curFrameX, playerKey2.curFrameY, false, true);

	if (east && !south && !north && !west)
		pMissile->FrameRender(hdc, pos.x, pos.y, playerKey.curFrameX, playerKey.curFrameY, false, false);

	if (west && !south && !east && !north)
		pMissile->FrameRender(hdc, pos.x, pos.y, playerKey.curFrameX, playerKey.curFrameY, true, false);

}

HRESULT EnemyMissile::Init()
{
	Missile::Init();

	size = 25;
	angle = PI / 2.0f;
	adjustAngle = 0.0f;
	speed = 50;

	hBrush = CreateSolidBrush(RGB(255, 255, 0));

	return S_OK;
}

void EnemyMissile::Release()
{
	DeleteObject(hBrush);
}

void EnemyMissile::Update(bool boss1)
{
	if (!boss1)
		Missile::Update();

	else
		if (isFire)
		{
			pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
			pos.y -= speed * sinf(angle2) * TimeManager::GetSingleton()->GetDeltaTime();
		}
}

void EnemyMissile::Render(HDC hdc, bool north, bool south, bool east, bool west)
{
	SelectObject(hdc, hBrush);

	RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
}
