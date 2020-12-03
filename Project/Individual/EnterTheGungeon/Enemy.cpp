#include "Enemy.h"
#include "TilemapToolScene.h"
#include "Collision.h"
#include "Animation.h"
#include "MissileFactory.h"
#include "BattleScene.h"
#include "Animation.h"

HRESULT Enemy::Init(float x, float y)
{
	pos.x = x;	pos.y = y;

	tileIdX = tileIdY = 0;

	size = 60;

	hp = 10;

	isDetect = false;
	doAttack = false;
	moving = false;
	isHit = false;
	isDead = false;
	getId = false;
	isFire = false;
	collisionCheck = false;

	spawn = false;

	tempId = 0;

	xSmall = false;	xBig = false;
	ySmall = false;	yBig = false;

	mf = new EnemyMissileFactory();
	mf->Init();
	mf->SetOwner(this);

	regenTime = 50;
	regenCount = 0;

	return S_OK;
}

void Enemy::Release()
{
	mf->Release();
	SAFE_DELETE(mf);
}

void Enemy::Update()
{
	tileIdX = pos.x / TILE_SIZE;	tileIdY = pos.y / TILE_SIZE;

	FPOINT tempPos = pos;
	rc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

	if (spawn)
	{
		moving = false; 
		isDetect = false; 
		doAttack = false;

		mf->FireInit();
	}

	else if (!isDead && !spawn)
	{
		MoveMode(&tempPos);

		if (moving)
			LocateMode();

		else
			AttackMode();

		if (mf)
		{
			if (doAttack)
				mf->FireDelayMode(angle, 0.0f, 150);

			mf->Update();
		}

		if (collision)
		{
			RECT tempRc;
			tempRc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

			collision->SetTempEnemyRc(&tempRc);
			collision->EnemyUpdate();

			if (!collision->GetEnemyCheck())
				pos = tempPos;

			else
			{
				getId = false;
				moving = true;
				isDetect = false;
				doAttack = false;
			}

			collision->SetEnemyCheck(false);
		}

		if (hp <= 0)
			isDead = true;
	}

	else
	{
		regenCount++;
		if (regenCount % regenTime == regenTime - 1)
		{
			regenCount = 0;

			int x = rand() % 590 + 270; int y = rand() % 350 + 300;

			pos.x = x;	pos.y = y;

			isDead = false;
			spawn = true;

			hp = 10;
		}
	}
}

void Enemy::MoveMode(FPOINT *tempPos)
{
	if (!moving && !isDetect && !doAttack && tileIdY > 0 && tileIdX > 0)
	{
		moveVec.clear();

		// 적 이동범위를 만드는 코드
		for (int i = tileIdY - 1; i < tileIdY + 2; i++)
		{
			for (int j = tileIdX - 1; j < tileIdX + 2; j++)
				moveVec.push_back(&mapTool->GetTileInf()[i * MAIN_TILE_X + j].rcTile);
		}

		if (!isDetect)
			moving = true;
	}

	//경계모드 + 이동모드
	else if (moving && !isDetect && !doAttack)
	{
		moveDelay = rand() % 100;

		if (!getId)
		{
			tempId = rand() % moveVec.size();

			countMove++;
			if (moveDelay <= countMove)
			{
				countMove = 0;
				getId = true;

				if (tempPos->x < moveVec[tempId]->left + TILE_SIZE / 2)
					xSmall = true;

				else if (tempPos->x > moveVec[tempId]->left + TILE_SIZE / 2)
					xBig = true;

				if (tempPos->y < moveVec[tempId]->top + TILE_SIZE / 2)
					ySmall = true;

				else if (tempPos->y > moveVec[tempId]->top + TILE_SIZE / 2)
					yBig = true;
			}
		}

		if (getId)
		{
			if (tempPos->x < moveVec[tempId]->left + TILE_SIZE / 2 && xSmall)
			{
				tempPos->x += 5;

				if (tempPos->x >= moveVec[tempId]->left + TILE_SIZE / 2 && xSmall)
					xSmall = false;
			}

			else if (tempPos->x > moveVec[tempId]->left + TILE_SIZE / 2 && xBig)
			{
				tempPos->x -= 5;

				if (tempPos->x <= moveVec[tempId]->left + TILE_SIZE / 2 && xBig)
					xBig = false;
			}

			if (tempPos->y < moveVec[tempId]->top + TILE_SIZE / 2 && ySmall)
			{
				tempPos->y += 5;

				if (tempPos->y >= moveVec[tempId]->top + TILE_SIZE / 2 && ySmall)
					ySmall = false;
			}

			else if (tempPos->y > moveVec[tempId]->top + TILE_SIZE / 2 && yBig)
			{
				tempPos->y -= 5;

				if (tempPos->y <= moveVec[tempId]->top + TILE_SIZE / 2 && yBig)
					yBig = false;
			}


			if (!xSmall && !xBig && !ySmall && !yBig)
			{
				getId = false;
			}
		}
	}

	//플레이어 따라가는 코드
	else if (!moving && isDetect && !doAttack)
	{
		if (tempPos->x <= tempRc->left + TILE_SIZE / 2)
		{
			if (tempPos->x <= (tempPos->x + 60))
			{
				tempPos->x += 1;

				if (tempPos->y <= tempRc->top + TILE_SIZE / 2)
				{
					if (tempPos->y <= (tempPos->y + 60))
						tempPos->y += 1;
				}

				else if (tempPos->y >= tempRc->top + TILE_SIZE / 2)
				{
					if (tempPos->y >= (tempPos->y - 60))
						tempPos->y -= 1;
				}
			}
		}

		else if (tempPos->x >= tempRc->left + TILE_SIZE / 2)
		{
			if (tempPos->x >= (tempPos->x - 60))
			{
				tempPos->x -= 1;

				if (tempPos->y >= tempRc->top + TILE_SIZE / 2)
				{
					if (tempPos->y >= (tempPos->y - 60))
						tempPos->y -= 1;
				}

				else if (tempPos->y <= tempRc->top + TILE_SIZE / 2)
				{
					if (tempPos->y <= (tempPos->y + 60))
						tempPos->y += 1;
				}
			}
		}
	}
}

