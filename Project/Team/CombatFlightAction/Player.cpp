#include "Player.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"

HRESULT Player::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 120;

	life = 1000;
	life2 = 9999999;

	fireCount = 0;
	fireDelay = rand() % 11;

	isFire = false;
	isPowerUp = false;

	isSuffer = false;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	isHP = false;

	sufferCount = 0;
	sufferDelay = 5;

	return S_OK;
}

void Player::Update()
{

	if (missileMgr)
	{
		////패턴 1
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		rotateAngle += 30;
		//		missileMgr->SetAngle(rotateAngle);
		//		missileMgr->Fire();
		//	}

		//	rotateAngle = 0;
		//}

		//패턴 2
		/*if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			for (int i = 0; i < 100; i++)
			{
				rotateAngle += 1;
				missileMgr->SetAngle(rotateAngle);
				missileMgr->Fire();
			}

			rotateAngle = 0;
		}
		*/

		////패턴 3
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		//{
		//	for (int i = 0; i < 7; i++)
		//	{
		//		missileMgr->SetAngle(rotateAngle);
		//		missileMgr->Fire();

		//		if (rotateAngle < 180)
		//			rotateAngle += 30;
		//		else
		//			rotateAngle = 0;
		//	}

		//	rotateAngle = 0;
		//}

		//패턴 4
		//if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
		//{
		//	for (int i = 0; i < 7; i++)
		//	{
		//		missileMgr->SetAngle(rotateAngle);
		//		//missileMgr->Fire();
		//		missileMgr->SetOwner(this);

		//		if (rotateAngle < 180)
		//			rotateAngle += 30;

		//		else
		//			rotateAngle = 0;
		//	}

		//	rotateAngle = 0;
		//}

		/*missileMgr->Update();*/
	}

	if (0 + (width / key.maxFrameX) / 2 < pos.x)
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
			pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();

	if (pos.x < WINSIZE_X - (width / key.maxFrameX) / 2)
		 if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
			pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();

	if (0 + (height / key.maxFrameY) / 2 < pos.y)
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
			pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();

	if (pos.y < WINSIZE_Y - (height / key.maxFrameY) / 2)
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
			pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();

	SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
}

void Player::Render(HDC hdc)
{
	if (!isSuffer)
	{
		if (player)
			player->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY, scale);
	}

	else
	{
		if (player)
			player->AlphaRender(hdc, pos.x, pos.y, 70);

		sufferCount++;
		if (sufferDelay == sufferCount)
		{
			sufferCount = 0;

			isSuffer = false;
		}
	}

	if (missileMgr)
		missileMgr->Render(hdc);

	//HitBoxRender(hdc, hitBox);
}

void Player::SetFireDelay(int maxDelay, int minDelay)
{
	fireDelay = rand() % maxDelay + minDelay;
}

void Player::FireMode(float angle, float speed)
{
	fireCount++;
	if (fireDelay == fireCount)
	{
		fireCount = 0;
		isFire = true;
	}

	if (isFire && !isPowerUp)
		missileMgr->playerFireMode(angle, speed);

	else if (isFire && !isPowerUp)
	{
	}
}

Player::Player(){}	Player::~Player(){}

HRESULT Hyeok::Init()
{
	Player::Init();

	width = 101;	height = 90;

	player = ImageManager::GetSingleton()->AddImage("Hyeok", "Image/Hyeok/BODY.bmp",
		pos.x, pos.y, width, height, 1, 1, true, RGB(255, 0, 255));

	if (player == nullptr)
		return E_FAIL;

	scale = 1.0f;
	angle = 90.0f;	rotateAngle = 0.0f;
	speed = 200.0f;

	Image * baseImg = ImageManager::GetSingleton()->AddImage("playerBasicWeapon", "Image/Hyeok/BasicWeapon.bmp",
		pos.x, pos.y, 40, 280, 1, 7, true, RGB(255, 0, 255));

	
	missileMgr->SetMissileInf(baseImg, 40, 280, 1, 7);

	SetFrame(0, 0, 0, 1, 1);

	return S_OK;
}

void Hyeok::Release(){}

void Hyeok::Update()
{
	Player::Update();
	//SetMaxFrameDetermine(10, 9);

	if (missileMgr)
	{
		for (auto & it : missileMgr->GetMissile())
			it->SetMaxFrameDetermine(10, 9);

		if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
			FireMode(90, 500);

		missileMgr->Update(2, 1);
		isFire = false;
	}
}

void Hyeok::Render(HDC hdc)
{
	Player::Render(hdc);
	if (missileMgr)
		missileMgr->Render(hdc);
}

Hyeok::Hyeok(){}

Hyeok::~Hyeok(){}

HRESULT Dongkyune::Init()
{
	Player::Init();

	width = 38;
	height = 70;

	player = ImageManager::GetSingleton()->AddImage("Dongkyune", "Image/Dongkyune/TureMissile.bmp",
		pos.x, pos.y, width, height, 1, 1, true, RGB(248, 0, 248));

	if (player == nullptr)
		return E_FAIL;

	scale = 1.0f;
	angle = 0.0f;
	rotateAngle = 0.0f;
	speed = 200.0f;

	SetFrame(0, 0, 0, 1, 1);

	//////////////
	Image * missile2 = ImageManager::GetSingleton()->AddImage("missile4", "Image/missile2.bmp",
		pos.x, pos.y, 18, 37, 1, 1, true, RGB(255, 0, 255));

	missileMgr->SetMissileInf(missile2, 18, 37, 1, 1);

	
	return S_OK;
}

void Dongkyune::Release(){}

void Dongkyune::Update()
{
	Player::Update();
	//SetMaxFrameDetermine(10, 9);

	if (missileMgr)
	{
		for (auto & it : missileMgr->GetMissile())
			it->SetMaxFrameDetermine(1, 1);

		if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
			FireMode(90, 500);

		missileMgr->Update(2, 1);
		isFire = false;
	}

}

void Dongkyune::Render(HDC hdc)
{
	Player::Render(hdc);
	if (missileMgr)
		missileMgr->Render(hdc);
}

Dongkyune::Dongkyune(){}	Dongkyune::~Dongkyune(){}

HRESULT Junhyeok::Init()
{
	Player::Init();

	width = 100;	height = 100;

	player = ImageManager::GetSingleton()->AddImage("JunHyeok", "Image/Junhyeok/CH0.bmp",
		pos.x, pos.y, width, height, 1, 1, true, RGB(255, 0, 255));

	if (player == nullptr)
		return E_FAIL;

	scale = 1.0f;
	angle = 0.0f;	rotateAngle = 0.0f;
	speed = 200.0f;

	SetFrame(0, 0, 0, 1, 1);

	Image * basic = ImageManager::GetSingleton()->AddImage("missile", "Image/missile.bmp",
		pos.x, pos.y, 13, 33, 1, 1, true, RGB(255, 0, 255));

	missileMgr->SetMissileInf(basic, 13, 33, 1, 1);

	SetFrame(0, 0, 0, 1, 1);

	return S_OK;
}

void Junhyeok::Release(){}

void Junhyeok::Update()
{
	Player::Update();
	//SetMoveFrameY(10, 9);

	if (missileMgr)
	{
		for (auto & it : missileMgr->GetMissile())
			it->SetMaxFrameDetermine(1, 1);

		if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
			FireMode(90, 500);

		missileMgr->Update(2, 1);
		isFire = false;
	}
}

void Junhyeok::Render(HDC hdc)
{
	Player::Render(hdc);
	if (missileMgr)
		missileMgr->Render(hdc);
}

Junhyeok::Junhyeok(){}	Junhyeok::~Junhyeok(){}
