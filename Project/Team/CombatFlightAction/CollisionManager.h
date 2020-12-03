#pragma once

#include "GameNode.h"

class PlayerManager;
class EnemyManager;
class Item;

class CollisionManager : public GameNode
{
private:
	PlayerManager * playerMgr;
	EnemyManager * enemyMgr;
	Item* item;

public:
	virtual void Update();

	void Collision();

	bool CheckCollision(HITBOX iTarget, HITBOX pTarget);

	void SetMgr(PlayerManager * _playerMgr, EnemyManager* _enemyMgr);

	CollisionManager();
	~CollisionManager();
};

