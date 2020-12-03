#pragma once

#include "GameNode.h"
#include <vector>

class Enemy;
class BombMan;
class Comet;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemys;

	int adjustW, adjustH;

	//enemy
	bool isBombMan;
	bool isComet;
	bool isCuteEye;
	bool isShyEye;
	bool isJellyFish;
	bool isUFO;
	bool isUFOEnemy;
	bool isBoss1;

	//boss
	bool isGiantBalloon;

	bool isSwitch;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	vector<Enemy*> GetEnemy() { return vecEnemys; }
	vector<Enemy*>::iterator GetEnemyitr() { return itEnemys; }

	void AddBombMan(int num);
	void AddComet(int num);
	void AddJellyFish(int num);
	void AddUFO(int num);
	void AddUFOEnemy(int num);
	void AddCuteEye(int num);
	void AddShyEye(int num);
	void AddBoss1();

	void SetIsBombMan(bool _isBombMan) { isBombMan = _isBombMan; }
	bool GetIsBombMan() { return isBombMan; }
	void SetIsComet(bool _isComet) { isComet = _isComet; }
	bool GetIsComet() { return isComet; }
	void SetIsCuteEye(bool _isCuteEye) { isCuteEye = _isCuteEye; }
	bool GetIsCuteEye() { return isCuteEye; }
	void SetIsShyEye(bool _isShyEye) { isShyEye = _isShyEye; }
	bool GetIsShyEye() { return isShyEye; }
	void SetIsJellyFish(bool _isJellyFish) { isJellyFish = _isJellyFish; }
	bool GetIsJellyFish() { return isJellyFish; }
	void SetIsUFO(bool _isUFO) { isUFO = _isUFO; }
	bool GetIsUFO() { return isUFO; }
	void SetIsUFOEnemy(bool _UFOEnemy) { isUFOEnemy = _UFOEnemy; }
	bool GetIsUFOEnemy() { return isUFOEnemy; }
	void SetIsBoss1(bool _isBoss1) { isBoss1 = _isBoss1; }
	bool GetIsBoss1() { return isBoss1; }
	void SetIsBool(bool _isSwitch);

	EnemyManager();
	~EnemyManager();
};

