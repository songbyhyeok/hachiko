#pragma once

#include "GameNode.h"
#include "TilemapToolScene.h"

class Image;
class Player;
class EnemyFactory;
class Enemy1Factory;
class Enemy2Factory;
class Enemy3Factory;
class Enemy4Factory;
class BossFactory;
class Collision;
class UI;
class BattleScene : public GameNode
{
private:
	Image* bg;
	Image* magma;
	TilemapToolScene * mapTool;
	Player * player;

	Enemy1Factory * enemy1Fa;
	Enemy2Factory * enemy2Fa;
	Enemy3Factory * enemy3Fa;
	Enemy4Factory * enemy4Fa;
	BossFactory * bossFa;

	Collision* collision;
	UI* userInterface;

	char szText[128];

	KEYFRAME magmaKey;

	bool tempObtain;

	bool stage1;
	bool stage2;
	bool stage3;
	bool tunnel;
	bool bBoss;

	bool enemy1Off;
	bool enemy2Off;
	bool enemy3Off;
	bool enemy4Off;
	bool bossOff;

	bool stageClear;

public:
	virtual HRESULT Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	void SetMapTool(TilemapToolScene * _mapTool);
	PTILE_INF GetTileInf();

	bool GetStage1();
	bool GetStage2();
	bool GetStage3();
	bool GetTunnel();
	bool boss();

	BattleScene();
	~BattleScene();
};

