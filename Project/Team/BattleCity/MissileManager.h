#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class MissileManager : public GameNode
{
private:
	
	float angle;
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator itMissiles;

	GameNode*	owner;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool Fire();

	void SetOwner(GameNode* gameNode) { owner = gameNode; }
	void SetAngle(float _angle) { angle = _angle; }
	vector<Missile*> GetMissileVector() { return vecMissiles; }

	MissileManager();
	~MissileManager();
};

