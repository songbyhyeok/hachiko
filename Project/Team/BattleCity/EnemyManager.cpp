#include "EnemyManager.h"
#include "Enemy.h"
#include "BattleScene.h"


HRESULT EnemyManager::Init()
{
	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		SAFE_DELETE((*itEnemys));
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}
}

void EnemyManager::AddEnemy(float posX, float posY)
{
	
}

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT DefalutEnemyManager::Init()
{
	int posX, posY;

	posX = 0;
	posY = 0;

	vecEnemys.resize(1);

	for (int i = 0; i < 1; i++)
	{

		vecEnemys[i] = new DefaultEnemy();

	}

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK1 && i % 2 == 0)
		{
			posX = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			posY = i / (TILE_X*2) * TILESIZE*2 + TILESIZE;
			break;
		}

	}

	

	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->SetBattleScene(battlescene);
		(*itEnemys)->Init(posX, posY);
		(*itEnemys)->SetTarget(tank);
		
	}

	return S_OK;
}

void DefalutEnemyManager::AddEnemy(float posX, float posY)
{
	int posx = 0, posy = 0;
	
	if (vecEnemys.size() < DEFAULTTANKNUM)
	{
		Enemy* enemy = new DefaultEnemy();

		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK1 && i % 2 == 0)
			{
				posx = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
				posy = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
				break;
			}

		}

		enemy->SetBattleScene(battlescene);
		enemy->Init(posx, posy);
		enemy->SetTarget(tank);
		

		vecEnemys.push_back(enemy);
	}
}

DefalutEnemyManager::DefalutEnemyManager()
{
}

DefalutEnemyManager::~DefalutEnemyManager()
{
}

HRESULT SpeedEnemyManager::Init()
{
	int posX, posY;

	posX = 0;
	posY = 0;

	vecEnemys.resize(1);

	for (int i = 0; i < 1; i++)
	{

		vecEnemys[i] = new SpeedEnemy();

	}

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK2 && i % 2 == 0)
		{
			posX = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			posY = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}

	

	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->SetBattleScene(battlescene);
		(*itEnemys)->Init(posX, posY);
		(*itEnemys)->SetTarget(tank);
		
	}

	return S_OK;
}

void SpeedEnemyManager::AddEnemy(float posX, float posY)
{
	int posx = 0, posy = 0;
	if (vecEnemys.size() < SPEEDTANKNUM)
	{
		Enemy* enemy = new SpeedEnemy();

		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK2 && i % 2 == 0)
			{
				posx = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
				posy = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
				break;
			}

		}

		enemy->SetBattleScene(battlescene);
		enemy->Init(posx, posy);
		enemy->SetTarget(tank);
		

		vecEnemys.push_back(enemy);
	}
}

SpeedEnemyManager::SpeedEnemyManager()
{
}

SpeedEnemyManager::~SpeedEnemyManager()
{
}

HRESULT PowerEnemyManager::Init()
{
	int posX, posY;

	posX = 0;
	posY = 0;

	vecEnemys.resize(1);

	for (int i = 0; i < 1; i++)
	{

		vecEnemys[i] = new PowerEnemy();

	}

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK3 && i % 2 == 0)
		{
			posX = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			posY = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}

	

	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->SetBattleScene(battlescene);
		(*itEnemys)->Init(posX, posY);
		(*itEnemys)->SetTarget(tank);
	}

	return S_OK;
}

void PowerEnemyManager::AddEnemy(float posX, float posY)
{
	int posx = 0, posy = 0;
	if (vecEnemys.size() < POWERTANKNUM)
	{
		Enemy* enemy = new PowerEnemy();

		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (battlescene->GetTileInfo()[i].objterrain == ENEMYTANK3 && i % 2 == 0)
			{
				posx = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
				posy = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
				break;
			}

		}

		enemy->SetBattleScene(battlescene);
		enemy->Init(posx, posy);
		enemy->SetTarget(tank);
		

		vecEnemys.push_back(enemy);
	}
}

PowerEnemyManager::PowerEnemyManager()
{
}

PowerEnemyManager::~PowerEnemyManager()
{
}
