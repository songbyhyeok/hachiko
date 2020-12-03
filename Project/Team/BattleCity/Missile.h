#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Image;
class Animation;
class Missile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;
	float speed;
	bool isFire;
	float adjustAngle;
	bool isCrash;
	bool isMissileCrash;
	int direction;
	int effecttime;
	int effectframeX;

	Animation* ani;
	Enemy* target;
	Image* img;
	Image* effectimg;
	Image* startimg;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTarget(Enemy* enemy) { target = enemy; }
	virtual void SetPos(FPOINT pt) { pos = pt; }
	virtual FPOINT GetPos() { return pos; }
	void SetIsFire(bool b) { isFire = b; }
	bool GetIsFire() { return isFire; }
	bool GetIsCrash() { return isCrash; }
	void SetAngle(float angle) { this->angle = angle; }
	float GetSize() { return size; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetIsCrash(bool iscrash) { isCrash = iscrash; }
	void SetIsMissileCrash(bool _ismissilecrash) {	isMissileCrash = _ismissilecrash;}

	void SetDirection(int _Direction) { direction = _Direction; }

	Missile();
	~Missile();
};

