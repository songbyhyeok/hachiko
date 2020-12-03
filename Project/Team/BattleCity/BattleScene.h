#pragma once
#include "GameNode.h"
#include "pch.h"

class Tank;
class EnemyManager;
class Image;
class Camel;
class Button;
class ChangeScene;
class BattleScene : public GameNode
{
private:
	int updateCount;
	float EnemyTime;
	bool gameOver;
	Image* bg;
	Image* blackbg;

	EnemyManager* enemyMgr;
	EnemyManager* enemyMgr2;
	EnemyManager* enemyMgr3;

	
	Tank* tank;
	Camel* camel;

	BATTLE_TILE_INFO tileInfo[TILE_X*TILE_Y];
	
	Button* loadbutton;

	Image* sampleTileImage;
	Image* objSampleTileImage;

	ChangeScene* changescene;
	

	int score;
	int enemynum;

	Image * enemyNum;
public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)
	void GameInit();

	BATTLE_TILE_INFO* GetTileInfo() { return tileInfo; }

	void SetGameOver(bool _gameover) { gameOver = _gameover; }
	int GetEnemyNum() { return enemynum; }
	void Setenemynum(int _enemynum) { enemynum = _enemynum; }
	
	BattleScene();
	~BattleScene();
};

