#pragma once

#include "GameNode.h"

class Missile : public GameNode
{
protected:
	int size;
	float angle;
	float angle2;
	float adjustAngle;
	float speed;

	bool isFire;
	bool isHit;

public:
	virtual HRESULT Init();
	virtual void Release() = 0;
	virtual void Update(bool boss1 = false);
	virtual void Render(HDC hdc, bool north, bool south, bool east, bool west) = 0;

	void SetAngle(float _angle, float _angle2);
	void SetSpeed(float _speed);

	void SetisFire(bool fire);
	bool GetisFire();

	void SetisHit(bool _isHit);
	bool GetisHit();

	HBRUSH hBrush;

	Missile();
	~Missile();
};

class PlayerMissile : public Missile
{
private:
	Image * pMissile;
	Image * pMissile2;

	KEYFRAME playerKey;
	KEYFRAME playerKey2;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc, bool north, bool south, bool east, bool west);
};

class EnemyMissile : public Missile
{
private:
	Image * eMissile;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(bool boss1 = false);
	virtual void Render(HDC hdc, bool north, bool south, bool east, bool west);
};
