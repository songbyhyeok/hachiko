#pragma once

#include "GameNode.h"

class Enemy;
class Collision;
class TilemapToolScene;
class BattleScene;
class EnemyFactory : public GameNode
{
protected:
	vector<Enemy*> EnemyDatas;
	vector<Enemy*>::iterator itEnemys;

	int enemyNum;

	Collision* collision;
	TilemapToolScene * mapTool;
	BattleScene * battleScene;

public:
	void NewEnemy(int num, int x, int y);
	virtual Enemy* CreateEnemy() = 0;
	virtual void Regen(int x, int y);

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetCollision(Collision* _collision);
	void SetMapTool(TilemapToolScene * _mapTool);
	void SetBattleScene(BattleScene * _battleScene);

	vector<Enemy*> GetEnemy();
	vector<Enemy*>::iterator GetEnemyIt();

	EnemyFactory();
	~EnemyFactory();
};

class Enemy1Factory : public EnemyFactory
{
private:
	

public:
	virtual Enemy* CreateEnemy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual vector<Enemy*> GetEnemy();
	virtual vector<Enemy*>::iterator GetEnemyIt();

	Enemy1Factory();
	virtual ~Enemy1Factory();
};

class Enemy2Factory : public EnemyFactory
{
private:

public:
	virtual Enemy* CreateEnemy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Enemy2Factory();
	virtual ~Enemy2Factory();
};

class Enemy3Factory : public EnemyFactory
{
private:

public:
	virtual Enemy* CreateEnemy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Enemy3Factory();
	virtual ~Enemy3Factory();
};

class Enemy4Factory : public EnemyFactory
{
private:

public:
	virtual Enemy* CreateEnemy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Enemy4Factory();
	virtual ~Enemy4Factory();
};

class BossFactory : public EnemyFactory
{
private:

public:
	virtual Enemy* CreateEnemy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	BossFactory();
	virtual ~BossFactory();
};