void Enemy::LocateMode()
{
	locateVec.clear();

	for (int i = tileIdY - 3; i < tileIdY + 4; i++)
	{
		for (int j = tileIdX - 3; j < tileIdX + 4; j++)
		{

			locateVec.push_back(&mapTool->GetTileInf()[i * MAIN_TILE_X + j].rcTile);
		}
	}
}

void Enemy::AttackMode()
{
	attackVec.clear();

	for (int i = tileIdY - 2; i < tileIdY + 3; i++)
	{
		for (int j = tileIdX - 2; j < tileIdX + 3; j++)
		{

			attackVec.push_back(&mapTool->GetTileInf()[i * MAIN_TILE_X + j].rcTile);
		}
	}

	if (!moving && !isDetect && doAttack)
	{
		float tempFloatX = (float)(tempRc->left + TILE_SIZE / 2);
		float tempFloatY = (float)(tempRc->top + TILE_SIZE / 2);

		isFire = true;
		angle = atan2(-(tempFloatY - pos.y), tempFloatX - pos.x);
	}

}

RECT* Enemy::GetRect()
{
	return &rc;
}

void Enemy::SetHp(int _hp)
{
	hp += _hp;
}

int Enemy::GetHp()
{
	return hp;
}

void Enemy::SetMoving(bool _moving)
{
	moving = _moving;
}

bool Enemy::GetMoving()
{
	return moving;
}

void Enemy::SetDetect(bool _isDetect)
{
	isDetect = _isDetect;
}

bool Enemy::GetDetect()
{
	return isDetect;
}

void Enemy::SetDoAttack(bool _doAttack)
{
	doAttack = _doAttack;
}

bool Enemy::GetDoAttack()
{
	return doAttack;
}

void Enemy::SetIsHit(bool _isHit)
{
	isHit = _isHit;
}

bool Enemy::GetIsHit()
{
	return isHit;
}

void Enemy::SetIsDead(bool _isDead)
{
	isDead = _isDead;
}

bool Enemy::GetIsDead()
{
	return isDead;
}

bool Enemy::GetSpawn()
{
	return spawn;
}

void Enemy::BringPlayerRectPos(RECT * playerRc)
{
	tempRc = playerRc;
}

void Enemy::SetTileIdX(int _idX)
{
	tileIdX = _idX;
}

int Enemy::GetTileIdX()
{
	return tileIdX;
}

void Enemy::SetTileIdY(int _idY)
{
	tileIdY = _idY;
}

int Enemy::GetTileIdY()
{
	return tileIdY;
}

void Enemy::SetCollisionCheck(bool _check)
{
	collisionCheck = _check;
}

