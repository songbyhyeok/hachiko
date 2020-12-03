#include "MissileManager.h"
#include "Missile.h"
#include "Enemy.h"

HRESULT MissileManager::Init()
{
	owner = nullptr;
	isTarget = false;

	angle = 0;	rotateAngle = 0;

	SetBullet(600);
	SetNorBullet(600);
	SetHighBullet(2);
	/////
	/*SetEnemyBullet(30);
	SetEnemy1Bullet(30);
	SetUFOBullet(30);
	SetEyeBullet(30);*/
	
	vecMissiles.reserve(100);

	fireCount = 0;
	fireDelay = rand() % 100 + 100;

	return S_OK;
}

void MissileManager::Release()
{
	for (auto& it : vecMissiles)
	{
		it->Release();
		SAFE_DELETE(it);
	}

	vecMissiles.clear();
}

void MissileManager::Update(int num, int remainder)
{
	for (auto& it : vecMissiles)
	{
		it->Update(num, remainder);
	}

	for (auto& its : vecNormalMissiles)
	{
		its->Update(num, remainder);
	}
}

void MissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}

	for (auto& its : vecNormalMissiles)
	{
		its->Render(hdc);
	}
}

void MissileManager::SetFireDelay(int maxDelay, int minDelay)
{
	fireDelay = rand() % maxDelay + minDelay;
}

bool MissileManager::FireMode(float _angleX,float _angleY, float _speed, float x, float y)
{
	fireCount++;
	if (fireDelay <= fireCount)
	{
		fireCount = 0;

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
				continue;

			it->SetIsFire(true);
			it->SetSpeed(_speed);
			it->SetAngleX(DEGREE_TO_RADIAN(_angleX));
			it->SetAngleY(DEGREE_TO_RADIAN(_angleY));
			it->SetIsPosX(owner->GetPos().x + x);
			it->SetIsPosY(owner->GetPos().y + y);
			
			return true;
		}
	}

	return false;
}

bool MissileManager::playerFireMode(float _angle, float _speed)
{
	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
			continue;

		it->SetIsFire(true);
		it->SetSpeed(_speed);
		it->SetAngleX(DEGREE_TO_RADIAN(_angle));
		it->SetAngleY(DEGREE_TO_RADIAN(_angle));
		it->SetIsPosX(owner->GetPos().x);
		it->SetIsPosY(owner->GetPos().y);

		return true;
	}

	return false;
}

void MissileManager::SetMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecMissiles.capacity(); i++)
	{
		Missile* missile = new Missile();
		missile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(missile);
	}
}

void MissileManager::SetNorMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecNormalMissiles.capacity(); i++)
	{
		NormalMissile* Normissile = new NormalMissile();
		Normissile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(Normissile);
	}
}

void MissileManager::SetHighMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecHighMissiles.capacity(); i++)
	{
		HighMissile* highMissile = new HighMissile();
		highMissile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(highMissile);
	}
}

//////

void MissileManager::SetEnemyMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecEnemyMissiles.capacity(); i++)
	{
		EnemyMissile* enemyMissile = new EnemyMissile();
		enemyMissile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(enemyMissile);
	}
}

void MissileManager::SetEnemy1MissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecEnemy1Missiles.capacity(); i++)
	{
		Enemy1Missile* enemy1Missile = new Enemy1Missile();
		enemy1Missile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(enemy1Missile);
	}
}

void MissileManager::SetUFOMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecHighMissiles.capacity(); i++)
	{
		UFOMissile* ufoMissile = new UFOMissile();
		ufoMissile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(ufoMissile);
	}
}

void MissileManager::SetEyeMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY)
{
	for (int i = 0; i < vecEyeMissiles.capacity(); i++)
	{
		EyeMissile* eyeMissile = new EyeMissile();
		eyeMissile->Init(image, _width, _height, maxKeyX, maxKeyY);
		vecMissiles.push_back(eyeMissile);
	}
}



MissileManager::MissileManager(){}

MissileManager::~MissileManager(){}
