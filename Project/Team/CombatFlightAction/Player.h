#pragma once

#include "GameNode.h"

class MissileManager;

class Player : public GameNode
{
protected:
	Image * player;
	MissileManager * missileMgr;

	float scale;
	float angle;	float rotateAngle;
	float speed;

	long int life;
	long int life2;


	int fireCount;
	int fireDelay;

	int sufferCount;
	int sufferDelay;

	bool isFire;
	bool isPowerUp;
	bool isSuffer;

	bool isHP;


	
public:
	virtual HRESULT Init();
	virtual void Release() = 0;
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetLift(int _life) { life += _life; }
	int GetLife() { return life; }

	void SetIsSuffer(bool _isSuffer) { isSuffer = _isSuffer; }
	bool GetIsSuffer() { return isSuffer; }

	void SetFireDelay(int maxDelay, int minDelay);
	void FireMode(float angle, float speed);

	MissileManager * GetMissile() { return missileMgr; }

	Player();
	virtual ~Player();
};

class Hyeok : public Player
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Hyeok();
	virtual ~Hyeok();
};

class Dongkyune : public Player
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Dongkyune();
	virtual ~Dongkyune();
};

class Junhyeok : public Player
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Junhyeok();
	virtual ~Junhyeok();
};

