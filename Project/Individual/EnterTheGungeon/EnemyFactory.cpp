#include "EnemyFactory.h"
#include "Enemy.h"

void EnemyFactory::NewEnemy(int num, int x, int y)
{
	enemyNum = num;

	EnemyDatas.resize(enemyNum);
	for (int i = 0; i < EnemyDatas.size(); i++)
	{
		EnemyDatas[i] = CreateEnemy();
		EnemyDatas[i]->Init((i % num) * 250 + x, y);
		EnemyDatas[i]->SetCollision(collision);
		EnemyDatas[i]->SetMapTool(mapTool);
	}
}

void EnemyFactory::Regen(int x, int y)
{
	for (int i = 0; i < EnemyDatas.size(); i++)
	{
		EnemyDatas[i]->Init((i % enemyNum) * 250 + x, y);
	}
}

HRESULT EnemyFactory::Init()
{



	return S_OK;
}

void EnemyFactory::Release()
{
	for (int i = 0; i != EnemyDatas.empty(); i++)
	{
		EnemyDatas[i]->Release();
		SAFE_ARR_DELETE(EnemyDatas[i]);
	}

	EnemyDatas.clear();
}

void EnemyFactory::Update()
{
	for (int i = 0; i < EnemyDatas.size(); i++)
	{
		EnemyDatas[i]->Update();
	}
}

void EnemyFactory::Render(HDC hdc)
{
	for (int i = 0; i < EnemyDatas.size(); i++)
	{
		EnemyDatas[0]->Render(hdc);
	}
}

void EnemyFactory::SetCollision(Collision * _collision)
{
	collision = _collision;
}

void EnemyFactory::SetMapTool(TilemapToolScene * _mapTool)
{
	mapTool = _mapTool;
}

void EnemyFactory::SetBattleScene(BattleScene * _battleScene)
{
	battleScene = _battleScene;
}

vector<Enemy*> EnemyFactory::GetEnemy()
{
	return EnemyDatas;
}

vector<Enemy*>::iterator EnemyFactory::GetEnemyIt()
{
	return itEnemys;
}

EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

Enemy * Enemy1Factory::CreateEnemy()
{
	return new Enemy1();
}

HRESULT Enemy1Factory::Init()
{

	return S_OK;
}

void Enemy1Factory::Release()
{
	EnemyFactory::Release();
}

void Enemy1Factory::Update()
{
	EnemyFactory::Update();
}

void Enemy1Factory::Render(HDC hdc)
{
	EnemyFactory::Render(hdc);
}

vector<Enemy*> Enemy1Factory::GetEnemy()
{
	return EnemyFactory::GetEnemy();
}

vector<Enemy*>::iterator Enemy1Factory::GetEnemyIt()
{
	return EnemyFactory::GetEnemyIt();
}

Enemy1Factory::Enemy1Factory()
{
}

Enemy1Factory::~Enemy1Factory()
{
}

Enemy * Enemy2Factory::CreateEnemy()
{
	return new Enemy2();
}

HRESULT Enemy2Factory::Init()
{
	return S_OK;
}

void Enemy2Factory::Release()
{
	EnemyFactory::Release();
}

void Enemy2Factory::Update()
{
	EnemyFactory::Update();
}

void Enemy2Factory::Render(HDC hdc)
{
	EnemyFactory::Render(hdc);
}

Enemy2Factory::Enemy2Factory()
{
}

Enemy2Factory::~Enemy2Factory()
{
}

Enemy * Enemy3Factory::CreateEnemy()
{
	return new Enemy3();
}

HRESULT Enemy3Factory::Init()
{
	return S_OK;
}

void Enemy3Factory::Release()
{
	EnemyFactory::Release();
}

void Enemy3Factory::Update()
{
	EnemyFactory::Update();
}

void Enemy3Factory::Render(HDC hdc)
{
	EnemyFactory::Render(hdc);
}

Enemy3Factory::Enemy3Factory()
{
}

Enemy3Factory::~Enemy3Factory()
{
}

Enemy * Enemy4Factory::CreateEnemy()
{
	return new Enemy4();
}

HRESULT Enemy4Factory::Init()
{
	return S_OK;
}

void Enemy4Factory::Release()
{
	EnemyFactory::Release();
}

void Enemy4Factory::Update()
{
	EnemyFactory::Update();
}

void Enemy4Factory::Render(HDC hdc)
{
	EnemyFactory::Render(hdc);
}

Enemy4Factory::Enemy4Factory()
{
}

Enemy4Factory::~Enemy4Factory()
{
}

Enemy * BossFactory::CreateEnemy()
{
	return new Boss();
}

HRESULT BossFactory::Init()
{
	return S_OK;
}

void BossFactory::Release()
{
	EnemyFactory::Release();
}

void BossFactory::Update()
{
	EnemyFactory::Update();
}

void BossFactory::Render(HDC hdc)
{
	EnemyFactory::Render(hdc);
}

BossFactory::BossFactory()
{
}

BossFactory::~BossFactory()
{
}
