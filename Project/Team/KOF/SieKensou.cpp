#include "SieKensou.h"
#include "SieKensou2.h"
#include "Image.h"

HRESULT SieKensou::Init()
{
	//캐릭터 설정
	pos.x = 200;	pos.y = 300;
	
	curKeyFrameX = 0, curKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 1.0f;

	hp = 100;
	attack = 10;
	blast = pos.x;

	isPlayer = true;
	isWin = false;
	
	// 각 이미지 동적할당
	stand = new Image();
	stand->Init("Image/SieKensou/Stand.bmp",
		pos.x, pos.y, 900, 108, 9, 1, true, RGB(255, 0, 255));

	sitDown = new Image();
	sitDown->Init("Image/SieKensou/Down.bmp",
		pos.x, pos.y, 200, 114, 2, 1, true, RGB(255, 0, 255));

	jump = new Image();
	jump->Init("Image/SieKensou/Jump.bmp",
		pos.x, pos.y, 1000, 160, 10, 1, true, RGB(255, 0, 255));

	left = new Image();
	left->Init("Image/SieKensou/Left.bmp",
		pos.x, pos.y, 700, 108, 7, 1, true, RGB(255, 0, 255));

	right = new Image();
	right->Init("Image/SieKensou/Right.bmp",
		pos.x, pos.y, 700, 119, 7, 1, true, RGB(255, 0, 255));

	eat = new Image();
	eat->Init("Image/SieKensou/Eat.bmp",
		pos.x, pos.y, 1900, 117, 19, 1, true, RGB(255, 0, 255));

	jab = new Image();
	jab->Init("Image/SieKensou/Jab.bmp",
		pos.x, pos.y, 500, 113, 5, 1, true, RGB(255, 0, 255));

	kick = new Image();
	kick->Init("Image/SieKensou/Kick.bmp",
		pos.x, pos.y, 600, 128, 6, 1, true, RGB(255, 0, 255));

	energy = new Image();
	energy->Init("Image/SieKensou/Energy.bmp",
		pos.x, pos.y, 1170, 120, 9, 1, true, RGB(128, 0, 255));

	energyWave = new Image();
	energyWave->Init("Image/SieKensou/EnergyWave.bmp",
		pos.x, pos.y, 1040, 102, 8, 1, true, RGB(128, 0, 255));

	defend = new Image();
	defend->Init("Image/SieKensou/Defend.bmp",
		pos.x, pos.y, 400, 114, 4, 1, true, RGB(255, 0, 255));

	suffer = new Image();
	suffer->Init("Image/SieKensou/Suffer.bmp",
		pos.x, pos.y, 500, 119, 5, 1, true, RGB(255, 0, 255));

	dead = new Image();
	dead->Init("Image/SieKensou/Dead.bmp",
		pos.x, pos.y, 700, 139, 7, 1, true, RGB(255, 0, 255));

	// hitBox 정보
	cRect.body = { 0, 0, 0, 0 };
	cRect.leg = { 0, 0, 0, 0 };
	cRect.hit = { 0, 0, 0, 0 };
	cRect.defence = { 0, 0, 0, 0 };

	//각 모션 정보
	standInf = { stand, cRect, 0, 0, 9, true };
	sitDownInf = { sitDown, cRect, 6, 0, 2, false };
	jumpInf = { jump, cRect, 152, 0, 10, false };
	leftInf = { left, cRect, 0, 0, 7, false };
	rightInf = { right, cRect, 11, 0, 7, false };
	eatInf = { eat, cRect, 9, 0, 19, false };
	jabInf = { jab, cRect, 5, 0, 5, false };
	kickInf = { kick, cRect, 20, 0, 6, false };
	energyInf = { energy, cRect, 20, 0, 9, false };
	energyWaveInf = { energyWave, cRect, 6, 0, 8, false };
	defendInf = { defend, cRect, 5, 0, 4, false };
	sufferInf = { suffer, cRect, 11, 0, 5, false };
	deadInf = { dead, cRect, 41, 0, 7, false };

	return S_OK;
}

