#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"
#include "MissileManager.h"
#include "Player.h"
#include "Missile.h"

HRESULT Enemy::Init()
{
	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	rotateAngle = 0;

	fireDelay = rand() % 100;
	fireCount = 0;

	bullet = 200;

	isDead = false;
	isCurBool = false;

	isCrashP = false;
	isCrashM = false;

	isLeft = false;
	isRight = false;

	return S_OK;
}

void Enemy::DisappearMode()
{
	isCrashP = false;
	isCrashM = false;

	pos.x = 9999;		pos.y = 9999;
}

void Enemy::SetIsTarget(Player * _isTarget)
{
	isTarget = _isTarget;
}

//image->Render(hdc, pos.x, pos.y);
//image->AlphaRender(hdc, pos.x, pos.y, 255);
//image->RotateRender(hdc, rotateAngle, pos.x, pos.y);
//image->RotateAlphaRender(hdc, rotateAngle, pos.x, pos.y, 180.0);

Enemy::Enemy(){}	Enemy::~Enemy(){}

HRESULT BombMan::Init(float posX, float posY)
{
	Enemy::Init();


	pos.x = posX;	pos.y = posY;

	SetFrame(0, 0, 0, 1, 1);
	width = 30;		height = 60;
	
	isEnemy = ImageManager::GetSingleton()->AddImage("BombMan", "Image/ENEMY/BombMan.bmp",
	pos.x, pos.y, width, height, 1, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void BombMan::Release()
{
	
}

void BombMan::Update()
{
	if (!isCrashP && !isCrashM)
	{
		Suicide();
		Motion();

		SetHitBox(pos, width, height);
		SetMoveFrameY(2, 1);
	}

	else
		DisappearMode();
}

void BombMan::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRotateAlphaRender(hdc, rotateAngle, pos.x, pos.y, key.curFrameX, key.curFrameY);

		if (missileMgr)
			missileMgr->Render(hdc);
	}
}

void BombMan::Suicide()
{
	if (isTarget)
	{
		float x = isTarget->GetPos().x - pos.x;
		float y = isTarget->GetPos().y - pos.y;
		angle = atan2(-y, x);
	}
}

void BombMan::Motion()
{
	if (rotateAngle < 180)
	{
		rotateAngle += 10;
		pos.x += cosf(rotateAngle) * speed;
		pos.y -= sinf(rotateAngle) * speed;
	}

	else
	{
		pos.x += cosf(angle) * speed;
		pos.y -= sinf(angle) * speed;

		speed = 10.0f;
	}
}

BombMan::BombMan(){}	BombMan::~BombMan(){}

HRESULT Comet::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	speed = 10.0f;

	SetFrame(0, 0, 0, 1, 5);
	width = 40;		height = 200;

	isEnemy = ImageManager::GetSingleton()->AddImage("Comet", "Image/ENEMY/Comet.bmp",
		pos.x, pos.y, width, height, 1, 5, true, RGB(255, 0, 255));

	if (pos.x <= 600 && pos.y == 0)
	{
		location = 0;
	}

	else if (pos.x == 0 && pos.y <= 200)
	{
		location = 1;
	}

	else if (pos.x == 600 && pos.y <= 200)
	{
		location = 2;
	}

	return S_OK;
}

void Comet::Release()
{
	/*missileMgr->Release();
	SAFE_DELETE(missileMgr);*/
}

void Comet::Update()
{
	if (!isCrashP && !isCrashM)
	{
		if (location == 0)
		{
			angle = -90;
			pos.y -= sinf(angle) * speed;
		}

		else if (location == 1)
		{
			pos.x += cosf(PI * 2) * speed;
			pos.y -= sinf(-(PI / 2)) * speed;
		}

		else
		{
			pos.x += cosf(PI) * speed;
			pos.y -= sinf(-(PI / 2)) * speed;
		}

		SetHitBox(pos, width, height / 5);
		SetMoveFrameY(2, 1);
	}

	else
		DisappearMode();
}

void Comet::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		if (missileMgr)
			missileMgr->Render(hdc);
	}
}

