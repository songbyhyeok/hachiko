#include "MissileFactory.h"
#include "Missile.h"

void MissileFactory::NewMissile()
{
	missileDatas.resize(40);
	for (int i = 0; i < missileDatas.size(); i++)
	{
		missileDatas[i] = CreateMissile();
		missileDatas[i]->Init();
	}

	missileNum = missileDatas.size();

	elapsedTime = 0;
	fireCount = 0;

}

Missile * MissileFactory::CreateMissile()
{
	return nullptr;
}

HRESULT MissileFactory::Init()
{
	NewMissile();

	return S_OK;
}

void MissileFactory::Release()
{
	for (int i = 0; i != missileDatas.empty(); i++)
	{
		missileDatas[i]->Release();
		SAFE_ARR_DELETE(missileDatas[i]);
	}

	missileDatas.clear();
}

void MissileFactory::Update(bool boss1)
{
	for (int i = 0; i < missileDatas.size(); i++)
	{
		if (missileDatas[i]->GetisFire())
			missileDatas[i]->Update(boss1);
	}
}

void MissileFactory::Render(HDC hdc, bool north, bool south, bool east, bool west)
{
	for (int i = 0; i < missileDatas.size(); i++)
	{
		if (missileDatas[i]->GetisFire())
			missileDatas[i]->Render(hdc, north, south, east, west);
	}
}

bool MissileFactory::Fire(float angle, float angle2, int speed)
{
	if (missileNum > 0)
	{
		int missileCount = 1;

		missileNum -= missileCount;
	}

	else
		missileNum = 0;

	for (int i = 0; i < missileDatas.size(); i++)
	{
		if (missileDatas[i]->GetisFire())
			continue;

		missileDatas[i]->SetisFire(true);
		missileDatas[i]->SetAngle(angle, angle2);
		missileDatas[i]->SetSpeed(speed);
		missileDatas[i]->SetPos(owner->GetPos());

		return true;
	}

	return false;
}

void MissileFactory::FireDelayMode(float angle, float angle2, int speed)
{
	elapsedTime = 3;

	fireCount++;
	if (fireCount % elapsedTime == elapsedTime - 1)
	{
		fireCount = 0;
		Fire(angle, angle2, speed);
	}
}

void MissileFactory::FireInit()
{
	for (int i = 0; i < missileDatas.size(); i++)
	{
		missileDatas[i]->SetisFire(false);
	}
}

void MissileFactory::SetOwner(GameNode * gameNode)
{
	owner = gameNode;
}

void MissileFactory::SetMissileNum()
{
	missileNum = 20;
}

int* MissileFactory::GetMissileNum()
{
	return &missileNum;
}

vector<Missile*> MissileFactory::GetMissile()
{
	return missileDatas;
}

MissileFactory::MissileFactory()
{
}

MissileFactory::~MissileFactory()
{
}

Missile * PlayerMissileFactory::CreateMissile()
{
	return new PlayerMissile();
}


PlayerMissileFactory::PlayerMissileFactory()
{
}

PlayerMissileFactory::~PlayerMissileFactory()
{
}

Missile * EnemyMissileFactory::CreateMissile()
{
	return new EnemyMissile();
}

EnemyMissileFactory::EnemyMissileFactory()
{
}

EnemyMissileFactory::~EnemyMissileFactory()
{
}