void SieKensou::Release()
{
	stand->Release();	sitDown->Release();		jump->Release();
	delete stand;		delete sitDown;			delete jump;

	left->Release();	right->Release();
	delete left;		delete right;

	eat->Release();
	delete eat;

	jab->Release();		kick->Release();
	delete jab;			delete kick;

	energy->Release();	energyWave->Release();
	delete energy;		delete energyWave;

	defend->Release();
	delete defend;
	suffer->Release();
	delete suffer;
	dead->Release();
	delete dead;
}

void SieKensou::Update()
{
	elapsedFrame++;

	//죽음
	if (hp <= 0)
	{
		standInf.moveMent = false;
		deadInf.moveMent = true;

		if (elapsedFrame % 20 == 19)
		{
			elapsedFrame = 0;

			curKeyFrameX++;
			if (curKeyFrameX >= deadInf.maxKeyFrame)
			{
				curKeyFrameX = 0;
				
				standInf.moveMent = true;
				deadInf.moveMent = false;

				hp = 100;
			}
		}	
	}

	// 멈춰있을 때
	if (standInf.moveMent && elapsedFrame % 10 == 9)
	{
		elapsedFrame = 0;

		curKeyFrameX++;
		if (curKeyFrameX >= standInf.maxKeyFrame)
			curKeyFrameX = 0;
	}

	// 점프
	if (jumpInf.moveMent && elapsedFrame % 10 == 9)
	{
		elapsedFrame = 0;

		++curKeyFrameX;
		if (curKeyFrameX == 1)
			pos.y += 50;

		else if (curKeyFrameX == 6)
			pos.y += 10;

		else if (curKeyFrameX == 7)
			pos.y += 10;

		else if (curKeyFrameX == 8)
			pos.y += 25;

		else if (curKeyFrameX >= 10)
		{
			pos.y -= 95;
			curKeyFrameX = 0;

			standInf.moveMent = true;
			jumpInf.moveMent = false;
		}
	}
	
	// 에너지파
	if (energyWaveInf.moveMent && elapsedFrame % 10 == 9)
	{
		elapsedFrame = 0;

		curKeyFrameX++;
		blast += 100;
		if (curKeyFrameX >= energyWaveInf.maxKeyFrame)
		{
			curKeyFrameX = 0;

			standInf.moveMent = true;
			energyWaveInf.moveMent = false;

			blast = pos.x;
		}
	}

	// 먹는모션
	if (eatInf.moveMent && elapsedFrame % 10 == 9)
	{
		elapsedFrame = 0;

		curKeyFrameX++;
		if (curKeyFrameX >= eatInf.maxKeyFrame)
		{
			curKeyFrameX = 0;

			standInf.moveMent = true;
			eatInf.moveMent = false;
		}
	}

	// 맞을 때
	if (sufferInf.moveMent && elapsedFrame % 10 == 9)
	{
		elapsedFrame = 0;

		standInf.moveMent = true;
		sufferInf.moveMent = false;

		curKeyFrameX++;
		if (curKeyFrameX >= sufferInf.maxKeyFrame)
		{
			curKeyFrameX = 0;

			pos.x -= 10;
		}
	}

	// 키입력
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT || VK_RIGHT))
	{
		elapsedFrame = 0;
		curKeyFrameX = 0;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		standInf.moveMent = false;
		jumpInf.moveMent = true;

		curKeyFrameX = 0;
		elapsedFrame = 0;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		if (!sitDownInf.moveMent && !kickInf.moveMent && !jabInf.moveMent && !jumpInf.moveMent && !eatInf.moveMent)
		{
			standInf.moveMent = false;
			leftInf.moveMent = true;

			pos.x -= 3;

			if (elapsedFrame % 10 == 9)
			{
				elapsedFrame = 0;

				curKeyFrameX++;
				if (curKeyFrameX >= leftInf.maxKeyFrame)
					curKeyFrameX = 0;
			}
		}

		else
		{
			standInf.moveMent = true;
			leftInf.moveMent = false;
			sitDownInf.moveMent = false;
			eatInf.moveMent = false;
			jumpInf.moveMent = false;
			defendInf.moveMent = false;
		}
	}

	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		if (!sitDownInf.moveMent && !kickInf.moveMent && !jabInf.moveMent && !jumpInf.moveMent && !eatInf.moveMent && !defendInf.moveMent)
		{
			standInf.moveMent = false;
			rightInf.moveMent = true;

			pos.x += 3;

			if (elapsedFrame % 10 == 9)
			{
				elapsedFrame = 0;

				curKeyFrameX++;
				if (curKeyFrameX >= rightInf.maxKeyFrame)
					curKeyFrameX = 0;
			}
		}

		else
		{
			standInf.moveMent = true;
			rightInf.moveMent = false;
			sitDownInf.moveMent = false;
			eatInf.moveMent = false;
			jumpInf.moveMent = false;
			defendInf.moveMent = false;
		}
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{
		if (!kickInf.moveMent && !jabInf.moveMent && !jumpInf.moveMent && !eatInf.moveMent && !defendInf.moveMent)
		{
			standInf.moveMent = false;
			sitDownInf.moveMent = true;

			if (elapsedFrame % 10 >= 9)
			{
				elapsedFrame = 0;

				curKeyFrameX++;
				if (curKeyFrameX >= sitDownInf.maxKeyFrame)
					curKeyFrameX = 0;
			}
		}

		else
		{
			standInf.moveMent = true;
			sitDownInf.moveMent = false;
			eatInf.moveMent = false;
			jumpInf.moveMent = false;
			defendInf.moveMent = false;
		}
	}

	// 주먹
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		standInf.moveMent = false;
		jabInf.moveMent = true;

		if (elapsedFrame % 10 == 9)
		{
			elapsedFrame = 0;

			curKeyFrameX++;
			if (curKeyFrameX >= jabInf.maxKeyFrame)
				curKeyFrameX = 0;
		}

	}

	// 발차기
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		standInf.moveMent = false;
		kickInf.moveMent = true;

		if (elapsedFrame % 10 == 9)
		{
			elapsedFrame = 0;

			curKeyFrameX++;
			if (curKeyFrameX >= kickInf.maxKeyFrame)
				curKeyFrameX = 0;

		}
	}

	// 방어
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		standInf.moveMent = false;
		defendInf.moveMent = true;

		if (elapsedFrame % 10 == 9)
		{
			elapsedFrame = 0;

			curKeyFrameX++;
			if (curKeyFrameX >= defendInf.maxKeyFrame)
			{
				curKeyFrameX = 0;
				hp -= 10;
			}
		}
	}

	// 에너지파
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
	{
		standInf.moveMent = false;
		energyInf.moveMent = true;
		
		if (elapsedFrame % 10 == 9)
		{
			elapsedFrame = 0;

			curKeyFrameX++;
			if (curKeyFrameX >= energyInf.maxKeyFrame)
				{
					standInf.moveMent = true;
					energyInf.moveMent = false;
					energyWaveInf.moveMent = true;

					curKeyFrameX = 0;
				}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
	{
		standInf.moveMent = true;
		sitDownInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
	{
		standInf.moveMent = true;
		leftInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
	{
		standInf.moveMent = true;
		rightInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
	{
		standInf.moveMent = true;
		jabInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp('A'))
	{
		standInf.moveMent = true;
		kickInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp('D'))
	{
		standInf.moveMent = true;
		defendInf.moveMent = false;
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp('E'))
	{
		standInf.moveMent = false;
		eatInf.moveMent = true;
	}

	//else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
	//{
	//	standInf.moveMent = true;
	//	energyInf.motion = false;
	//}

	/*if (KeyManager::GetSingleton()->IsOnceKeyUp('F'))
	{
		standInf.moveMent = true;
		energyInf.motion = false;
	}*/

	cRect.body = { (int)pos.x + 25, (int)pos.y + 20, (int)pos.x + 65, (int)pos.y + 70 };
	cRect.leg = { (int)pos.x + 25, (int)pos.y + 70, (int)pos.x + 65, (int)pos.y + 100 };

	if (jabInf.moveMent || kickInf.moveMent)
		cRect.hit = { (int)pos.x + 65, (int)pos.y + 20, (int)pos.x + 95, (int)pos.y + 40 };

	if (defendInf.moveMent)
		cRect.defence = { (int)pos.x + 55, (int)pos.y + 10, (int)pos.x + 85, (int)pos.y + 40 };
}

void SieKensou::Render(HDC hdc)
{
	if (standInf.moveMent)
		stand->FrameRender(hdc, pos.x, pos.y - standInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (sitDownInf.moveMent)
		sitDown->FrameRender(hdc, pos.x, pos.y - sitDownInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (jumpInf.moveMent)
		jump->FrameRender(hdc, pos.x, pos.y - jumpInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (leftInf.moveMent)
		left->FrameRender(hdc, pos.x, pos.y - leftInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (rightInf.moveMent)
		right->FrameRender(hdc, pos.x, pos.y - rightInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (eatInf.moveMent)
		eat->FrameRender(hdc, pos.x, pos.y - eatInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);
	
	if (jabInf.moveMent)
	{
		jab->FrameRender(hdc, pos.x, pos.y - jabInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

		if (curKeyFrameX == jabInf.maxKeyFrame - 2)
			RenderRect(hdc, cRect.hit);
	}

	if (kickInf.moveMent)
	{
		kick->FrameRender(hdc, pos.x, pos.y - kickInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

		if (curKeyFrameX == kickInf.maxKeyFrame - 3)
			RenderRect(hdc, cRect.hit);
	}

	if (energyInf.moveMent)
	{
		energy->FrameRender(hdc, pos.x, pos.y - energyInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);
	}

	if (energyWaveInf.moveMent)
		energyWave->FrameRender(hdc, blast, pos.y - energyWaveInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);
		
	if (defendInf.moveMent)
		defend->FrameRender(hdc, pos.x, pos.y - defendInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	if (sufferInf.moveMent)
		suffer->FrameRender(hdc, pos.x, pos.y - sufferInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);
	
	if (deadInf.moveMent)
		dead->FrameRender(hdc, pos.x, pos.y - deadInf.adjustHeight, curKeyFrameX, curKeyFrameY, scale);

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
 	hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RenderRect(hdc, cRect.body);
	RenderRect(hdc, cRect.leg);
	RenderRect(hdc, cRect.defence);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void SieKensou::SetPosX(float _x) { pos.x = _x; }

void SieKensou::SetPosY(float _y) { pos.y = _y; }

void SieKensou::SetScale(float _scale) { this->scale = _scale; }

void SieKensou::SetStandInf(bool TF) { standInf.moveMent = TF; }

void SieKensou::SetSuffer(bool TF) { sufferInf.moveMent = TF; }

void SieKensou::SetTarget(SieKensou2 * enemyInf) { target = enemyInf; }

void SieKensou::SetBack(float push) { pos.x -= push; }

void SieKensou::SetLoseHp(int _hp)  {hp -= _hp; }

CHARINF SieKensou::GetJabInf() { return jabInf; }

CHARINF SieKensou::GetKickInf() { return kickInf; }

CHARINF SieKensou::GetDefendInf() { return defendInf; }

CHARINF SieKensou::GetSufferInf() {return sufferInf;}

CRECT SieKensou::GetCharInf() { return cRect; }

SieKensou2 * SieKensou::GetTarget() { return target; }

int SieKensou::GetHp() { return hp; }

int SieKensou::GetAttack() { return attack; }

bool SieKensou::GetIsPlayer() { return isPlayer; }

bool SieKensou::GetIsWin() { return isWin; }

SieKensou::SieKensou()
{}

SieKensou::~SieKensou()
{}
