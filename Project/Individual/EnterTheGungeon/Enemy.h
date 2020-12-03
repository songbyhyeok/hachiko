#pragma once

#include "GameNode.h"

#define VISUALFIELD_X 4
#define VISUALFIELD_Y 4

class Image;
class Collision;
class EnemyMissileFactory;
class TilemapToolScene;
class Animation;
class Enemy : public GameNode
{
protected:
	Collision* collision;
	TilemapToolScene * mapTool;

	int tileIdX, tileIdY;

	int size;
	int hp;

	int countMove;
	int moveDelay;

	float angle;

	bool spawn;

	bool moving;
	bool isDetect;
	bool doAttack;
	bool isHit;
	bool isDead;
	bool isFire;
	bool getId;
	int tempId;

	bool xSmall;
	bool xBig;
	bool ySmall;
	bool yBig;

	bool collisionCheck;

	int regenCount;
	int regenTime;

	RECT rc;
	RECT *tempRc;

	vector<RECT*> moveVec;
	vector<RECT*> locateVec;
	vector<RECT*> attackVec;

	EnemyMissileFactory* mf;

public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc) = 0;

	void MoveMode(FPOINT *tempPos);
	void LocateMode();
	void AttackMode();

	void SetHp(int _hp);
	int GetHp();

	void SetMoving(bool _moving);
	bool GetMoving();

	void SetDetect(bool _isDetect);
	bool GetDetect();

	void SetDoAttack(bool _doAttack);
	bool GetDoAttack();

	void SetIsHit(bool _isHit);
	bool GetIsHit();

	void SetIsDead(bool _isDead);
	bool GetIsDead();

	bool GetSpawn();

	void BringPlayerRectPos(RECT* playerRc);

	void SetTileIdX(int _idX);
	int GetTileIdX();

	void SetTileIdY(int _idY);
	int GetTileIdY();

	void SetCollisionCheck(bool _check);
	bool GetCollisionCheck();

	RECT* GetRect();
	vector<RECT *> GetMoveVec();
	vector<RECT *> GetLocateVec();
	vector<RECT *> GetAttackVec();

	EnemyMissileFactory * GetMissileMf();

	void SetCollision(Collision* _collision);

	void SetMapTool(TilemapToolScene * _mapTool);

	Enemy();
	~Enemy();
};

class Enemy1 : public Enemy
{
private:
	typedef struct tagMushroomIdle
	{
		int spawn[9] = { 0,1,2,3,4,5,6,7,8 };
		int attack[9] = { 9,10,11,12,13,14,15,16,17 };
		int hit[9] = { 18,19,20,21,22,23,24,25,26 };
		int die[9] = { 27,28,29,30,31,32,33,34,35 };
		int idle[9] = { 36,37,38,39,40,41,42,43,44 };
		int move[9] = { 45,46,47,48,49,50,51,52,53 };
	}MUSHROOM, *PMMUSHROOM;

	Image* mushroom;
	MUSHROOM* mushroomMotion;
	Animation* mushroomAni;
	
public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};

class Enemy2 : public Enemy
{
private:
	typedef struct tagEnemy2
	{
		int idle[4] = { 0,1,2,3 };
		int attack[4] = { 4,5,6,7 };
		int die[4] = { 8,9,10,11 };
	}ENEMY2, *PENEMY2;

	Image* enemy2;
	ENEMY2* enemy2Motion;
	Animation* enemy2Ani;

public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

class Enemy3 : public Enemy
{
private:
	typedef struct tagEnemy3
	{
		int idle[6] = { 0,1,2,3,4,5 };
		int die[6] = { 6,7,8,9,10,11 };
	}ENEMY3, *PENEMY3;

	Image* enemy3;
	ENEMY3* enemy3Motion;
	Animation* enemy3Ani;

public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

class Enemy4 : public Enemy
{
private:
	typedef struct tagEnemy4
	{
		int idle[5] = { 0,1,2,3,4 };
		int die[5] = { 5,6,7,8,9 };
	}ENEMY4, *PENEMY4;

	Image* enemy4;
	ENEMY4* enemy4Motion;
	Animation* enemy4Ani;

public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

class Boss : public Enemy
{
private:
	typedef struct tagBoss
	{
		int appear[9] = { 0,1,2,3,4,5,6,7,8 };
		int charge[9] = { 9,10,11,12,13,14,15,16,17 };
		int die[9] = { 18,19,20,21,22,23,24,25,26 };
		int teleport[9] = { 27,28,29,30,31,32,33,34,35 };
		int south[9] = { 36,37,38,39,40,41,42,43,44 };
		int north[9] = { 45,46,47,48,49,50,51,52,53 };
		int southWest[9] = { 54,55,56,57,58,59,60,61,62 };
		int NorthEast[9] = { 63,64,65,66,67,68,69,70,71 };
	}BOSS, *PBOSS;

	Image* boss;
	BOSS* bossMotion;
	Animation* bossAni;

	bool appear;
	bool bossDie;
	float tempFloatX, tempFloatY;
	int speed;

public:
	virtual HRESULT Init(float x = 0.0f, float y = 0.0f);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};