bool Enemy::GetCollisionCheck()
{
	return collisionCheck;
}

vector<RECT*> Enemy::GetMoveVec()
{
	return moveVec;
}

vector<RECT*> Enemy::GetLocateVec()
{
	return locateVec;
}

vector<RECT*> Enemy::GetAttackVec()
{
	return attackVec;
}

EnemyMissileFactory * Enemy::GetMissileMf()
{
	return mf;
}

void Enemy::SetCollision(Collision * _collision)
{
	collision = _collision;
}

void Enemy::SetMapTool(TilemapToolScene * _mapTool)
{
	mapTool = _mapTool;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy1::Init(float x, float y)
{
	Enemy::Init(x, y);

	mushroom = ImageManager::GetSingleton()->AddImage("적1", "Image/enemy/mushroom.bmp", 0, 0, 540, 360,
		9, 6, true, RGB(255, 0, 255));

	mushroomMotion = new MUSHROOM();

	mushroomAni = new ArrAnimation();
	mushroomAni->Init(mushroom->GetWidth(), mushroom->GetHeight(), mushroom->GetFrameWidth(), mushroom->GetFrameHeight());
	mushroomAni->SetUpdateTime(FPS / 10);
	mushroomAni->SetPlayFrame(mushroomMotion->spawn, sizeof(mushroomMotion->spawn) / sizeof(int));
	mushroomAni->Start();

	return S_OK;
}

void Enemy1::Release()
{
	Enemy::Release();

	SAFE_DELETE(mushroomMotion);
	SAFE_DELETE(mushroomAni);
}

void Enemy1::Update()
{
	Enemy::Update();

	mushroomAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (spawn)
	{
		mushroomAni->SetUpdateTime(FPS / 25);
		mushroomAni->SetPlayFrame(mushroomMotion->spawn, sizeof(mushroomMotion->spawn) / sizeof(int));

		if (mushroomAni->GetNowPlayIdx() >= 8)
			spawn = false;
	}

	if (!isDead)
	{
		mushroomAni->SetUpdateTime(FPS / 10);

		//경계
		if (moving && !isDetect && !doAttack)
			mushroomAni->SetPlayFrame(mushroomMotion->idle, sizeof(mushroomMotion->idle) / sizeof(int));

		//이동
		if (!moving && isDetect && !doAttack)
			mushroomAni->SetPlayFrame(mushroomMotion->move, sizeof(mushroomMotion->move) / sizeof(int));

		//공격
		if (!moving && !isDetect && doAttack)
			mushroomAni->SetPlayFrame(mushroomMotion->attack, sizeof(mushroomMotion->attack) / sizeof(int));
	}
	
}

void Enemy1::Render(HDC hdc)
{
	if (!isDead)
	{
		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);

		mushroom->AnimationRender(hdc, pos.x, pos.y, mushroomAni, false, true);

		if (mf && isFire)
			mf->Render(hdc, false, false, false, false);

		HPEN myPen, oldPen;

		myPen = CreatePen(PS_DASHDOTDOT, 1, RGB(125, 125, 0));
		oldPen = (HPEN)SelectObject(hdc, myPen);

		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		/*for (int i = 0; i < moveVec.size(); i++)
			RenderRect(hdc, moveVec[i]->left, moveVec[i]->top, TILE_SIZE);*/

		/*if (moving)
		{
			for (int i = 0; i < locateVec.size(); i++)
				RenderRect(hdc, locateVec[i]->left, locateVec[i]->top, TILE_SIZE);
		}*/

		//else
		{
			for (int i = 0; i < attackVec.size(); i++)
				RenderRect(hdc, attackVec[i]->left, attackVec[i]->top, TILE_SIZE);
		}

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(myPen);
		DeleteObject(myBrush);
	}
}

HRESULT Enemy2::Init(float x, float y)
{
	Enemy::Init(x, y);

	enemy2 = ImageManager::GetSingleton()->AddImage("적2", "Image/enemy/bird.bmp", 0, 0, 240, 180,
		4, 3, true, RGB(255, 0, 255));

	enemy2Motion = new ENEMY2();

	enemy2Ani = new ArrAnimation();
	enemy2Ani->Init(enemy2->GetWidth(), enemy2->GetHeight(), enemy2->GetFrameWidth(), enemy2->GetFrameHeight());
	enemy2Ani->SetUpdateTime(FPS / 10);
	enemy2Ani->SetPlayFrame(enemy2Motion->idle, sizeof(enemy2Motion->idle) / sizeof(int));
	enemy2Ani->Start();

	return S_OK;
}