Comet::Comet(){}	Comet::~Comet(){}

HRESULT JellyFish::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	angle = PI;
	speed = 200.0f;

	SetFrame(0, 0, 0, 1, 5);
	width = 25;		height = 150;
	
	isEnemy = ImageManager::GetSingleton()->AddImage("JellyFish", "Image/ENEMY/JellyFish.bmp",
	pos.x, pos.y, width, height, 1, 5, true, RGB(255, 0, 255));

	Image * curImg = ImageManager::GetSingleton()->AddImage("enemyBullet1", "Image/MISSILE/bullet.bmp",
		pos.x, pos.y, 10, 10, 1, 1, true, RGB(255, 0, 255));

	/*missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);*/

	missileMgr->SetMissileInf(curImg,21,21,1,1);

	return S_OK;
}

void JellyFish::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void JellyFish::Update()
{

	if (!isCrashP && !isCrashM)
	{
		pos.x -= cosf(angle) * speed * TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width, height / 5);
		SetMoveFrameY(2, 1);

		

	}

	else
		DisappearMode();

	if (missileMgr)
	{
		//if (isFire)
		{
			for (auto & it : missileMgr->GetMissile())
				it->SetMaxFrameDetermine(2, 1);

			missileMgr->SetFireDelay(10, 5);
			missileMgr->FireMode(0, 270, 200.0f);
		}
	}
	missileMgr->Update(10, 5);
}

void JellyFish::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		/*HitBoxRender(hdc, hitBox);*/
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		

		/*if (isFire)
			fireMode->FrameRender(hdc, pos.x, pos.y + 75, key2.curFrameX, key2.curFrameY);*/
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

JellyFish::JellyFish(){}	JellyFish::~JellyFish(){}

HRESULT UFO::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	angle = PI / 2;	angle1 = PI / 3;
	speed = 200.0f;

	SetFrame(0, 0, 0, 10, 1);
	width = 530;		height = 32;

	isEnemy = ImageManager::GetSingleton()->AddImage("UFO", "Image/ENEMY/UFO.bmp",
	pos.x, pos.y, width, height, 10, 1, true, RGB(255, 0, 255));

	Image * ufoImg = ImageManager::GetSingleton()->AddImage("UfoMissile", "Image/MISSILE/UfoMissile.bmp",
		pos.x, pos.y, 110, 14, 8, 1, true, RGB(255, 0, 255));

	/*missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);*/
	//missileMgr->SetMissileInf(curImg);
	missileMgr->SetMissileInf(ufoImg, 110, 14, 8, 1);

	return S_OK;
}

void UFO::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void UFO::Update()
{
	if (!isCrashP && !isCrashM)
	{
		pos.x -= cosf(angle1) * speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y += sinf(angle) * speed* TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width / 10, height);
		SetMoveFrameX(2, 1);
		
		
	}

	else
		DisappearMode();

	if (missileMgr)
	{
		//if (isFire)
		{
			for (auto & it : missileMgr->GetMissile())
				it->SetMaxFrameDetermine(2, 1);

			missileMgr->SetFireDelay(10, 10);
			missileMgr->FireMode(60, 0, 200.0f);
			//rotateAngle =+200;
		}
	}
	missileMgr->Update(10, 5);
}

void UFO::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

UFO::UFO(){}	UFO::~UFO(){}

HRESULT UFOEnemy::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	angle = PI / 2;	angle1 = PI / 3;
	speed = 200.0f;

	SetFrame(0, 0, 0, 1, 5);
	width = 50;		height = 300;

	isEnemy = ImageManager::GetSingleton()->AddImage("UFOEnemy", "Image/ENEMY/UFOEnemy.bmp",
	pos.x, pos.y, width, height, 1, 5, true, RGB(255, 0, 255));

	Image * ufoImg = ImageManager::GetSingleton()->AddImage("UfoMissile", "Image/MISSILE/UfoMissile.bmp",
		pos.x, pos.y, 110, 14, 8, 1, true, RGB(255, 0, 255));

	/*missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);*/
	//missileMgr->SetMissileInf(curImg);
	missileMgr->SetMissileInf(ufoImg, 110, 14, 8, 1);


	return S_OK;
}

