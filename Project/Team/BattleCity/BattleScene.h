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

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void GameInit();

	BATTLE_TILE_INFO* GetTileInfo() { return tileInfo; }

	void SetGameOver(bool _gameover) { gameOver = _gameover; }
	int GetEnemyNum() { return enemynum; }
	void Setenemynum(int _enemynum) { enemynum = _enemynum; }
	
	BattleScene();
	~BattleScene();
};

