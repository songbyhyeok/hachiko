#include "GameManager.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "UI.h"
#include "Item.h"
#include "SceneManager.h"
#include "CollisionManager.h"

HRESULT GameManager::Init()
{
	playerMgr = new PlayerManager();
	playerMgr->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	isUI = new UI();
	isUI->Init();

	/*item = new Item();
	item->Init();*/

	sceneMgr = new SceneManager();
	sceneMgr->Init();
	sceneMgr->SetMgr(playerMgr, enemyMgr, isUI);

	collisionMgr = new CollisionManager();
	collisionMgr->SetMgr(playerMgr, enemyMgr);

	return S_OK;
}

void GameManager::Release()
{
	if (enemyMgr)
	{
		enemyMgr->Release();
		SAFE_DELETE(enemyMgr);
	}

	if (playerMgr)
	{
		playerMgr->Release();
		SAFE_DELETE(playerMgr);
	}

	if (isUI)
	{
		isUI->Release();
		SAFE_DELETE(isUI);
	}

	if (item)
	{
		item->Release();
		SAFE_DELETE(item);
	}

	if (sceneMgr)
	{
		sceneMgr->Release();
		SAFE_DELETE(sceneMgr);
	}

	if (collisionMgr)
	{
		collisionMgr->Release();
		SAFE_DELETE(collisionMgr);
	}
}

void GameManager::Update()
{
	sceneMgr->Update();
	//item->Update();
	collisionMgr->Update();
}

void GameManager::Render(HDC hdc)
{
	sceneMgr->Render(hdc);
	//item->Render(hdc);
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}