void Enemy2::Release()
{
	Enemy::Release();

	SAFE_DELETE(enemy2Motion);
	SAFE_DELETE(enemy2Ani);
}

void Enemy2::Update()
{
	Enemy::Update();

	enemy2Ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (spawn)
	{
		spawn = false;
	}

	if (!isDead)
	{
		enemy2Ani->SetUpdateTime(FPS / 10);

		//경계
		if (moving && !isDetect && !doAttack)
			enemy2Ani->SetPlayFrame(enemy2Motion->idle, sizeof(enemy2Motion->idle) / sizeof(int));

		//공격
		if (!moving && !isDetect && doAttack)
			enemy2Ani->SetPlayFrame(enemy2Motion->attack, sizeof(enemy2Motion->attack) / sizeof(int));
	}
}

void Enemy2::Render(HDC hdc)
{
	if (!isDead)
	{
		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);

		enemy2->AnimationRender(hdc, pos.x, pos.y, enemy2Ani, false, false);

		if (mf && isFire)
			mf->Render(hdc, false, false, false, false);
	}
}

HRESULT Enemy3::Init(float x, float y)
{
	Enemy::Init(x, y);

	enemy3 = ImageManager::GetSingleton()->AddImage("적3", "Image/enemy/bubred.bmp", 0, 0, 360, 120,
		6, 2, true, RGB(255, 0, 255));

	enemy3Motion = new ENEMY3();

	enemy3Ani = new ArrAnimation();
	enemy3Ani->Init(enemy3->GetWidth(), enemy3->GetHeight(), enemy3->GetFrameWidth(), enemy3->GetFrameHeight());
	enemy3Ani->SetUpdateTime(FPS / 10);
	enemy3Ani->SetPlayFrame(enemy3Motion->idle, sizeof(enemy3Motion->idle) / sizeof(int));
	enemy3Ani->Start();

	return S_OK;
}

void Enemy3::Release()
{
	Enemy::Release();

	SAFE_DELETE(enemy3Ani);
	SAFE_DELETE(enemy3Motion);
}

void Enemy3::Update()
{
	Enemy::Update();

	enemy3Ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (spawn)
	{
		spawn = false;
	}

	if (!isDead)
	{
		enemy3Ani->SetUpdateTime(FPS / 10);

		//경계
		if (moving && !isDetect && !doAttack)
			enemy3Ani->SetPlayFrame(enemy3Motion->idle, sizeof(enemy3Motion->idle) / sizeof(int));
	}
}

void Enemy3::Render(HDC hdc)
{
	if (!isDead)
	{
		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);

		enemy3->AnimationRender(hdc, pos.x, pos.y, enemy3Ani, false, false);

		if (mf && isFire)
			mf->Render(hdc, false, false, false, false);
	}
}

HRESULT Enemy4::Init(float x, float y)
{
	Enemy::Init(x, y);

	enemy4 = ImageManager::GetSingleton()->AddImage("적4", "Image/enemy/bullet.bmp", 0, 0, 300, 120,
		5, 2, true, RGB(255, 0, 255));

	enemy4Motion = new ENEMY4();

	enemy4Ani = new ArrAnimation();
	enemy4Ani->Init(enemy4->GetWidth(), enemy4->GetHeight(), enemy4->GetFrameWidth(), enemy4->GetFrameHeight());
	enemy4Ani->SetUpdateTime(FPS / 10);
	enemy4Ani->SetPlayFrame(enemy4Motion->idle, sizeof(enemy4Motion->idle) / sizeof(int));
	enemy4Ani->Start();

	return S_OK;
}

void Enemy4::Release()
{
	Enemy::Release();

	SAFE_DELETE(enemy4Motion);
	SAFE_DELETE(enemy4Ani);
}

void Enemy4::Update()
{
	Enemy::Update();

	enemy4Ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (spawn)
	{
		spawn = false;
	}

	if (!isDead)
	{
		enemy4Ani->SetUpdateTime(FPS / 10);

		//경계
		if (moving && !isDetect && !doAttack)
			enemy4Ani->SetPlayFrame(enemy4Motion->idle, sizeof(enemy4Motion->idle) / sizeof(int));

	}
}

