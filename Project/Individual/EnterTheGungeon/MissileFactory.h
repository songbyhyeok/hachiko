#pragma once

#include "GameNode.h"

class Missile;
class MissileFactory : public GameNode
{
protected:
	vector<Missile*> missileDatas;

	GameNode*	owner;

	int fireCount;
	int elapsedTime;

	int missileNum;

public:
	void NewMissile();
	virtual Missile* CreateMissile() = 0;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(bool boss1 = false);
	void Render(HDC hdc, bool north = false, bool south = false, bool east = false, bool west = false);

	bool Fire(float angle = 0.0f, float angle2 = 0.0f, int speed = 0);
	void FireDelayMode(float angle = 0.0f, float angle2 = 0.0f, int speed = 0);
	void FireInit();

	void SetOwner(GameNode * gameNode);

	void SetMissileNum();
	int * GetMissileNum();

	vector<Missile*> GetMissile();

	MissileFactory();
	virtual ~MissileFactory();
};

class PlayerMissileFactory : public MissileFactory
{
public:
	virtual Missile* CreateMissile();

	PlayerMissileFactory();
	virtual ~PlayerMissileFactory();
};

class EnemyMissileFactory : public MissileFactory
{
public:
	virtual Missile* CreateMissile();

	EnemyMissileFactory();
	virtual ~EnemyMissileFactory();
};


