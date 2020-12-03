#pragma once
#include "GameNode.h"

class Image;
class MissileManager;
class Player;
class Missile;

class Enemy : public GameNode
{
protected:
	Image * isEnemy;
	MissileManager* missileMgr;
	Player * isTarget;

	float speed;
	float angle, angle1;
	float rotateAngle;

	int fireDelay;
	int fireCount;

	int bullet;

	bool isCrashP;
	bool isCrashM;

	bool isLeft;
	bool isRight;

	bool isFire;

	bool isCurBool;
	bool isDead;

public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY) = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;

	void DisappearMode();

	void SetIsTarget(Player * _isTarget);

	void SetIsCrashP(bool _isCrash) { isCrashP = _isCrash; }
	bool GetIsCrashP() { return isCrashP; }

	void SetIsCrashM(bool _isCrashM) { isCrashM = _isCrashM; }
	bool GetIsCrashM() { return isCrashM; }

	bool GetIsFire() { return isFire; }

	void SetIsCurBool(bool _is) { isCurBool = _is; }
	bool GetIsCurBool() { return isCurBool; }

	void SetisDead(bool _is) { isDead = _is; }
	bool GetisDead() { return isDead; }

	Enemy* GetEnemyInf() { return this; }
	MissileManager * GetMissileInf() { return missileMgr; }

	Enemy();
	virtual ~Enemy();
};

class BombMan : public Enemy
{
private:

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Suicide();
	void Motion();
	
	BombMan();
	virtual ~BombMan();
};

class Comet : public Enemy
{
private:
	int location;

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Comet();
	virtual ~Comet();
};

class JellyFish : public Enemy
{
private:

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	JellyFish();
	virtual ~JellyFish();
};

class UFO : public Enemy
{
private:

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	UFO();
	virtual ~UFO();
};

class UFOEnemy : public Enemy
{
private:

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	UFOEnemy();
	virtual ~UFOEnemy();
};

class CuteEye : public Enemy
{
private:
	
public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	CuteEye();
	virtual ~CuteEye();
};

class ShyEye : public Enemy
{
private:

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	ShyEye();
	virtual ~ShyEye();
};

class GiantBalloon : public Enemy // <- º¸½º1
{
private:
	Image* fireMode;
	int GiantBalloonHP;
	bool isGiantBalloonHit;
	bool isBossIm;

public:
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void MoveLeft();
	void MoveRight();
	void IsAttack();
	void MovementControl();
	bool GetBossHit() {return isGiantBalloonHit;}
	void SetBossHit(bool isHit) { isGiantBalloonHit = isHit; }

	GiantBalloon();
	virtual ~GiantBalloon();
};

