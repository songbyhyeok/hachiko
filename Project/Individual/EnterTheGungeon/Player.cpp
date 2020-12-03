#include "Player.h"
#include "Animation.h"
#include "MissileFactory.h"
#include "Collision.h"
#include "TilemapToolScene.h"
#include "UI.h"

HRESULT Player::Init()
{
	player = ImageManager::GetSingleton()->AddImage("플레이어", "Image/Player/idle.bmp", 0, 0, 240, 480,
		4, 8, true, RGB(255, 0, 255));

	die = ImageManager::GetSingleton()->AddImage("죽음", "Image/Player/die.bmp", 0, 0, 480, 120,
		8, 2, true, RGB(255, 0, 255));

	dodge = ImageManager::GetSingleton()->AddImage("구르기", "Image/Player/dodge.bmp", 0, 0, 540, 120,
		9, 2, true, RGB(255, 0, 255));

	dodgeBack = ImageManager::GetSingleton()->AddImage("구르기백", "Image/Player/dodgeBack.bmp", 0, 0, 540, 60,
		9, 1, true, RGB(255, 0, 255));

	dodgeSide = ImageManager::GetSingleton()->AddImage("구르기옆", "Image/Player/dodgeSide.bmp", 0, 0, 540, 60,
		9, 1, true, RGB(255, 0, 255));

	weapon = ImageManager::GetSingleton()->AddImage("플레이어무기", "Image/weapon/idle.bmp", 23, 23, true, RGB(255, 0, 255));

	swipe = ImageManager::GetSingleton()->AddImage("휘두르기", "Image/weapon/swipe1.bmp", 0, 0, 150, 30, 5, 1, true, RGB(255, 0, 255));
	SetFrame(&swipeKey, 0, 0, 0, swipe->GetMaxKeyFrameX(), swipe->GetMaxKeyFrameY());

	weaponReload = ImageManager::GetSingleton()->AddImage("플레이어무기장전", "Image/weapon/reload.bmp", 0, 0, 210, 30, 7, 1, true, RGB(255, 0, 255));
	SetFrame(&reloadKey, 0, 0, 0, weaponReload->GetMaxKeyFrameX(), weaponReload->GetMaxKeyFrameY());

	weaponVfx = ImageManager::GetSingleton()->AddImage("무기이펙트", "Image/weapon/vfx.bmp", 0, 0, 84, 69, 3, 1, true, RGB(255, 0, 255));
	SetFrame(&vfxKey, 0, 0, 0, weaponVfx->GetMaxKeyFrameX(), weaponVfx->GetMaxKeyFrameY());

	weaponVfx2 = ImageManager::GetSingleton()->AddImage("무기이펙트2", "Image/weapon/vfx2.bmp", 0, 0, 69, 84, 1, 3, true, RGB(255, 0, 255));
	SetFrame(&vfxKey2, 0, 0, 0, weaponVfx2->GetMaxKeyFrameX(), weaponVfx2->GetMaxKeyFrameY());

	pos.x = 100;	pos.y = 220;

	size = 60;
	hp = 60;

	angle = 0.0f;

	idleAni = new ArrAnimation();
	idleAni->Init(player->GetWidth(), player->GetHeight(), player->GetFrameWidth(), player->GetFrameHeight());
	idleAni->SetUpdateTime(FPS / 10);
	idleAni->SetPlayFrame(idle.north, sizeof(idle.north) / sizeof(int));
	idleAni->Start();

	dieAni = new ArrAnimation();
	dieAni->Init(die->GetWidth(), die->GetHeight(), die->GetFrameWidth(), die->GetFrameHeight());
	dieAni->SetUpdateTime(FPS / 20);
	dieAni->SetPlayFrame(pDie.falldown, sizeof(pDie.falldown) / sizeof(int), false);
	dieAni->Start();

	dodgeAni = new ArrAnimation();
	dodgeAni->Init(dodge->GetWidth(), dodge->GetHeight(), dodge->GetFrameWidth(), dodge->GetFrameHeight());
	dodgeAni->SetUpdateTime(FPS / 5);
	dodgeAni->SetPlayFrame(dodgeMotion.north, sizeof(dodgeMotion.north) / sizeof(int), true);
	dodgeAni->Start();

	dodgeSideAni = new ArrAnimation();
	dodgeSideAni->Init(dodgeSide->GetWidth(), dodgeSide->GetHeight(), dodgeSide->GetFrameWidth(), dodgeSide->GetFrameHeight());
	dodgeSideAni->SetUpdateTime(FPS / 5);
	dodgeSideAni->SetPlayFrame(dodgeMotion.side, sizeof(dodgeMotion.side) / sizeof(int), true);
	dodgeSideAni->Start();

	mf = new PlayerMissileFactory();
	mf->NewMissile();
	mf->SetOwner(this);

	eyesight.x = 0;		eyesight.y = 0;

	equip = true;
	isDead = false;
	isIdle = true;
	isDodge = false;
	isStop = false;
	isDodgeSide = false;
	isReverse = false;
	reloading = false;

	SetGunpointDirection(false, false, false, false);

	tileIdX = tileIdY = 0;

	bullet = 20;

	kill = 0;

	return S_OK;
}