void UFOEnemy::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void UFOEnemy::Update()
{
	if (!isCrashP && !isCrashM)
	{
		pos.x += cosf(angle1) * speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y += sinf(angle) * speed* TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width, height / 5);
		SetMoveFrameY(10, 9);
		
		
	}

	else
		DisappearMode();

	if (missileMgr)
	{
		//if (isFire)
		{
			for (auto & it : missileMgr->GetMissile())
				it->SetMaxFrameDetermine(2, 1);

			missileMgr->SetFireDelay(10, 10);
			missileMgr->FireMode(90, 270, 200.0f);
		}
	}
	missileMgr->Update(10, 5);
}

void UFOEnemy::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

UFOEnemy::UFOEnemy(){}	UFOEnemy::~UFOEnemy(){}

HRESULT CuteEye::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	angle = PI;
	speed = 200.0f;

	isFire = false;

	SetFrame(0, 0, 0, 1, 1);
	width = 40;		height = 35;

	isEnemy = ImageManager::GetSingleton()->AddImage("CuteEye", "Image/ENEMY/CuteEye.bmp",
		pos.x, pos.y, width, height, 1, 1, true, RGB(255, 0, 255));

	Image * cutImg = ImageManager::GetSingleton()->AddImage("EyeMissile1", "Image/MISSILE/Missile2.bmp",
		pos.x, pos.y, 19, 19, 1, 1, true, RGB(255, 0, 255));

	/*missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);*/
	missileMgr->SetMissileInf(cutImg, 19, 19, 1, 1);
	

	return S_OK;
}

void CuteEye::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void CuteEye::Update()
{
	if (!isCrashP && !isCrashM)
	{
		pos.x += cosf(angle) * speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y += sinf(PI / 2) * speed* TimeManager::GetSingleton()->GetDeltaTime();
		
		SetHitBox(pos, width, height);
		SetMoveFrameY(10, 9);

		
		
	}
	else
		DisappearMode();

	if (missileMgr)
	{
		for (auto & it : missileMgr->GetMissile())
			it->SetMaxFrameDetermine(2, 1);

		missileMgr->SetFireDelay(10, 10);
		missileMgr->FireMode(90, 270, 200.0f);
		
	}

	missileMgr->Update(10, 5);

}

void CuteEye::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

CuteEye::CuteEye(){}	CuteEye::~CuteEye(){}

HRESULT ShyEye::Init(float posX, float posY)
{
	Enemy::Init();

	pos.x = posX;	pos.y = posY;

	angle = PI;
	speed = 200.0f;

	isFire = false;

	SetFrame(0, 0, 0, 1, 5);
	width = 50;		height = 300;

	isEnemy = ImageManager::GetSingleton()->AddImage("ShyEye", "Image/ENEMY/ShyEye.bmp",
		pos.x, pos.y, width, height, 1, 5, true, RGB(255, 0, 255));

	Image * cutImg = ImageManager::GetSingleton()->AddImage("EyeMissile1", "Image/MISSILE/Missile2.bmp",
		pos.x, pos.y, 19, 19, 1, 1, true, RGB(255, 0, 255));

	
	missileMgr->SetMissileInf(cutImg, 19, 19, 1, 1);
	//missileMgr->SetMissileInf(curImg);

	return S_OK;
}

void ShyEye::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void ShyEye::Update()
{
	if (!isCrashP && !isCrashM)
	{
		pos.x += cosf(PI / 3) * speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y += sinf(PI / 2) * speed* TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width, height);
		SetMoveFrameY(10, 9);


		
		
	}

	else
		DisappearMode();

	if (missileMgr)
	{
		//if (isFire)
		{
			for (auto & it : missileMgr->GetMissile())
				it->SetMaxFrameDetermine(2, 1);

			missileMgr->SetFireDelay(10, 1);
			missileMgr->FireMode(90, 215, 200.0f);
		}
	}
	missileMgr->Update(10, 5);
}

