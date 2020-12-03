#include "MissileManager.h"
#include "Missile.h"


HRESULT MissileManager::Init()
{
	
	vecMissiles.resize(10);
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i] = new Missile();
		vecMissiles[i]->Init();
	}

	angle = 270;
	owner = nullptr;

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

void MissileManager::Update()
{
	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

void MissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

bool MissileManager::Fire()
{
	for (auto& it : vecMissiles)
	{
		if (it->GetIsCrash() || it->GetIsFire())
		{
			continue;
		}

		it->Init();
		it->SetIsFire(true);
		it->SetAngle(DEGREE_TO_RADIAN(angle));
		
		if (angle == 0)
		{
			it->SetDirection(2);
		}

		else if (angle == 90)
		{
			it->SetDirection(1);
		}
		else if (angle == 180)
		{
			it->SetDirection(0);
		}
		else if (angle == 270)
		{
			it->SetDirection(3);
		}

		it->SetPos(owner->GetPos());
		return true;
	}

	return false;
}

MissileManager::MissileManager()
{
}


MissileManager::~MissileManager()
{
}