void Player::Release()
{
	SAFE_DELETE(idleAni);
	SAFE_DELETE(dieAni);
	SAFE_DELETE(dodgeAni);
	SAFE_DELETE(weaponAni);

	mf->Release();
	SAFE_DELETE(mf);
}

void Player::Update()
{
	// 맵 상에서의 인덱스 계산
	tileIdX = pos.x / TILE_SIZE;	tileIdY = pos.y / TILE_SIZE;

	eyesight.x = (float)g_ptMouse.x;	eyesight.y = (float)g_ptMouse.y;

	EyesightMode(eyesight);

	if (idleAni)
		idleAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (dieAni)
	{
		dieAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		if (dieAni->GetNowPlayIdx() == die->GetMaxKeyFrameX())
		{
			dieAni->SetPlayFrame(pDie.ghost, sizeof(pDie.ghost) / sizeof(int));
			dieAni->SetUpdateTime(FPS / 15);
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
	{
		isDodge = true;
		isIdle = false;
	}

	if (isDodge && !isIdle && !isDodgeSide)
	{
		dodgeAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		if (dodgeAni->GetNowPlayIdx() >= dodge->GetMaxKeyFrameX())
		{
			isDodge = false;
			isIdle = true;
			isDodgeSide = false;

			dodgeAni->SetNowPlayIdx(0);
		}
	}

	else if (isDodge && !isIdle && isDodgeSide)
	{
		dodgeSideAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		if (dodgeSideAni->GetNowPlayIdx() >= dodgeSide->GetMaxKeyFrameX())
		{
			isDodge = false;
			isIdle = true;
			isDodgeSide = true;
		}
	}

	if (weaponAni)
		weaponAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	FPOINT tempPos = pos;
	rc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

	if (!isDodge)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('A') && idleAni)
			tempPos.x -= 10;

		if (KeyManager::GetSingleton()->IsStayKeyDown('W') && idleAni)
			tempPos.y -= 10;

		if (KeyManager::GetSingleton()->IsStayKeyDown('D') && idleAni)
			tempPos.x += 10;

		if (KeyManager::GetSingleton()->IsStayKeyDown('S') && idleAni)
			tempPos.y += 10;
	}

	if (collision)
	{
		RECT tempRc;
		tempRc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

		collision->SetTempPlayerRc(&tempRc);
		collision->PlayerUpdate();

		if (!collision->GetPlayerCheck())
			pos = tempPos;

		collision->SetPlayerCheck(false);
	}

	if (mf)
	{
		if (*mf->GetMissileNum() != 0)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{

				swipeKey.curFrameX++;
				if (swipeKey.curFrameX >= swipeKey.maxFrameX)
				{
					mf->FireDelayMode(angle, 0.0f, 500);

					swipeKey.curFrameX = 0;
				}

				if (northDirection || southDirection || eastDirection || westDirection)
				{
					SetMoveFrameX(&vfxKey, 3, 2);
					SetMoveFrameY(&vfxKey2, 3, 2);

				}

			}
		}

		else
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
				reloading = true;

			if (reloading)
			{
				reloadKey.elapsedFrame++;
				if (reloadKey.elapsedFrame % 2 == 1)
				{
					reloadKey.curFrameX++;
					if (reloadKey.curFrameX >= reloadKey.maxFrameX)
					{
						reloadKey.curFrameX = 0;

						reloading = false;

						userInterface->SetReload(true);
					}
				}
			}

			if (userInterface->GetIsReady())
			{
				mf->SetMissileNum();

				userInterface->SetIsReady(false);
			}

		}

		mf->Update();

		if (userInterface)
			userInterface->Update();
	}

	if (hp <= 0)
		isDead = true;
}

