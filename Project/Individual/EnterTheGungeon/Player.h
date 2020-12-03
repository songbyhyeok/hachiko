#pragma once

#include "GameNode.h"

class Image;
class Animation;
class PlayerMissileFactory;
class Collision;
class UI;
class Player : public GameNode
{
private:
	typedef struct tagPlayerIdle
	{
		int north[4] = { 0,1,2,3 };
		int northEast[4] = { 4,5,6,7 };
		int northWest[4] = { 8,9,10,11 };
		int south[4] = { 12,13,14,15 };
		int southEast[4] = { 16,17,18,19 };
		int southWest[4] = { 20,21,22,23 };
	}IDLE;

	typedef struct tagPlayerDodge
	{
		int north[9] = { 0,1,2,3,4,5,6,7,8 };
		int south[9] = { 9,10,11,12,13,14,15,16,17 };
		int side[9] = { 0,1,2,3,4,5,6,7,8 };
	}DODGE, *PDODGE;

	typedef struct tagPlayerDie
	{
		int falldown[8] = { 0,1,2,3,4,5,6,7 };
		int ghost[8] = { 8,9,10,11,12,13,14,15 };
	}DIE;

private:
	Image * player;
	Image * die;
	Image * dodge;
	Image * dodgeBack;
	Image * dodgeSide;
	Image * weapon;
	Image * weaponReload;
	Image * swipe;
	Image * weaponVfx;
	Image * weaponVfx2;

	KEYFRAME swipeKey;
	KEYFRAME reloadKey;
	KEYFRAME vfxKey;
	KEYFRAME vfxKey2;

	RECT rc;
	int size;
	int hp;

	float angle;

	PlayerMissileFactory* mf;

	Animation * idleAni;
	Animation * dieAni;
	Animation * dodgeAni;
	Animation * dodgeBackAni;
	Animation * dodgeSideAni;

	Animation * weaponAni;

	Collision * collision;

	UI * userInterface;

	IDLE idle;
	DODGE dodgeMotion;
	DIE pDie;

	FPOINT eyesight;

	bool equip;
	bool isDead;
	bool isIdle;
	bool isDodge;
	bool isStop;
	bool isDodgeSide;
	bool isReverse;
	bool reloading;

	bool northDirection, southDirection, eastDirection, westDirection;

	int tileIdX, tileIdY;

	int bullet;

	int kill;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void EyesightMode(FPOINT _eyesight);

	RECT* GetRect();

	PlayerMissileFactory* GetMissileMf();

	void SetGunpointDirection(bool north, bool south, bool east, bool west);

	void SetHp(int _hp);
	int GetHp();

	void SetTileIdX(int _idX);
	int GetTileIdX();

	void SetTileIdY(int _idY);
	int GetTileIdY();

	void SetKill(int num);
	int GetKill();

	void SetCollision(Collision* _collision);

	void SetUI(UI* _UI);

	Player();
	~Player();
};