void Enemy4::Render(HDC hdc)
{
	if (!isDead)
	{
		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);

		enemy4->AnimationRender(hdc, pos.x, pos.y, enemy4Ani, false, false);

		if (mf && isFire)
			mf->Render(hdc, false, false, false, false);
	}
}

HRESULT Boss::Init(float x, float y)
{
	Enemy::Init(x, y);

	hp = 500;

	boss = ImageManager::GetSingleton()->AddImage("보스", "Image/enemy/boss.bmp", 0, 0, 720, 640,
		9, 8, true, RGB(255, 0, 255));

	bossMotion = new BOSS();

	bossAni = new ArrAnimation();
	bossAni->Init(boss->GetWidth(), boss->GetHeight(), boss->GetFrameWidth(), boss->GetFrameHeight());
	bossAni->SetUpdateTime(FPS / 10);
	bossAni->SetPlayFrame(bossMotion->appear, sizeof(bossMotion->appear) / sizeof(int));
	bossAni->Start();

	appear = true;
	bossDie = false;

	angle = 0;

	float tempFloatX, tempFloatY;

	speed = 100;

	return S_OK;
}

void Boss::Release()
{
	Enemy::Release();

	SAFE_DELETE(bossMotion);
	SAFE_DELETE(bossAni);
}

void Boss::Update()
{
	// 맵 상에서의 인덱스 계산
	tileIdX = pos.x / TILE_SIZE;	tileIdY = pos.y / TILE_SIZE;

	FPOINT tempPos = pos;
	rc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

	if (!isDead && !spawn)
	{
		MoveMode(&tempPos);

		if (moving)
			LocateMode();

		else
		{
			attackVec.clear();

			for (int i = tileIdY - 2; i < tileIdY + 3; i++)
			{
				for (int j = tileIdX - 2; j < tileIdX + 3; j++)
				{

					attackVec.push_back(&mapTool->GetTileInf()[i * MAIN_TILE_X + j].rcTile);
				}
			}

			if (!moving && !isDetect && doAttack)
			{
				angle = atan2(-(tempFloatY - pos.y), tempFloatX - pos.x);
				angle += 1;

				if (angle > 360)
					angle = 0;

				tempFloatX += cosf(angle * PI / 180) * speed;
				tempFloatY -= sinf(angle * PI / 180) * speed;

				isFire = true;
				
			}
		}

		if (mf)
		{
			if (doAttack)
			{
				mf->Fire(tempFloatX, tempFloatY, 500);
			}

			mf->Update(true);
		}

		if (collision)
		{
			RECT tempRc;
			tempRc = GetRectToCenter(tempPos.x, tempPos.y, size, size);

			collision->SetTempEnemyRc(&tempRc);
			collision->EnemyUpdate();

			if (!collision->GetEnemyCheck())
				pos = tempPos;

			else
			{
				getId = false;
				moving = true;
				isDetect = false;
				doAttack = false;
			}

			collision->SetEnemyCheck(false);
		}

		if (hp <= 0)
		{
			bossDie = true;
		}
	}

	bossAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if (appear)
	{
		bossAni->SetUpdateTime(FPS / 25);
		bossAni->SetPlayFrame(bossMotion->appear, sizeof(bossMotion->appear) / sizeof(int));

		if (bossAni->GetNowPlayIdx() >= 8)
		{
			appear = false;
		}
	}

	else if (!isDead && !appear)
	{
		//경계
		if (moving && !isDetect && !doAttack)
			bossAni->SetPlayFrame(bossMotion->north, sizeof(bossMotion->north) / sizeof(int));

		//이동
		if (!moving && isDetect && !doAttack)
			bossAni->SetPlayFrame(bossMotion->teleport, sizeof(bossMotion->teleport) / sizeof(int));

		//공격
		if (!moving && !isDetect && doAttack)
			bossAni->SetPlayFrame(bossMotion->charge, sizeof(bossMotion->charge) / sizeof(int));
	}

	if (bossDie)
	{
		bossAni->SetPlayFrame(bossMotion->die, sizeof(bossMotion->die) / sizeof(int));

		if (bossAni->GetNowPlayIdx() >= 26)
		{
			bossDie = false;
		}
	}
}

void Boss::Render(HDC hdc)
{
	if (!isDead)
	{
		//RenderRectToCenter(hdc, pos.x, pos.y, size, size);
		boss->AnimationRender(hdc, pos.x, pos.y, bossAni, false, false);

		if (mf && isFire)
			mf->Render(hdc, false, false, false, false);
	}

	
}