void Player::Render(HDC hdc)
{
	if (player)
	{
		if (isIdle && !isDodge && !isDead)
			player->AnimationRender(hdc, pos.x, pos.y, idleAni);

		else if (!isIdle && isDodge && !isDead && !isStop)
		{
			if (!isDodgeSide)
				dodge->AnimationRender(hdc, pos.x, pos.y, dodgeAni);

			else
				dodgeSide->AnimationRender(hdc, pos.x, pos.y, dodgeSideAni, false, isReverse);
		}

		else
			die->AnimationRender(hdc, pos.x, pos.y, dieAni);

		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);
	}

	if (mf)
	{
		if (northDirection)
			mf->Render(hdc, true, false, false, false);

		if (southDirection)
			mf->Render(hdc, false, true, false, false);

		if (eastDirection)
			mf->Render(hdc, false, false, true, false);

		if (westDirection)
			mf->Render(hdc, false, false, false, true);
	}

	if (equip)
	{
		//weaponVfx->FrameRender(hdc, pos.x + 25, pos.y + 10, 0, 1);
		if (northDirection)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				swipe->FrameRender(hdc, pos.x + 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY, false, false);
				//weaponVfx2->FrameRender(hdc, pos.x, pos.y - 30, vfxKey2.curFrameX, vfxKey2.curFrameY, false, true);
			}

			else if (userInterface->GetIsReady())
				weaponReload->FrameRender(hdc, pos.x + 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY);

			else
				weapon->Render(hdc, pos.x + 25, pos.y + 10, false);
		}

		if (southDirection)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				swipe->FrameRender(hdc, pos.x - 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY, true, false);
				//weaponVfx2->FrameRender(hdc, pos.x, pos.y + 30, vfxKey2.curFrameX, vfxKey2.curFrameY, false, false);
			}

			else if (userInterface->GetIsReady())
				weaponReload->FrameRender(hdc, pos.x - 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY);

			else
				weapon->Render(hdc, pos.x - 25, pos.y + 10, true);
		}

		if (eastDirection)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				swipe->FrameRender(hdc, pos.x + 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY);
				//weaponVfx->FrameRender(hdc, pos.x + 25, pos.y + 10, vfxKey.curFrameX, vfxKey.curFrameY);
			}

			else if (userInterface->GetIsReady())
				weaponReload->FrameRender(hdc, pos.x + 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY);

			else
				weapon->Render(hdc, pos.x + 25, pos.y + 10, false);
		}

		if (westDirection)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
			{
				swipe->FrameRender(hdc, pos.x - 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY, true);
				//weaponVfx->FrameRender(hdc, pos.x - 25, pos.y + 10, vfxKey.curFrameX, vfxKey.curFrameY, true);
			}

			else if (userInterface->GetIsReady())
				weaponReload->FrameRender(hdc, pos.x - 25, pos.y + 10, swipeKey.curFrameX, swipeKey.curFrameY);

			else
				weapon->Render(hdc, pos.x - 25, pos.y + 10, true);
		}
	}

	//RenderLine(hdc, pos.x, pos.y, eyesight.x, eyesight.y);
}

