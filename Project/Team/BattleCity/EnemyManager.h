#pragma once
#include "GameNode.h"
#include <vector>

class BattleScene;
class Enemy;
class Tank;
class EnemyManager : public GameNode
{
protected:
	vector<Enemy*>	vecEnemys;
	vector<Enemy*>::iterator	itEnemys;
	BattleScene* battlescene;

	Tank * tank;

	int life = 20;
public:
	virtual HRESULT Init()=0;
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void AddEnemy(float posX, float posY)=0;

	void SetBattleScene(BattleScene* _battlescene) { battlescene = _battlescene; }

	void SetTankInf(Tank * _tank) { tank = _tank; }

	void SetLife(int _life) { life = _life; }
	int GetLife() { return life; }

	EnemyManager();
	~EnemyManager();
};

class DefalutEnemyManager : public EnemyManager
{
	
public:
	virtual HRESULT Init();
	virtual void AddEnemy(float posX, float posY);

	DefalutEnemyManager();
	~DefalutEnemyManager();
};

class SpeedEnemyManager : public EnemyManager
{

public:
	virtual HRESULT Init();
	virtual void AddEnemy(float posX, float posY);

	SpeedEnemyManager();
	~SpeedEnemyManager();
};

class PowerEnemyManager : public EnemyManager
{

public:
	virtual HRESULT Init();
	virtual void AddEnemy(float posX, float posY);

	PowerEnemyManager();
	~PowerEnemyManager();
};

