#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Image;
class Missile : public GameNode
{
protected:
	Image* img;
	GameNode* target;

	int size;
	float speed;
	float angleY;
	float angleX;
	float adjustAngle;
	bool isFire;

	float leftX;
	float leftY;

	float rightX;
	float rightY;

	bool isCrash;

	bool istest;

public:
	virtual HRESULT Init(Image * lowImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	void SetTarget(GameNode* enemy);
	void SetSpeed(float _speed);
	void SetAngleX(float _angleX);
	void SetAngleY(float _angleY);
	void SetIsFire(bool _isFire);

	void SetIsCrash(bool _isCrash) { isCrash = _isCrash; }
	bool GetIsCrash() { return isCrash; }

	void SetIsPosX(float x) { pos.x += x; }
	void SetIsPosY(float y) { pos.y += y; }

	bool GetIsFire();
	float GetSize();

	void SetIsTest(bool a) { istest = a; }
	bool GetIsTest() { return istest; }

	Missile();
	~Missile();
};

class NormalMissile : public Missile
{
protected:
	Image* normalImg;

public:
	virtual HRESULT Init(Image * norImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	NormalMissile();
	virtual ~NormalMissile();
};

class HighMissile : public NormalMissile
{
private:
	Image* highImg;

public:
	virtual HRESULT Init(Image * _highImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	HighMissile();
	virtual ~HighMissile();
};

class EnemyMissile : public Missile
{
private:
	Image* enemyImg;
public:
	virtual HRESULT Init(Image * _enemyImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	EnemyMissile();
	virtual ~EnemyMissile();
};

class Enemy1Missile : public Missile
{
private:
	Image* enemy1Img;
public:
	virtual HRESULT Init(Image * _enemy1Img, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	Enemy1Missile();
	virtual ~Enemy1Missile();
};


class UFOMissile : public Missile
{
private:
	Image* ufoImg;
public:
	virtual HRESULT Init(Image * _ufoImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	UFOMissile();
	virtual ~UFOMissile();
};


class EyeMissile : public Missile
{
private:
	Image* eyeImg;
public:
	virtual HRESULT Init(Image * _eyeImg, int _width, int _height, int maxKeyX, int maxKeyY);
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	EyeMissile();
	virtual ~EyeMissile();
};

