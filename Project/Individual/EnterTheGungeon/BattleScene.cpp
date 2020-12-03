#include "BattleScene.h"
#include "Image.h"
#include "ChangeScene.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "Collision.h"
#include "UI.h"
#include <iostream>

HRESULT BattleScene::Init()
{
	srand((unsigned int)time(NULL));

	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	bg = ImageManager::GetSingleton()->FindImage("샘플타일");

	magma = ImageManager::GetSingleton()->AddImage("마그마타일", "Image/maptool/magma.bmp", 0, 0,
		420, 60, 7, 1, true, RGB(255, 0, 255));

	player = new Player();
	player->Init();

	userInterface = new UI();
	userInterface->Init();
	userInterface->SetPlayer(player);

	player->SetUI(userInterface);

	enemy1Fa = new Enemy1Factory();
	enemy2Fa = new Enemy2Factory();
	enemy3Fa = new Enemy3Factory();
	enemy4Fa = new Enemy4Factory();
	bossFa = new BossFactory();

	collision = new Collision();
	collision->Init();
	collision->SetPlayer(player);
	(collision)->SetEnemy1Factory(enemy1Fa);
	collision->SetMapTool(mapTool);

	player->SetCollision(collision);

	enemy1Fa->SetCollision(collision);
	enemy1Fa->SetMapTool(mapTool); 
	enemy1Fa->NewEnemy(4, 200, 600);

	enemy2Fa->SetCollision(collision);
	enemy2Fa->SetMapTool(mapTool);
	enemy2Fa->NewEnemy(5, 350, 450);

	enemy3Fa->SetCollision(collision);
	enemy3Fa->SetMapTool(mapTool);
	enemy3Fa->NewEnemy(4, 250, 400);

	enemy4Fa->SetCollision(collision);
	enemy4Fa->SetMapTool(mapTool);
	enemy4Fa->NewEnemy(3, 400, 300);

	bossFa->SetCollision(collision);
	bossFa->SetMapTool(mapTool);
	bossFa->NewEnemy(1, 500, 500);
	
	ChangeScene::GetSingleton()->SetBattleScene(this);
	ChangeScene::GetSingleton()->stage1();

	//Sleep(1000);

	SetFrame(&magmaKey, 15, 0, 0, magma->GetMaxKeyFrameX(), magma->GetMaxKeyFrameY());

	stage1 = true;	stage2 = false;
	stage3 = false;	tunnel = false;
	bBoss = false;	stageClear = false;

	enemy1Off = false;
	enemy2Off = false;
	enemy3Off = false;
	enemy4Off = false;
	bossOff = false;

	return S_OK;
}

void BattleScene::Release()
{
	if (player)
	{
		player->Release();
		SAFE_DELETE(player);
	}

	if (enemy1Fa)
	{
		enemy1Fa->Release();
		SAFE_DELETE(enemy1Fa);
	}

	if (enemy2Fa)
	{
		enemy2Fa->Release();
		SAFE_DELETE(enemy2Fa);
	}

	if (enemy3Fa)
	{
		enemy3Fa->Release();
		SAFE_DELETE(enemy3Fa);
	}

	if (enemy4Fa)
	{
		enemy4Fa->Release();
		SAFE_DELETE(enemy4Fa);
	}

	if (bossFa)
	{
		bossFa->Release();
		SAFE_DELETE(bossFa);
	}

	if (collision)
	{
		collision->Release();
		SAFE_DELETE(collision);
	}

	if (userInterface)
	{
		userInterface->Release();
		SAFE_DELETE(userInterface);
	}
}

