#pragma once

#include "GameNode.h"

class Player;
class EnemyFactory;
class Enemy1Factory;
class Enemy2Factory;
class Enemy3Factory;
class Enemy4Factory;
class BossFactory;
class TilemapToolScene;
class Collision : public GameNode
{
private:
	Player* player;
	EnemyFactory* enemyFa;
	TilemapToolScene * mapTool;

	FPOINT* tempPlayerPos;
	RECT* tempPlayerRect;

	FPOINT* tempEnemyPos;
	RECT* tempEnemyRect;

	RECT saveRect;

	bool exit;

	bool playerCheck;
	bool enemyCheck;
public:
	virtual HRESULT Init();
	virtual void Update(); 
	void PlayerUpdate();
	void EnemyUpdate();

	void SetPlayer(Player* _player);
	void SetEnemy1Factory(Enemy1Factory * _enemyFa);
	void SetEnemy2Factory(Enemy2Factory * _enemyFa);
	void SetEnemy3Factory(Enemy3Factory * _enemyFa);
	void SetEnemy4Factory(Enemy4Factory * _enemyFa);
	void SetBossFactory(BossFactory * _enemyFa);
	void SetMapTool(TilemapToolScene* _mapTool);
	void SetTempPlayerPos(FPOINT* _tempPlayerPos);
	void SetTempPlayerRc(RECT* _tempPlayerRc);

	void SetTempEnemyPos(FPOINT* _tempEnemyPos);
	void SetTempEnemyRc(RECT* _tempEnemyRc);

	void SetPlayerCheck(bool _playerCheck);
	bool GetPlayerCheck();

	void SetEnemyCheck(bool _enemyCheck);
	bool GetEnemyCheck();

	Collision();
	~Collision();
};

