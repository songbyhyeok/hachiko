#pragma once
#include "GameNode.h"
#include <vector>

class BattleScene;
class Image;
class MissileManager;
class Missile;
class Animation;
class Tank : public GameNode
{
protected:

	FPOINT startPos;

	Image* image;
	Image* effectimage;

	int currFrameX, currFrameY;
	int effectFrameX, effectFrameY;
	int updateCount;

	bool up, right, left, down;
	bool isHit;
	int size;
	int HP;
	
	float angle;
	float speed;

	int count;
	int life=3;
	
	int fireDelay;
	int fireCount;
	
	int arrAni[2];
	Animation* ani;
	vector<Missile*> ownmissile;

	MissileManager* missileMgr;
	BattleScene* battlescene;

public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetBattleScene(BattleScene* _battlescene) { battlescene = _battlescene; }
	void SetIsHit(bool _ishit) { isHit = _ishit; }
	void CheckCollision();
	void SetLife(int _life) { life = _life; }
	int GetLife() { return life; }
	//void SetTarget(Tank* tank);
	FPOINT GetPos() { return pos; }

	int GetSize() { return size; }
	HRESULT GameInit(float posX, float posY);
	vector<Missile*> GetMissile() { return ownmissile; }

	Tank();
	virtual ~Tank();
};