void BattleScene::Update()
{
	if (!stage1 && stage2)
		if (player->GetPos().y < 40 &&
			player->GetPos().x > 510 &&
			player->GetPos().x < 700)
		{
			ChangeScene::GetSingleton()->stage1();

			stage1 = true;
			stage2 = false;

			if (stage1 && !stage2)
			{
				FPOINT tempPos;
				tempPos.x = 600;	tempPos.y = 790;

				player->SetPos(tempPos);

			}
		}

	if (stage1 && !stage2)
		if (player->GetPos().y > 800 &&
			player->GetPos().x > 510 &&
			player->GetPos().x < 700)
		{
			ChangeScene::GetSingleton()->stage2();

			stage1 = false;
			stage2 = true;

			if (!stage1 && stage2)
			{
				FPOINT tempPos;
				tempPos.x = 600;	tempPos.y = 90;

				player->SetPos(tempPos);

			}
		}

	if (stage2 && !tunnel)
		if (player->GetPos().y > 800 &&
			player->GetPos().x > 510 &&
			player->GetPos().x < 700)
		{
			ChangeScene::GetSingleton()->tunnel();


			stage2 = false;
			tunnel = true;

			if (!stage2 && tunnel)
			{
				FPOINT tempPos;
				tempPos.x = 600;	tempPos.y = 90;

				player->SetPos(tempPos);

			}
		}

	if (!stage2 && tunnel)
		if (player->GetPos().y < 40 &&
			player->GetPos().x > 510 &&
			player->GetPos().x < 700)
		{
			ChangeScene::GetSingleton()->stage2();


			stage2 = true;
			tunnel = false;

			if (stage2 && !tunnel)
			{
				FPOINT tempPos;
				tempPos.x = 600;	tempPos.y = 790;

				player->SetPos(tempPos);

			}
		}

	if (!bBoss && tunnel)
		if (player->GetPos().y < 800 &&
			player->GetPos().x > 510 &&
			player->GetPos().x < 700)
		{
			ChangeScene::GetSingleton()->boss();


			bBoss = true;
			tunnel = false;

			if (bBoss && !tunnel)
			{
				FPOINT tempPos;
				tempPos.x = 150;	tempPos.y = 200;

				player->SetPos(tempPos);

			}
		}

	if (bBoss)
		SetMoveFrameX(&magmaKey, 16, 15);

	player->Update();

	if (player->GetKill() == 10)
		enemy1Off = true;

	else if (player->GetKill() == 15)
		enemy2Off = true;

	else if (player->GetKill() == 20)
		enemy3Off = true;

	else if (player->GetKill() == 30)
		enemy4Off = true;

	else if (player->GetKill() == 45)
		bossOff = true;

	if (!enemy1Off)
		enemy1Fa->Update();

	else if (player->GetKill() >= 10 && !enemy2Off)
	{
		(collision)->SetEnemy2Factory(enemy2Fa);
			enemy2Fa->Update();
	}

	else if (player->GetKill() >= 15 && !enemy3Off)
	{
		(collision)->SetEnemy3Factory(enemy3Fa);
		enemy3Fa->Update();
	}

	else if (player->GetKill() >= 20 && !enemy4Off)
	{
		(collision)->SetEnemy4Factory(enemy4Fa);
		enemy4Fa->Update();
	}

	else if (player->GetKill() >= 30 && !bossOff)
	{
		(collision)->SetBossFactory(bossFa);
		bossFa->Update();
	}
}

void BattleScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, 1200, 900, BLACKNESS);
	
	for (int i = 0; i < MAIN_TILE_Y * MAIN_TILE_X; i++)
	{		bg->FrameRender(hdc, 
			(mapTool->GetTileInf()[i].rcTile.left + TILE_SIZE / 2),
			(mapTool->GetTileInf()[i].rcTile.top + TILE_SIZE / 2),
			mapTool->GetTileInf()[i].sFrameX, 
			mapTool->GetTileInf()[i].sFrameY);
		
		if (mapTool->GetTileInf()[i].sTerrain == MAGMA)
		{
			magma->FrameRender(hdc,
				(mapTool->GetTileInf()[i].rcTile.left + TILE_SIZE / 2),
				(mapTool->GetTileInf()[i].rcTile.top + TILE_SIZE / 2),
				magmaKey.curFrameX,
				magmaKey.curFrameY);
		}
	}

	/*sprintf_s(szText, "마우스 : [%d, %d]", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, WINSIZE_X - 160, 10, szText, strlen(szText));

	sprintf_s(szText, "위치 : [%d, %d]", (int)player->GetPos().x, (int)player->GetPos().y);
	TextOut(hdc, WINSIZE_X - 160, 30, szText, strlen(szText));
	
	sprintf_s(szText, "타일 인덱스 : [%d, %d]", player->GetTileIdX(), player->GetTileIdY());
	TextOut(hdc, WINSIZE_X - 160, 50, szText, strlen(szText));*/

	/*if (collision->GetCheck() == true)
	sprintf_s(szText, "충돌ㅇ.");
	else
	sprintf_s(szText, "충돌x.");

	TextOut(hdc, WINSIZE_X - 160, 70, szText, strlen(szText));*/

	player->Render(hdc);

	if (!enemy1Off)
	{
		enemy1Fa->Render(hdc);
		
		//enemy1Fa->GetEnemyIt = enemy1Fa->GetEnemy().begin();

	}

	else if (player->GetKill() >= 10 && !enemy2Off)
		enemy2Fa->Render(hdc);

	else if (player->GetKill() >= 15 && !enemy3Off)
		enemy3Fa->Render(hdc);

	else if (player->GetKill() >= 20 && !enemy4Off)
		enemy4Fa->Render(hdc);

	else if (player->GetKill() >= 20 && !enemy4Off)
		enemy4Fa->Render(hdc);

	else if (player->GetKill() >= 30 && !bossOff)
		bossFa->Render(hdc);

	userInterface->Render(hdc);
}

void BattleScene::SetMapTool(TilemapToolScene * _mapTool)
{
	mapTool = _mapTool;
}

PTILE_INF BattleScene::GetTileInf()
{
	return mapTool->GetTileInf();
}

bool BattleScene::GetStage1()
{
	return stage1;
}

bool BattleScene::GetStage2()
{
	return stage2;
}

bool BattleScene::GetStage3()
{
	return stage3;
}

bool BattleScene::GetTunnel()
{
	return tunnel;
}

bool BattleScene::boss()
{
	return bBoss;
}

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}