void Player::EyesightMode(FPOINT _eyesight)
{
	angle = atan2(-(_eyesight.y - pos.y), _eyesight.x - pos.x);

	float tempX, tempY;
	tempX = _eyesight.x - pos.x; tempY = (_eyesight.y - pos.y);

	if (angle < 0)
		angle = 2 * PI + angle;

	// 0도 방향
	if (0 < angle && angle < PI / 180.0f * 10.0f)
	{
		idleAni->SetPlayFrame(idle.southEast, sizeof(idle.southEast) / sizeof(int));

		if (!isDodge)
		{
			isDodgeSide = true;
			isReverse = false;
		}

		SetGunpointDirection(false, false, true, false);
	}

	// 2번 방향
	else if (PI / 180.0f * 10.0f < angle && angle < PI / 180.0f * 60.0f)
	{
		idleAni->SetPlayFrame(idle.northEast, sizeof(idle.northEast) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.north, sizeof(dodgeMotion.north) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(false, false, true, false);
	}

	// 1번 방향
	else if (PI / 180.0f * 61.0f < angle && angle < PI / 180.0f * 120.0f)
	{
		idleAni->SetPlayFrame(idle.north, sizeof(idle.north) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.north, sizeof(dodgeMotion.north) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(true, false, false, false);
	}

	// 3번 방향
	else if (PI / 180.0f * 121.0f <= angle && angle < PI / 180.0f * 175.0f)
	{
		idleAni->SetPlayFrame(idle.northWest, sizeof(idle.northWest) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.north, sizeof(dodgeMotion.north) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(false, false, false, true);
	}

	// 180도 방향
	else if (PI / 180.0f * 175.0f < angle && angle < PI / 180.0f * 185.0f)
	{
		if (!isDodge)
		{
			isDodgeSide = true;
			isReverse = true;
		}

		SetGunpointDirection(false, false, false, true);
	}

	// 6번 방향
	else if (PI / 180.0f * 185.0f < angle && angle < PI / 180.0f * 240.0f)
	{
		idleAni->SetPlayFrame(idle.southWest, sizeof(idle.southWest) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.south, sizeof(dodgeMotion.south) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(false, true, false, false);
	}

	// 4번 방향
	else if (PI / 180.0f * 241.0f < angle && angle < PI / 180.0f * 270.0f)
	{
		idleAni->SetPlayFrame(idle.south, sizeof(idle.south) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.south, sizeof(dodgeMotion.south) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(false, true, false, false);
	}

	// 5번 방향
	else if (PI / 180.0f * 271.0f < angle && angle < PI / 180.0f * 350.0f)
	{
		idleAni->SetPlayFrame(idle.southEast, sizeof(idle.southEast) / sizeof(int));

		if (!isDodge)
		{
			dodgeAni->SetPlayFrame(dodgeMotion.south, sizeof(dodgeMotion.south) / sizeof(int), true);
			isDodgeSide = false;
		}

		SetGunpointDirection(false, false, true, false);
	}

	else
		float test = angle;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
	{
		float tempX = pos.x += cosf(angle) * 10;
		float tempY = pos.y += -sinf(angle) * 10;
		pos.x = tempX;	pos.y = tempY;
	}

}

RECT * Player::GetRect()
{
	return &rc;
}

PlayerMissileFactory * Player::GetMissileMf()
{
	return mf;
}

void Player::SetGunpointDirection(bool north, bool south, bool east, bool west)
{
	northDirection = north;
	southDirection = south;
	eastDirection = east;
	westDirection = west;
}

void Player::SetHp(int _hp)
{
	hp += _hp;
}

int Player::GetHp()
{
	return hp;
}

void Player::SetTileIdX(int _idX)
{
	tileIdX = _idX;
}

int Player::GetTileIdX()
{
	return tileIdX;
}

void Player::SetTileIdY(int _idY)
{
	tileIdY = _idY;
}

int Player::GetTileIdY()
{
	return tileIdY;
}

void Player::SetKill(int num)
{
	kill += num;
}

int Player::GetKill()
{
	return kill;
}

void Player::SetCollision(Collision * _collision)
{
	collision = _collision;
}

void Player::SetUI(UI * _UI)
{
	userInterface = _UI;
}

Player::Player()
{}

Player::~Player()
{}
