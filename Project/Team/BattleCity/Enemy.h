#pragma once
#include "GameNode.h"

class BattleScene;
class Image;
class MissileManager;
class Astar;
class Tank;
class Missile;
class Animation;
class Enemy : public GameNode
{
protected:

	FPOINT startPos;
	FPOINT endPos;
	vector<Missile*> ownmissile;

	Image* image;
	Image* effectimage;

	bool isStart;

	int currFrameX, currFrameY;
	int effectFrameX, effectFrameY;
	int updateCount;

	int size;
	float firetime;
	float angle;
	float speed;

	int count;
	int index1;
	int index2;
	int fireDelay;
	int fireCount;
	int **map;
	int HP;

	bool isDead;

	Astar* astar;
	MissileManager* missileMgr;
	BattleScene* battlescene;

	Tank * tank;
	Image* startimg;
	Animation* ani;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY)=0;
	virtual void Release();
	virtual void Update()=0;
	virtual void Render(HDC hdc);

	void AstarInit(int startx, int starty, int endx, int endy);
	void SetBattleScene(BattleScene* _battlescene) { battlescene = _battlescene; }
	void SetTarget(Tank* _tank) { tank = _tank; }
	
	//FPOINT GetPos() { return pos; }

	void Collision();

	Enemy();
	virtual ~Enemy();
};

class DefaultEnemy : public Enemy
{
	virtual HRESULT Init(float posX, float posY);
	virtual void Update();


public:
	DefaultEnemy();
	virtual ~DefaultEnemy();
};

class SpeedEnemy : public Enemy
{
	virtual HRESULT Init(float posX, float posY);
	virtual void Update();


public:
	SpeedEnemy();
	virtual ~SpeedEnemy();
};

class PowerEnemy : public Enemy
{
	virtual HRESULT Init(float posX, float posY);
	virtual void Update();


public:
	PowerEnemy();
	virtual ~PowerEnemy();
};


