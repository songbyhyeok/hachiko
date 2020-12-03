#pragma once

#include "GameNode.h"

class EnemyManager;
class PlayerManager;
class UI;
class SceneManager;
class CollisionManager;
class Item;
class GameManager : public GameNode
{
private:
	EnemyManager * enemyMgr;
	PlayerManager * playerMgr;
	UI * isUI;
	Item * item;
	SceneManager * sceneMgr;
	CollisionManager * collisionMgr;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	GameManager();
	~GameManager();
};