void ShyEye::Render(HDC hdc)
{
	if (!isCrashP && !isCrashM)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

ShyEye::ShyEye(){}	ShyEye::~ShyEye(){}

HRESULT GiantBalloon::Init(float posX, float posY)
{
	Enemy::Init();

	GiantBalloonHP = 5000;
	isGiantBalloonHit = false;

	pos.x = posX;	pos.y = posY;

	angle = PI / 2;	angle1 = PI / 3;
	speed = 200.0f;

	SetFrame(0, 0, 0, 6, 1);	SetFrame2(0, 0, 0, 1, 3);
	width = 1020;		height = 140;

	isBossIm = true;
	isFire = true;

	isEnemy = ImageManager::GetSingleton()->AddImage("Boss1", "Image/ENEMY/Boss1/GiantBalloon.bmp",
		pos.x, pos.y, width, height, 6, 1, true, RGB(255, 0, 255));

	fireMode = ImageManager::GetSingleton()->AddImage("Boss1Ready", "Image/ENEMY/Boss1/BossMissile.bmp",
		pos.x, pos.y, 140, 180, 1, 3, true, RGB(255, 0, 255));

	Image * baseImg = ImageManager::GetSingleton()->AddImage("BossBasicWeapon", "Image/ENEMY/Boss1/baseWeapon.bmp",
		pos.x, pos.y, 600, 200, 6, 1, true, RGB(255, 0, 255));

	Image * norImg = ImageManager::GetSingleton()->AddImage("BossNormalWeapon", "Image/ENEMY/Boss1/norWeapon.bmp",
		pos.x, pos.y, 720, 75, 12, 1, true, RGB(255, 0, 255));


	missileMgr->SetMissileInf(baseImg, 600, 200, 6, 1);
	missileMgr->SetNorMissileInf(norImg, 720, 75, 12, 1);

	return S_OK;
}

void GiantBalloon::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);
}

void GiantBalloon::Update()
{
	//if (!isCurBool && !isGiantBalloonHit)
	{
		SetHitBox(pos, width / key.maxFrameX, height);

		SetMaxFrameDetermine(10, 9);
		SetMaxFrameDetermine2(10, 9);

		MovementControl();

		if (missileMgr)
		{
			if (isFire)
			{
			
				for (auto & it : missileMgr->GetMissile())
					it->SetMaxFrameDetermine(2, 1);
					
				missileMgr->SetFireDelay(50, 0);
				missileMgr->FireMode(-90, -90, 500, 0, 50);
				missileMgr->Update(2, 1);
				
			}

		}
	}

	if (isCurBool && !isGiantBalloonHit)
	{
		GiantBalloonHP -= 10;
		isCurBool = false;

		if (GiantBalloonHP <= 0)
		{
			isGiantBalloonHit = true;
			isDead = true;
		}
	}
}

void GiantBalloon::Render(HDC hdc)
{
	//if (!isCurBool && !isGiantBalloonHit)
	{
		//HitBoxRender(hdc, hitBox);
		isEnemy->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);

		if (isFire)
			fireMode->FrameRender(hdc, pos.x, pos.y + 75, key2.curFrameX, key2.curFrameY);

		if (missileMgr)
			missileMgr->Render(hdc);
	}
}

void GiantBalloon::MoveLeft()
{
	pos.x -= 5;
}

void GiantBalloon::MoveRight()
{
	pos.x += 5;
}

void GiantBalloon::IsAttack()
{

}

void GiantBalloon::MovementControl()
{
	if (85 < pos.x && !isLeft)
	{
		MoveLeft();
		//isFire = false;

		if (pos.x == 85)
		{
			isLeft = true;
			isRight = false;
			pos.x = 90;
		}
	}

	else if (pos.x > 85 && !isRight)
	{
		MoveRight();
		//isFire = true;

		if (pos.x == WINSIZE_X - 85)
		{
			isRight = true;
			isLeft = false;
			pos.x = 590 - 85;
		}
	}
	
}

GiantBalloon::GiantBalloon(){}	GiantBalloon::~GiantBalloon(){}
